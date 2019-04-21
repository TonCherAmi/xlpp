#pragma once

#include <stdexcept>

namespace event {

namespace {
namespace detail {

template <typename event_t>
class notifiable {
public:
  virtual ~notifiable() { }
  virtual auto on(const event_t &event) -> void = 0;
};

} // namespace detail
} // namespace

class inotifiable {
public:
  virtual ~inotifiable() { };

  template <typename event_t>
  auto on(const event_t &event) -> void {
    auto result = dynamic_cast<detail::notifiable<event_t>*>(this);

    if (result == nullptr) {
      throw std::domain_error("invalid event type");
    }

    result->on(event);
  }
};

template <typename event_t, typename ...event_ts>
class notifiable : public inotifiable, public detail::notifiable<event_t>, public detail::notifiable<event_ts>... { };

} // namespace event
