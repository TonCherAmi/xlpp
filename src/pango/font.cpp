#include <string>

#include <pango/pango.h>

#include "pango/font.hpp"

namespace pango::font {

description::description() : description_wrapper(pango_font_description_new(), pango_font_description_free) { }

description::description(
  const std::string &family,
  const size &size,
  const style &style,
  const weight &weight
) : description_wrapper(pango_font_description_new(), pango_font_description_free) {
  *this << size << style << weight;
}

auto description::operator<<(const size &s) -> description & {
  pango_font_description_set_size(*this, s);
  return *this;
}

auto description::operator<<(const style &s) -> description & {
  pango_font_description_set_style(*this, s);
  return *this;
}

auto description::operator<<(const weight &w) -> description & {
  pango_font_description_set_weight(*this, w);
  return *this;
}

auto description::operator<<(const std::string &family) -> description & {
  pango_font_description_set_family(*this, family.c_str());
  return *this;
}

} // namespace pango::font
