#pragma once

namespace para {

class runnable {
public:
  virtual ~runnable() { }

  virtual auto run() -> void = 0;
};

} // namespace para
