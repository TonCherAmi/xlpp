#pragma once

#include <vector>

#include <xcb/xcb.h>

#include "generic/value.hpp"

#include "request.hpp"

namespace x {

struct window {
  uint8_t               depth{XCB_COPY_FROM_PARENT};
  xcb_window_t          wid;
  xcb_window_t          parent;
  int16_t               x{0};
  int16_t               y{0};
  uint16_t              width{0};
  uint16_t              height{0};
  uint16_t              border_width{0};
  uint16_t              _class{XCB_WINDOW_CLASS_INPUT_OUTPUT};
  xcb_visualid_t        visual{XCB_WINDOW_CLASS_COPY_FROM_PARENT};
  uint32_t              value_mask{0};
  std::vector<uint32_t> value_list;
};

template <>
class request::void_request<xcb_create_window> {
public:
  auto args() {
    return std::make_tuple(m_depth,
                           m_wid,
                           m_parent,
                           m_x, m_y,
                           m_width, m_height,
                           m_border_width,
                           m_class,
                           m_visual,
                           m_value_mask,
                           m_value_list);
  }

private:
  uint8_t               m_depth{XCB_COPY_FROM_PARENT};
  xcb_window_t          m_wid;
  xcb_window_t          m_parent;
  int16_t               m_x{0};
  int16_t               m_y{0};
  uint16_t              m_width{0};
  uint16_t              m_height{0};
  uint16_t              m_border_width{0};
  uint16_t              m_class{XCB_WINDOW_CLASS_INPUT_OUTPUT};
  xcb_visualid_t        m_visual{XCB_WINDOW_CLASS_COPY_FROM_PARENT};
  uint32_t              m_value_mask{0};
  std::vector<uint32_t> m_value_list;
};

namespace cw {

struct mask {
  using flag = uint32_t;

  static constexpr flag back_pixmap       = XCB_CW_BACK_PIXMAP;
  static constexpr flag back_pixel        = XCB_CW_BACK_PIXEL;
  static constexpr flag border_pixmap     = XCB_CW_BORDER_PIXMAP;
  static constexpr flag border_pixel      = XCB_CW_BORDER_PIXEL;
  static constexpr flag bit_gravity       = XCB_CW_BIT_GRAVITY;
  static constexpr flag win_gravity       = XCB_CW_WIN_GRAVITY;
  static constexpr flag backing_store     = XCB_CW_BACKING_STORE;
  static constexpr flag backing_planes    = XCB_CW_BACKING_PLANES;
  static constexpr flag backing_pixel     = XCB_CW_BACKING_PIXEL;
  static constexpr flag override_redirect = XCB_CW_OVERRIDE_REDIRECT;
  static constexpr flag save_under        = XCB_CW_SAVE_UNDER;
  static constexpr flag event_mask        = XCB_CW_EVENT_MASK;
  static constexpr flag dont_propagate    = XCB_CW_DONT_PROPAGATE;
  static constexpr flag colormap          = XCB_CW_COLORMAP;
  static constexpr flag cursor            = XCB_CW_CURSOR;
};

using ::generic::value;

class depth        : public value<uint8_t>  { using value::value; };
class x            : public value<uint16_t> { using value::value; };
class y            : public value<uint16_t> { using value::value; };
class width        : public value<uint16_t> { using value::value; };
class height       : public value<uint16_t> { using value::value; };
class border_width : public value<uint16_t> { using value::value; };
class _class       : public value<uint16_t> { using value::value; };

class window_id    : public value<xcb_window_t> { using value::value; };
class parent       : public window_id { using window_id::window_id; };
class root         : public parent { using parent::parent; };

class visual       : public value<xcb_visualid_t> { using value::value; };

class mask_flag    : public value<mask::flag> { using value:: value; };
class mask_value   : public value<uint32_t> { using value::value; };

auto operator<<(window &w, const depth &depth)               -> window &;
auto operator<<(window &w, const x &x)                       -> window &;
auto operator<<(window &w, const y &y)                       -> window &;
auto operator<<(window &w, const width &width)               -> window &;
auto operator<<(window &w, const height &height)             -> window &;
auto operator<<(window &w, const border_width &border_width) -> window &;
auto operator<<(window &w, const _class &_class)             -> window &;
auto operator<<(window &w, const window_id &id)              -> window &;
auto operator<<(window &w, const parent &parent)             -> window &;
auto operator<<(window &w, const visual &visual)             -> window &;
auto operator<<(window &w, const mask_flag &flag)            -> window &;
auto operator<<(window &w, const mask_value &mask_value)     -> window &;

} // namespace cw
} // namespace x
