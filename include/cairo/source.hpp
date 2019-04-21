#pragma once

#include <string>

#include "generic/value.hpp"

#include "surface.hpp"

namespace cairo::source {

struct rgb {
  rgb();
  rgb(std::string hex);

  double red{0.0};
  double green{0.0};
  double blue{0.0};
};

struct rgba : public rgb {
  using rgb::rgb;

  rgba(std::string hex);

  double alpha{1.0};
};

struct surface {
  cairo::surface _surface;
  int x{0};
  int y{0};
};

using ::generic::value;

class red   : public value<double> { using value::value; };
class green : public value<double> { using value::value; };
class blue  : public value<double> { using value::value; };

class alpha : public value<double> { using value::value; };

class x     : public value<double> { using value::value; };
class y     : public value<double> { using value::value; };

auto operator<<(rgb &source, const red &r) -> rgb &;
auto operator<<(rgb &source, const green &g) -> rgb &;
auto operator<<(rgb &source, const blue &b) -> rgb &;

auto operator<<(rgba &source, const alpha &a) -> rgba &;

auto operator<<(surface &source, const cairo::surface &s) -> surface &;
auto operator<<(surface &source, const x &x) -> surface &;
auto operator<<(surface &source, const y &y) -> surface &;

} // namespace cairo::source
