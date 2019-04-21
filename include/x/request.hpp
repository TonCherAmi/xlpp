#pragma once

#include <tuple>
#include <vector>
#include <optional>
#include <memory>
#include <type_traits>

#include <xcb/xcb.h>

namespace x {
class connection;
}

namespace x::request {

template <auto request_fn, typename ...arg_types>
class void_request {
public:
  using arg_tuple = std::tuple<arg_types...>;

  explicit void_request(arg_types &&...args) : m_args(std::forward<arg_types>(args)...) { }
  virtual ~void_request() { }

  const auto &args() const {
    return m_args;
  }

private:
  arg_tuple m_args;
};

template <auto request_fn, auto reply_fn, typename ...arg_types>
class reply_request : public void_request<request_fn, arg_types...> {
  friend class x::connection;

  using cookie_type   = typename std::invoke_result<decltype(request_fn),
                                                    xcb_connection_t *,
                                                    arg_types...>::type;
  using reply_pointer = typename std::invoke_result<decltype(reply_fn),
                                                    xcb_connection_t *,
                                                    cookie_type,
                                                    xcb_generic_error_t **>::type;
  using reply_type    = typename std::remove_pointer<reply_pointer>::type;

public:
  using void_request<request_fn, arg_types...>::void_request;

  auto operator->() const -> const std::unique_ptr<reply_type> & {
    return m_reply;
  }

private:
  auto get_cookie() -> std::optional<cookie_type> {
    return m_cookie;
  }

  auto set_cookie(cookie_type cookie) -> void {
    m_cookie = std::move(cookie);
  }

  virtual auto set_reply(reply_pointer p) -> void {
    m_reply.reset(p);
  }

  std::optional<cookie_type> m_cookie;
  std::unique_ptr<reply_type> m_reply;
};

template <template <typename...> typename request_type, typename ...arg_types>
request_type<arg_types...> make(arg_types &&...args) {
  return request_type<arg_types...>(std::forward<arg_types>(args)...);
}

template <typename ...ts>
using create_window = void_request<xcb_create_window, ts...>;

template <typename ...ts>
using map_window = void_request<xcb_map_window, ts...>;

template <typename ...ts>
using get_window_attributes = reply_request<xcb_get_window_attributes, xcb_get_window_attributes_reply, ts...>;

} // namespace x::request
