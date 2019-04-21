#include <stdexcept>

#include "connection.hpp"

namespace x {

connection::connection(
  const std::string &displayname
) : connection_wrapper(xcb_connect(nullptr, nullptr), xcb_disconnect) { }

auto connection::setevfl(eventflag evfl) -> void {
  m_evfl = evfl;
}

template <>
auto connection::get<setup>() const -> const setup & {
  return *xcb_get_setup(m_impl.get());
}

auto connection::generate_id() const -> id {
  return xcb_generate_id(m_impl.get());
}

connection::operator bool() const {
  return xcb_connection_has_error(m_impl.get()) == 0;
}

auto connection::operator<<(std::function<void(connection_wrapper::pointer)> f) -> connection & {
  f(m_impl.get());
  return *this;
}

auto connection::operator<<(operation op) -> connection & {
  switch (op) {
  case operation::none:
  case operation::create:
  case operation::destroy:
  case operation::map:
    m_next = op;
    break;
  case operation::flush:
    xcb_flush(m_impl.get());
    break;
  }

  return *this;
}

auto connection::operator<<(const window &window) -> connection & {
  switch (m_next) {
  case operation::create:
    xcb_create_window(m_impl.get(),
                      window.depth,
                      window.wid,
                      window.parent,
                      window.x, window.y,
                      window.width, window.height,
                      window.border_width,
                      window._class,
                      window.visual,
                      window.value_mask,
                      window.value_list.data());
    break;
  case operation::destroy:
    xcb_destroy_window(m_impl.get(), window.wid);
    break;
  case operation::map:
    xcb_map_window(m_impl.get(), window.wid);
    break;
  default:
    throw std::invalid_argument("operation mismatch");
  }

  return *this;
}

auto connection::operator>>(event::generic &ev) -> connection & {
  xcb_generic_event_t *tmp;

  switch (m_evfl) {
  case eventflag::poll:
    tmp = xcb_poll_for_event(m_impl.get());
  case eventflag::wait:
    tmp = xcb_wait_for_event(m_impl.get());
  }

  if (!tmp) {
    throw std::runtime_error("connection error");
  }

  ev = event::generic(tmp);

  return *this;
}

auto connection::operator>>(std::function<connection &(connection &)> fn) -> connection & {
  return fn(*this);
}

auto poll(connection &c) -> connection & {
  c.setevfl(connection::eventflag::poll);
  return c;
}

auto wait(connection &c) -> connection & {
  c.setevfl(connection::eventflag::wait);
  return c;
}

} // namespace x
