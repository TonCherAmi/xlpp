#include <stdexcept>

#include <pango/pangocairo.h>

#include "context.hpp"

namespace cairo {

context::context() { }

context::context(
  surface &surface
) : context_wrapper(cairo_create(surface), cairo_destroy) { }

auto context::operator<<(operation op) -> context & {
  switch (op) {
  case operation::none:
  case operation::line:
  case operation::move:
  case operation::rect:
  case operation::text:
    m_next = op;
    break;
  case operation::fill:
    cairo_fill(m_impl.get());
    break;
  case operation::paint:
    cairo_paint(m_impl.get());
    break;
  case operation::stroke:
    cairo_stroke(m_impl.get());
    break;
  }

  return *this;
}

auto context::operator<<(const std::tuple<double, double> &t) -> context & {
  auto [ x, y ] = t;

  switch (m_next) {
  case operation::line:
    cairo_line_to(m_impl.get(), x, y);
    break;
  case operation::move:
    cairo_move_to(m_impl.get(), x, y);
    break;
  default:
    throw std::invalid_argument("operation mismatch");
  }

  return *this;
}

auto context::operator<<(const std::tuple<double, double, double, double> &t) -> context & {
  auto [ x, y, width, height ] = t;

  switch (m_next) {
  case operation::rect:
    cairo_rectangle(m_impl.get(), x, y, width, height);
    break;
  default:
    throw std::invalid_argument("operation mismatch");
  }

  return *this;
}

auto context::operator<<(const source::rgb &source) -> context & {
  cairo_set_source_rgb(m_impl.get(), source.red, source.green, source.blue);
  return *this;
}

auto context::operator<<(const source::rgba &source) -> context & {
  cairo_set_source_rgba(m_impl.get(), source.red, source.green, source.blue, source.alpha);
  return *this;
}

auto context::operator<<(source::surface &source) -> context & {
  cairo_set_source_surface(m_impl.get(), source._surface, source.x, source.y);
  return *this;
}

auto context::operator<<(pango::layout &l) -> context & {
  pango_cairo_show_layout(*this, l);
  return *this;
}

} // namespace cairo
