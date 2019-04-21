#pragma once

#include <string>

#include <pango/pango.h>

#include "generic/ptr.hpp"

#include "font.hpp"

// fwd
namespace cairo {
class context;
}

namespace pango {

using layout_wrapper = ::generic::unique_wrapper<PangoLayout>;

class layout : public layout_wrapper {
public:
  layout(cairo::context &c);

  auto operator<<(font::description &d) -> layout &;
  auto operator<<(const std::string &text) -> layout &;
};

} // namespace pango
