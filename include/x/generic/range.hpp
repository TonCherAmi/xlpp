#pragma once

#include "iterator.hpp"

namespace x::generic {

template <auto init, auto next, auto last, typename base_iterator>
class range {
public:
  using iterator = input_iterator<next, base_iterator>;

  explicit range() { }

  template <typename t>
  explicit range(const t &i) : m_begin(init(&i)),
                               m_end(++iterator(last(init(&i)))) { }

  auto begin() -> iterator {
    return m_begin;
  }

  auto end() -> iterator {
    return m_end;
  }

private:
  iterator m_begin;
  iterator m_end;
};

} // namespace x::generic
