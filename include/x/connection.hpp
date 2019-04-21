#pragma once

#include <tuple>

#include <xcb/xcb.h>

#include "generic/ptr.hpp"

#include "event.hpp"
#include "request.hpp"
#include "setup.hpp"
#include "window.hpp"

namespace x {

using id = uint32_t;

using connection_wrapper = ::generic::shared_wrapper<xcb_connection_t>;

class connection : public connection_wrapper {
public:
  enum class operation { none, create, destroy, flush, map };
  enum class eventflag { poll, wait };

  explicit connection(const std::string &displayname = "");

  auto setevfl(eventflag evfl) -> void;

  template <typename t>
  auto get() const -> const t &;

  auto generate_id() const -> id;

  operator bool() const;

  auto operator<<(std::function<void(connection_wrapper::pointer)> f) -> connection &;

  template <auto f, typename ...ts>
  auto operator<<(request::void_request<f, ts...> &&request) -> connection &;

  template <auto f, auto g, typename ...ts>
  auto operator<<(request::reply_request<f, g, ts...> &request) -> connection &;

  auto operator<<(operation op) -> connection &;
  auto operator<<(const window &window) -> connection &;

  template <auto f, auto g, typename ...ts>
  auto operator>>(request::reply_request<f, g, ts...> &reqyest) -> connection &;

  auto operator>>(event::generic &ev) -> connection &;

  auto operator>>(std::function<connection &(connection &)> fn) -> connection &;

private:
  operation m_next{operation::none};
  eventflag m_evfl{eventflag::poll};
};

auto poll(connection &c) -> connection &;
auto wait(connection &c) -> connection &;

template <auto f, typename ...ts>
auto connection::operator<<(request::void_request<f, ts...> &&request) -> connection & {
  std::apply(f, std::tuple_cat(std::make_tuple(m_impl.get()), request.args()));
  return *this;
}

template <auto f, auto g, typename ...ts>
auto connection::operator<<(request::reply_request<f, g, ts...> &request) -> connection & {
  auto cookie = std::apply(f, std::tuple_cat(std::make_tuple(m_impl.get()), request.args()));
  request.set_cookie(cookie);

  return *this;
}

template <auto f, auto g, typename ...ts>
auto connection::operator>>(request::reply_request<f, g, ts...> &request) -> connection & {
  if (auto cookie = request.get_cookie()) {
    auto reply = g(m_impl.get(), *cookie, nullptr);
    request.set_reply(reply);
  } else {
    throw std::invalid_argument("missing cookie");
  }

  return *this;
}

constexpr auto flush = xcb_flush;

} // namespace x
