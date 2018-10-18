#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include "window.hpp"

class Application {
 public:
  Application();
  int Run();

 private:
  Window window_;
};

#endif  // APPLICATION_HPP_
