#pragma once

#include <mutex>
#include <thread>
#include <memory>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <stdexcept>
#include <functional>
#include <unordered_map>

#include "event/notifiable.hpp"

namespace event {

class bus {
public:
  template <typename last_event_t>
  auto subscribe(inotifiable &n) -> void {
    std::scoped_lock lock(*m_eventmap_mutex);

    (*m_eventmap)[typeid(last_event_t)].push_back(n);
  }

  template <typename first_event_t, typename second_event_t, typename ...rest>
  auto subscribe(inotifiable &n) -> void {
    std::scoped_lock lock(m_eventmap_mutex);

    // *m_eventmap[typeid(first_event_t)].push_back(n);

    subscribe<first_event_t>(n);
    subscribe<second_event_t, rest...>(n);
  }

  // dispatch
  template <typename event_t>
  auto operator<<(const event_t &event) -> bus & {
    try {
      std::scoped_lock lock(*m_eventmap_mutex);

      const auto &subscribers = m_eventmap->at(typeid(event));

      std::vector<std::thread> threads;

      for (auto &&subscriber : subscribers) {
        threads.emplace_back(&inotifiable::on<event_t>, &subscriber.get(), event);
      }

      for (auto &&thread : threads) {
        thread.join();
      }

      return *this;
    } catch (const std::out_of_range &e) {
      // no subscribers
      return *this;
    }
  }

private:
  // subscriber list
  using sublist  = std::vector<std::reference_wrapper<inotifiable>>;
  using eventmap = std::unordered_map<std::type_index, sublist>;

  std::shared_ptr<std::recursive_mutex> m_eventmap_mutex {
    std::make_shared<std::recursive_mutex>()
  };

  std::shared_ptr<eventmap> m_eventmap { std::make_shared<eventmap>() };
};

// default event bus
extern bus debus;

} // namespace event
