#include <mutex>
#include <thread>
#include <optional>
#include <stdexcept>

#include <iostream>

#include "x/util.hpp"

#include "event/bus.hpp"
#include "event/type/draw.hpp"

#include "canvas.hpp"

canvas::canvas(
  x::connection connection,
  x::id window
) : m_connection(connection) {
  const x::setup &setup(m_connection.get<x::setup>());
  auto screen_it = x::range::screen(setup).begin();

  if (std::optional rootv = x::util::root_visualtype(*screen_it)) {
    m_surface = std::make_unique<cairo::surface>(
      connection,
      window,
      *rootv,
      screen_it->width_in_pixels,
      screen_it->height_in_pixels
    );
    m_context = std::make_unique<cairo::context>(*m_surface);
  } else {
    throw std::runtime_error("unable to acquire root visualtype");
  }

  event::debus.subscribe<event::type::draw>(*this);
}

auto canvas::render(cairo::surface &output) -> void {
  cairo::source::surface output_source;

  output_source << output
                << cairo::source::x(150)
                << cairo::source::y(150);

  *m_context << output_source
             << cairo::context::operation::paint;

  cairo_surface_flush(*m_surface);
}

auto canvas::set_background(const std::string &rgba) -> void {
  cairo::source::rgba rgba_source(rgba);

  *m_context << rgba_source
             << cairo::context::operation::rect
             << std::make_tuple(0, 0, 1920, 1080)
             << cairo::context::operation::fill;

  cairo_surface_flush(*m_surface);
}

auto canvas::set_background(const std::filesystem::path &png) -> void {
  if (!std::filesystem::exists(png)) {
    throw std::runtime_error("no such image");
  }

  cairo::surface image_surface(png.c_str());
  cairo::source::surface image_source;

  image_source << image_surface
               << cairo::source::x(0)
               << cairo::source::y(0);

  *m_context << image_source
             << cairo::context::operation::paint;

  cairo_surface_flush(*m_surface);
}

auto canvas::on(const event::type::draw &event) -> void {
  auto thread_id = std::this_thread::get_id();

  std::scoped_lock lock(m_cairo_mutex);

  std::cout << "LOCKED: " << thread_id << std::endl;

  auto [ surface ] = event;

  cairo::source::surface output_source;

  output_source << surface
                << cairo::source::x(150)
                << cairo::source::y(150);

  *m_context << output_source
             << cairo::context::operation::paint;

  cairo_surface_flush(*m_surface);
  m_connection << x::flush;
}
