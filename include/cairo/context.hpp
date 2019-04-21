#pragma once

#include <tuple>

#include <cairo/cairo.h>

#include "generic/ptr.hpp"

#include "pango/layout.hpp"

#include "source.hpp"
#include "surface.hpp"

namespace cairo {

using context_wrapper = ::generic::unique_wrapper<cairo_t>;

class context : public context_wrapper {
public:
  enum class operation { none, line, move, rect, fill, paint, stroke, text };

  context();
  context(surface &surface);

  auto operator<<(operation op) -> context &;

  auto operator<<(const std::tuple<double, double> &t) -> context &;
  auto operator<<(const std::tuple<double, double, double, double> &t) -> context &;

  auto operator<<(const source::rgb &source) -> context &;
  auto operator<<(const source::rgba &source) -> context &;
  auto operator<<(source::surface &source) -> context &;

  auto operator<<(pango::layout &l) -> context &;

private:
  operation m_next{operation::none};
};

} // namespace cairo
