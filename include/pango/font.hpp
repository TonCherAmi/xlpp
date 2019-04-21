#pragma once

#include <string>

#include <pango/pango.h>

#include "generic/ptr.hpp"
#include "generic/value.hpp"

namespace pango::font {

using ::generic::value;

struct size : public value<int> {
  size(int s) : value(s * scale) { }

  constexpr static int scale = PANGO_SCALE;
};

struct style : public value<PangoStyle> {
  using value::value;

  using flag = PangoStyle;

  static constexpr flag normal  = PANGO_STYLE_NORMAL;
  static constexpr flag italic  = PANGO_STYLE_ITALIC;
  static constexpr flag oblique = PANGO_STYLE_OBLIQUE;
};

struct weight : public value<PangoWeight> {
  using value::value;

  using flag = PangoWeight;

  static constexpr flag thin       = PANGO_WEIGHT_THIN;
  static constexpr flag ultralight = PANGO_WEIGHT_ULTRALIGHT;
  static constexpr flag light      = PANGO_WEIGHT_LIGHT;
  static constexpr flag semilight  = PANGO_WEIGHT_SEMILIGHT;
  static constexpr flag book       = PANGO_WEIGHT_BOOK;
  static constexpr flag normal     = PANGO_WEIGHT_NORMAL;
  static constexpr flag medium     = PANGO_WEIGHT_MEDIUM;
  static constexpr flag semibold   = PANGO_WEIGHT_SEMIBOLD;
  static constexpr flag bold       = PANGO_WEIGHT_BOLD;
  static constexpr flag ultrabold  = PANGO_WEIGHT_ULTRABOLD;
  static constexpr flag heavy      = PANGO_WEIGHT_HEAVY;
  static constexpr flag ultraheavy = PANGO_WEIGHT_ULTRAHEAVY;
};

using description_wrapper = ::generic::unique_wrapper<PangoFontDescription>;

class description : public description_wrapper {
public:
  description();
  description(
    const std::string &family,
    const size &size,
    const style &style,
    const weight &weight
  );

  auto operator<<(const size &s) -> description &;
  auto operator<<(const style &s) -> description &;
  auto operator<<(const weight &w) -> description &;
  auto operator<<(const std::string &family) -> description &;
};

} // namespace pango::font
