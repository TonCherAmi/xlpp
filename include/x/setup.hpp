#pragma once

#include <xcb/xcb.h>

#include "generic/range.hpp"

namespace x {

using setup      = xcb_setup_t;
using screen     = xcb_screen_t;
using depth      = xcb_depth_t;
using visualtype = xcb_visualtype_t;

namespace range {

using screen     = generic::range<xcb_setup_roots_iterator,
                                  xcb_screen_next,
                                  xcb_screen_end,
                                  xcb_screen_iterator_t>;

using depth      = generic::range<xcb_screen_allowed_depths_iterator,
                                  xcb_depth_next,
                                  xcb_depth_end,
                                  xcb_depth_iterator_t>;

using visualtype = generic::range<xcb_depth_visuals_iterator,
                                  xcb_visualtype_next,
                                  xcb_visualtype_end,
                                  xcb_visualtype_iterator_t>;

} // namespace range
} // namespace x
