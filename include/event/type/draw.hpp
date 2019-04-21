#pragma once

#include "cairo/surface.hpp"

namespace event::type {

struct draw {
  cairo::surface surface;
};

} // namespace event::type
