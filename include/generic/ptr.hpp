#pragma once

#include <memory>
#include <utility>
#include <functional>
#include <type_traits>

namespace generic {

template <typename type, typename deleter = std::function<void(type *)>>
class unique_wrapper {
public:
  using pointer = typename std::add_pointer<type>::type;

  template <typename ...ts>
  explicit unique_wrapper(ts && ...args) : m_impl(std::forward<ts>(args)...) { }

  operator pointer() { return m_impl.get(); }

protected:
  std::unique_ptr<type, deleter> m_impl;
};

template <typename type>
class shared_wrapper {
public:
  using pointer = typename std::add_pointer<type>::type;

  template <typename ...ts>
  explicit shared_wrapper(ts && ...args) : m_impl(std::forward<ts>(args)...) { }

  operator pointer() { return m_impl.get(); }

protected:
  std::shared_ptr<type> m_impl;
};

} // namespace generic
