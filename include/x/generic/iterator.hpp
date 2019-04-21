#pragma once

#include <utility>
#include <type_traits>

namespace x::generic {

template <auto next, typename base_iterator>
class input_iterator {
public:
  using iterator   = input_iterator<next, base_iterator>;

  using difference_type   = std::ptrdiff_t;
  using value_type        = typename std::remove_pointer<decltype(base_iterator::data)>::type;
  using pointer           = const typename std::add_pointer<value_type>::type;
  using reference         = const typename std::add_lvalue_reference<value_type>::type;
  using iterator_category = std::input_iterator_tag;

  explicit input_iterator() { }
  explicit input_iterator(base_iterator i) : m_impl(std::move(i)) { }
  explicit input_iterator(xcb_generic_iterator_t &&i) {
    m_impl.data = static_cast<pointer>(i.data);
    m_impl.rem = i.rem;
    m_impl.index = i.index;
  }

  auto operator++() -> iterator & {
    if (m_impl.rem) {
      next(&m_impl);
    } else if (m_impl.data) {
      m_impl.data = nullptr;
    }

    return *this;
  }

  auto operator++(int) -> iterator {
    auto copy = *this;
    ++(*this);
    return copy;
  }

  auto operator*() const -> reference {
    return *m_impl.data;
  }

  auto operator->() const -> pointer {
    return m_impl.data;
  }

  auto operator==(const iterator &rhs) const -> bool {
    return m_impl.data == rhs.m_impl.data;
  }

  auto operator!=(const iterator &rhs) const -> bool {
    return !(*this == rhs);
  }

private:
  base_iterator m_impl;
};

} // namespace x::generic
