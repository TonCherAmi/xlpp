#pragma once

#include <mutex>
#include <memory>
#include <filesystem>

#include "x/connection.hpp"

#include "cairo/context.hpp"
#include "cairo/surface.hpp"

#include "event/notifiable.hpp"
#include "event/type/draw.hpp"

class canvas : public event::notifiable<event::type::draw> {
public:
  explicit canvas(x::connection connection, x::id window);

  auto render(cairo::surface &output) -> void;

  auto set_background(const std::string &rgba) -> void;
  auto set_background(const std::filesystem::path &png) -> void;

  auto on(const event::type::draw &event) -> void override;

private:
  // x::id m_window{0};

  std::mutex m_cairo_mutex;

  std::unique_ptr<cairo::surface> m_surface;
  std::unique_ptr<cairo::context> m_context;

  x::connection m_connection;
};
