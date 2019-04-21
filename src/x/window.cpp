#include <xcb/xcb.h>

#include "window.hpp"

namespace x::cw {

auto operator<<(window &w, const depth &depth) -> window & {
  w.depth = depth;
  return w;
}

auto operator<<(window &w, const x &x) -> window & {
  w.x = x;
  return w;
}

auto operator<<(window &w, const y &y) -> window & {
  w.y = y;
  return w;
}

auto operator<<(window &w, const width &width) -> window & {
  w.width = width;
  return w;
}

auto operator<<(window &w, const height &height) -> window & {
  w.height = height;
  return w;
}

auto operator<<(window &w, const border_width &border_width) -> window & {
  w.border_width = border_width;
  return w;
}

auto operator<<(window &w, const _class &_class) -> window & {
  w._class = _class;
  return w;
}

auto operator<<(window &w, const window_id &id) -> window & {
  w.wid = id;
  return w;
}

auto operator<<(window &w, const parent &parent) -> window & {
  w.parent = parent;
  return w;
}

auto operator<<(window &w, const visual &visual) -> window & {
  w.visual = visual;
  return w;
}

auto operator<<(window &w, const mask_flag &flag) -> window & {
  w.value_mask |= flag;
  return w;
}

auto operator<<(window &w, const mask_value &mask_value) -> window & {
  w.value_list.emplace_back(mask_value);
  return w;
}

} // namespace x::window
