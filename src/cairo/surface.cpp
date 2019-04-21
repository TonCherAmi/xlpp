#include <cairo/cairo.h>
#include <cairo/cairo-xcb.h>

#include "surface.hpp"

namespace cairo {

surface::surface() { }

surface::surface(
  int width,
  int height
) : surface_wrapper(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height), cairo_surface_destroy) { }

surface::surface(
  x::connection &c,
  x::id window,
  x::visualtype &visualtype,
  int w,
  int h
) : surface_wrapper(cairo_xcb_surface_create(c, window, &visualtype, w, h), cairo_surface_destroy) { }

surface::surface(
  const std::filesystem::path &png
) : surface_wrapper(cairo_image_surface_create_from_png(png.c_str()), cairo_surface_destroy) { }

} // namespace cairo
