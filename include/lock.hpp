#pragma once

#include <memory>

#include "x/connection.hpp"

#include "canvas.hpp"

class lock {
public:
  explicit lock();

  auto run() -> void;

  auto notify(cairo::surface &output) -> void;

protected:
  auto setup_window() -> void;
  auto setup_background() -> void;

private:
  x::id         m_window;
  x::connection m_connection;

  std::unique_ptr<canvas> m_canvas;
};
