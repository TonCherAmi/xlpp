#pragma once

#include <thread>
#include <memory>

#include "runnable.hpp"

namespace para {

class runner {
public:
  explicit runner(std::unique_ptr<runnable> r) : m_runnable(std::move(r)) { }

  auto start() -> void {
    m_thread = std::thread(&runnable::run, std::move(m_runnable));
  }

private:
  std::thread m_thread;
  std::unique_ptr<runnable> m_runnable;
};

} // namespace para
