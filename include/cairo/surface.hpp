#pragma once

#include <filesystem>

#include <cairo/cairo.h>

#include "generic/ptr.hpp"

#include "x/connection.hpp"
#include "x/setup.hpp"
#include "x/window.hpp"

namespace cairo {

using surface_wrapper = ::generic::shared_wrapper<cairo_surface_t>;

class surface : public surface_wrapper {
public:
  explicit surface();
  explicit surface(int width, int height);
  explicit surface(x::connection &c, x::id window, x::visualtype &visualtype, int width, int height);
  explicit surface(const std::filesystem::path &png);
};

} // namespace cairo
