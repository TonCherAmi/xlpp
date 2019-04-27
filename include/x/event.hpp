#pragma once

#include <memory>

#include <xcb/xcb.h>

namespace x::event {

class generic {
public:
  template <typename t>
  friend class basic_event;

  explicit generic() { }
  explicit generic(xcb_generic_event_t *ev) : m_impl(ev) { }

  auto operator->() const -> const std::unique_ptr<xcb_generic_event_t> & {
    return m_impl;
  }

private:
  std::unique_ptr<xcb_generic_event_t> m_impl;
};

template <typename event_type>
class basic_event {
public:
  explicit basic_event(generic &&ev) : m_impl(reinterpret_cast<event_type *>(ev.m_impl.release())) { }

  auto operator->() const -> const std::unique_ptr<event_type> & {
    return m_impl;
  }

private:
  std::unique_ptr<event_type> m_impl;
};

using key_press      = basic_event<xcb_key_press_event_t>;
using key_release    = basic_event<xcb_key_release_event_t>;
using button_press   = basic_event<xcb_button_press_event_t>;
using button_release = basic_event<xcb_button_release_event_t>;

struct type {
  using flag = uint32_t;

  static constexpr flag key_press         = XCB_KEY_PRESS;
  static constexpr flag key_release       = XCB_KEY_RELEASE;
  static constexpr flag button_press      = XCB_BUTTON_PRESS;
  static constexpr flag button_release    = XCB_BUTTON_RELEASE;
  static constexpr flag motion_notify     = XCB_MOTION_NOTIFY;
  static constexpr flag enter_notify      = XCB_ENTER_NOTIFY;
  static constexpr flag leave_notify      = XCB_LEAVE_NOTIFY;
  static constexpr flag focus_in          = XCB_FOCUS_IN;
  static constexpr flag focus_out         = XCB_FOCUS_OUT;
  static constexpr flag keymap_notify     = XCB_KEYMAP_NOTIFY;
  static constexpr flag expose            = XCB_EXPOSE;
  static constexpr flag graphics_exposure = XCB_GRAPHICS_EXPOSURE;
  static constexpr flag no_exposure       = XCB_NO_EXPOSURE;
  static constexpr flag visibility_notify = XCB_VISIBILITY_NOTIFY;
  static constexpr flag create_notify     = XCB_CREATE_NOTIFY;
  static constexpr flag destroy_notify    = XCB_DESTROY_NOTIFY;
  static constexpr flag unmap_notify      = XCB_UNMAP_NOTIFY;
  static constexpr flag map_notify        = XCB_MAP_NOTIFY;
  static constexpr flag map_request       = XCB_MAP_REQUEST;
  static constexpr flag reparent_notify   = XCB_REPARENT_NOTIFY;
  static constexpr flag configure_notify  = XCB_CONFIGURE_NOTIFY;
  static constexpr flag configure_request = XCB_CONFIGURE_REQUEST;
  static constexpr flag gravity_notify    = XCB_GRAVITY_NOTIFY;
  static constexpr flag resize_request    = XCB_RESIZE_REQUEST;
  static constexpr flag circulate_notify  = XCB_CIRCULATE_NOTIFY;
  static constexpr flag circulate_request = XCB_CIRCULATE_REQUEST;
  static constexpr flag property_notify   = XCB_PROPERTY_NOTIFY;
  static constexpr flag selection_clear   = XCB_SELECTION_CLEAR;
  static constexpr flag selection_request = XCB_SELECTION_REQUEST;
  static constexpr flag selection_notify  = XCB_SELECTION_NOTIFY;
  static constexpr flag colormap_notify   = XCB_COLORMAP_NOTIFY;
  static constexpr flag client_message    = XCB_CLIENT_MESSAGE;
  static constexpr flag mapping_notify    = XCB_MAPPING_NOTIFY;
  static constexpr flag ge_generic        = XCB_GE_GENERIC;
};


struct mask {
  using flag = uint32_t;

  static constexpr flag no_event              = XCB_EVENT_MASK_NO_EVENT;
  static constexpr flag key_press             = XCB_EVENT_MASK_KEY_PRESS;
  static constexpr flag key_release           = XCB_EVENT_MASK_KEY_RELEASE;
  static constexpr flag button_press          = XCB_EVENT_MASK_BUTTON_PRESS;
  static constexpr flag button_release        = XCB_EVENT_MASK_BUTTON_RELEASE;
  static constexpr flag enter_window          = XCB_EVENT_MASK_ENTER_WINDOW;
  static constexpr flag leave_window          = XCB_EVENT_MASK_LEAVE_WINDOW;
  static constexpr flag pointer_motion        = XCB_EVENT_MASK_POINTER_MOTION;
  static constexpr flag pointer_motion_hint   = XCB_EVENT_MASK_POINTER_MOTION_HINT;
  static constexpr flag button_1_motion       = XCB_EVENT_MASK_BUTTON_1_MOTION;
  static constexpr flag button_2_motion       = XCB_EVENT_MASK_BUTTON_2_MOTION;
  static constexpr flag button_3_motion       = XCB_EVENT_MASK_BUTTON_3_MOTION;
  static constexpr flag button_4_motion       = XCB_EVENT_MASK_BUTTON_4_MOTION;
  static constexpr flag button_5_motion       = XCB_EVENT_MASK_BUTTON_5_MOTION;
  static constexpr flag button_motion         = XCB_EVENT_MASK_BUTTON_MOTION;
  static constexpr flag keymap_state          = XCB_EVENT_MASK_KEYMAP_STATE;
  static constexpr flag exposure              = XCB_EVENT_MASK_EXPOSURE;
  static constexpr flag visibility_change     = XCB_EVENT_MASK_VISIBILITY_CHANGE;
  static constexpr flag structure_notify      = XCB_EVENT_MASK_STRUCTURE_NOTIFY;
  static constexpr flag resize_redirect       = XCB_EVENT_MASK_RESIZE_REDIRECT;
  static constexpr flag substructure_notify   = XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY;
  static constexpr flag substructure_redirect = XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT;
  static constexpr flag focus_change          = XCB_EVENT_MASK_FOCUS_CHANGE;
  static constexpr flag property_change       = XCB_EVENT_MASK_PROPERTY_CHANGE;
  static constexpr flag color_map_change      = XCB_EVENT_MASK_COLOR_MAP_CHANGE;
  static constexpr flag owner_grab_button     = XCB_EVENT_MASK_OWNER_GRAB_BUTTON;
};

} // namespace x::event
