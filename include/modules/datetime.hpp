#pragma once

#include <ctime>
#include <mutex>
#include <chrono>
#include <thread>
#include <future>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <condition_variable>

#include "pango/font.hpp"
#include "pango/layout.hpp"

#include "para/runnable.hpp"

#include "event/bus.hpp"
#include "event/type/draw.hpp"

#include "modules/base.hpp"

class datetime : public module {
public:
  explicit datetime(int a = 5) : approx(a) { }

  auto run() -> void override {
    pango::font::description desc;

    desc << "Roboto Condensed"
         << pango::font::size(20)
         << pango::font::style(pango::font::style::italic)
         << pango::font::weight(pango::font::weight::normal);

    pango::layout layout(m_context);

    std::stringstream time_stream;

    while (true) {
      const std::string time = [&] () -> std::string {
        auto now   = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);

        time_stream << std::put_time(std::localtime(&now_c), "%F %T");

        auto result = time_stream.str();

        time_stream.str(std::string());
        time_stream.clear();

        return result;
      } ();

      layout << desc << time;

      approx += 35;

      m_context << cairo::source::rgb("#f1f1f1")
                << cairo::context::operation::move
                << std::make_tuple(approx, approx)
                << layout;

      // m_receivers.at(0).get().notify(m_surface);

      std::cout << "FROM: " << std::this_thread::get_id() << std::endl;

      event::debus << event::type::draw { .surface = m_surface };

      // std::cout << "wakawaka" << std::endl;

      std::cout << "GOING TO SLEEP" << std::endl;

      std::unique_lock lock(m_sleep_mutex);
      m_sleep_handler.wait_for(lock, std::chrono::milliseconds(2000));

      // std::this_thread::sleep_for(std::chrono::milliseconds(2050));

      std::cout << "WOKE UP" << std::endl;
    }
  }

private:
  int approx { 10 };

  std::mutex m_sleep_mutex;
  std::condition_variable m_sleep_handler;
};
