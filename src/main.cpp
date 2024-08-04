#include "core/core.hpp"
#include "window.hpp"

int main() {
  YAML_DEBUG("Hello how are you ?");
  YAML_ASSERTM(1 == 1, "1 is not equal to 1");

  Yaml::Window window = Yaml::Window::Builder()
                            .set_title("Hello World")
                            .set_size(800,800)
                            .build();


  return EXIT_SUCCESS;
}