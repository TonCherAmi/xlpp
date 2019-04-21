#pragma once

#include <utility>

namespace generic {

template<typename value_type>
class value {
public:
  explicit value() {}
  explicit value(value_type v) : m_v(std::move(v)) { };

  operator value_type() const { return m_v; }

private:
  value_type m_v;
};

} // namespace generic
