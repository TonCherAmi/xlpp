#include <array>
#include <memory>
#include <iostream>

#include "para/runner.hpp"
#include "modules/datetime.hpp"

#include "lock.hpp"

lock::lock() { }

auto lock::run() -> void {
  setup_window();
  m_canvas = std::make_unique<canvas>(m_connection, m_window);
  setup_background();

  auto mod = std::make_unique<datetime>(15);
  auto mod2 = std::make_unique<datetime>(500);

  auto runner = para::runner(std::move(mod));
  auto runner2 = para::runner(std::move(mod2));

  runner.start();
  runner2.start();

  while (true) { }
}

auto lock::setup_window() -> void {
  namespace ev  = x::event;
  namespace req = x::request;

  const auto &setup = m_connection.get<x::setup>();
  auto screen_it    = x::range::screen(setup).begin();

  m_window = m_connection.generate_id();

  std::array<uint32_t, 2> values{1, ev::mask::key_press | ev::mask::exposure};

  m_connection << req::make<req::create_window>(XCB_COPY_FROM_PARENT,
                                                m_window,
                                                screen_it->root,
                                                0, 0,
                                                screen_it->width_in_pixels,
                                                screen_it->height_in_pixels,
                                                0,
                                                XCB_WINDOW_CLASS_INPUT_OUTPUT,
                                                screen_it->root_visual,
                                                x::cw::mask::override_redirect |
                                                x::cw::mask::event_mask,
                                                values.data())
               << req::make<req::map_window>(m_window)
               << x::flush;
}

auto lock::setup_background() -> void {
  // m_canvas->set_background(std::filesystem::path("/home/vasili/pictures/wallpapers/mountains.png"));
  m_canvas->set_background(std::string("#000"));

  m_connection << x::flush;
}

auto lock::notify( cairo::surface &output) -> void {
  m_canvas->render(output);
  std::cout << "GOT OUTPUT" << std::endl;
}
