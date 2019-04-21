#include <stdexcept>

#include "source.hpp"

namespace cairo::source {

rgb::rgb() { }

rgb::rgb(std::string hex) {
  hex.erase(0, 1);

  switch (hex.length()) {
  case 3:
    hex = { hex.at(0), hex.at(0), hex.at(1), hex.at(1), hex.at(2), hex.at(2) };
  case 6:
    red = static_cast<double>(std::stoi(hex.substr(0, 2), nullptr, 16)) / 255.0;
    green = static_cast<double>(std::stoi(hex.substr(2, 2), nullptr, 16)) / 255.0;
    blue = static_cast<double>(std::stoi(hex.substr(4, 2), nullptr, 16)) / 255.0;
    break;
  default:
    throw std::invalid_argument("invalid string length");
  }
}

rgba::rgba(std::string hex) : rgb(hex.substr(0, hex.length() > 5 ? 7 : 4)) {
  hex.erase(0, 1);

  switch (hex.length()) {
  // allow to omit alpha
  case 3:
  case 6:
    break;
  case 4:
    hex = { hex.at(0), hex.at(0), hex.at(1), hex.at(1), hex.at(2), hex.at(2), hex.at(3), hex.at(3) };
  case 8:
    alpha = static_cast<double>(std::stoi(hex.substr(6, 2), nullptr, 16)) / 255.0;
    break;
  default:
    throw std::invalid_argument("invalid string length");
  }
}

auto operator<<(rgb &source, const red &r) -> rgb & {
  source.red = r;
  return source;
}

auto operator<<(rgb &source, const green &g) -> rgb & {
  source.green = g;
  return source;
}

auto operator<<(rgb &source, const blue &b) -> rgb & {
  source.blue = b;
  return source;
}

auto operator<<(rgba &source, const alpha &a) -> rgba & {
  source.alpha = a;
  return source;
}

auto operator<<(surface &source, const cairo::surface &s) -> surface & {
  source._surface = s;
  return source;
}

auto operator<<(surface &source, const x &x) -> surface & {
  source.x = x;
  return source;
}

auto operator<<(surface &source, const y &y) -> surface & {
  source.y = y;
  return source;
}

} // namespace cairo::source
