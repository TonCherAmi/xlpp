#pragma once

#include "x/event.hpp"
#include "x/connection.hpp"

#include "para/runnable.hpp"

#include "event/bus.hpp"

namespace event::adapter {

class x : public para::runnable {
public:
  explicit x(x::connection connection);

  auto run() -> void override;

private:
  x::connection m_connection;
}

} // namespace event::adapter
