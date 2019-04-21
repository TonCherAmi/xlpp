#include <iostream>
#include <tuple>
#include <thread>
#include <chrono>
#include <exception>

#include <xcb/xcb.h>

#include "x/connection.hpp"
#include "x/setup.hpp"
#include "x/event.hpp"
#include "x/window.hpp"
#include "x/util.hpp"

#include "cairo/surface.hpp"
#include "cairo/context.hpp"
#include "cairo/source.hpp"

#include "lock.hpp"

auto main() -> int {
  lock l;

  l.run();
}

auto old_main() -> int {
  try {
    x::connection c;
    const x::setup &setup{c.get<x::setup>()};

    x::range::screen screens{setup};

    auto it = screens.begin();

    x::window win;

    x::id id{c.generate_id()};

    win << x::cw::window_id(id)
        << x::cw::parent(it->root)
        << x::cw::width(it->width_in_pixels)
        << x::cw::height(it->height_in_pixels)
        << x::cw::x(0)
        << x::cw::y(0)
        << x::cw::visual(it->root_visual)
        << x::cw::mask_flag(x::cw::mask::override_redirect)
        << x::cw::mask_value(1)
        << x::cw::mask_flag(x::cw::mask::event_mask)
        << x::cw::mask_value(x::event::mask::key_press | x::event::mask::exposure);

    std::array<uint32_t, 2> values{1, x::event::mask::key_press | x::event::mask::exposure};

    c << x::request::make<x::request::create_window>(win.depth,
                                                     win.wid,
                                                     win.parent,
                                                     win.x, win.y,
                                                     win.width, win.height,
                                                     win.border_width,
                                                     win._class,
                                                     win.visual,
                                                     x::cw::mask::override_redirect | x::cw::mask::event_mask,
                                                     values.data())
    // c << x::connection::operation::create
    //   << win
      << x::request::make<x::request::map_window>(win.wid)
      << x::flush;
      // << x::connection::operation::map
      // << win
      // << x::connection::operation::flush;

    // auto mapr = x::request::make<x::request::map_window>(win.wid);

    // c << mapr << xcb_flush;

    auto winattrs = x::request::make<x::request::get_window_attributes>(win.wid);

    c << winattrs
      >> winattrs;

    std::cout << std::boolalpha
              << "Override redirect: "
              << static_cast<int>(winattrs->length)
              << std::endl;

    c >> x::wait;

    if (std::optional rootv = x::util::root_visualtype(*it)) {
      cairo::surface surface(c, win.wid, *rootv, it->width_in_pixels, it->height_in_pixels);
      cairo::context context(surface);

      cairo::surface image_surface("/tmp/test.png");

      cairo::source::surface image_source;

      image_source << image_surface
                   << cairo::source::x(0)
                   << cairo::source::y(0);

      context << image_source;

      x::event::generic ge;
      while (c >> ge) {
        switch (ge->response_type & ~0x80) {
        case x::event::type::key_press: {
          x::event::key_press ev(std::move(ge));
          std::cout << "Key: " << ev->detail << std::endl;
          break;
        }
        case x::event::type::expose: {
          for (int i = 1; i <= it->height_in_pixels; i++) {
            context << cairo::context::operation::rect
                    << std::make_tuple(0, i, it->width_in_pixels, 1)
                    << cairo::context::operation::fill;

            cairo_surface_flush(surface);

            //c << x::connection::operation::flush;
            //xcb_aux_sync(c);
          }
        }
        }
      }

      c << x::connection::operation::flush;
    } else {
      throw std::string("MOTHERFUCKER");
    }

  } catch (const std::exception &e) {
    std::cout << "err in  main: " << e.what() << std::endl;
  }

  return 0;
}
