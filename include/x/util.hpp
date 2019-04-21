#pragma once

#include <optional>

#include "setup.hpp"

namespace x::util {

static auto root_visualtype(const screen &screen) -> std::optional<visualtype> {
  for (auto &&depth : range::depth(screen)) {
    for (auto &&visual : range::visualtype(depth)) {
      if (screen.root_visual == visual.visual_id) {
        return visual;
      }
    }
  }

  return std::nullopt;
}

} // namespace x::util
