#include <string>

#include <pango/pangocairo.h>

#include "cairo/context.hpp"

#include "pango/font.hpp"
#include "pango/layout.hpp"

namespace pango {

layout::layout(
  cairo::context &c
) : layout_wrapper(pango_cairo_create_layout(c), g_object_unref) { }

auto layout::operator<<(font::description &d) -> layout & {
  pango_layout_set_font_description(*this, d);
  return *this;
}

auto layout::operator<<(const std::string &text) -> layout & {
  pango_layout_set_text(*this, text.c_str(), -1);
  return *this;
}

} // namespace pango
