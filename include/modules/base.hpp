#pragma once

#include <thread>
#include <memory>
#include <vector>
#include <functional>

#include "para/runnable.hpp"
#include "event/notifiable.hpp"

#include "cairo/surface.hpp"
#include "cairo/context.hpp"

class module : public para::runnable {
public:
  module() {
    m_surface = cairo::surface(1000, 1000);
    m_context = cairo::context(m_surface);
  }

protected:
  cairo::surface m_surface;
  cairo::context m_context;
};
