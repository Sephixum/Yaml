#include "core/core.hpp"
#include "core/window.hpp"

int main() {
  YAML_DEBUG("Hello how are you ?");
  YAML_ASSERTM(1 == 1, "1 is not equal to 1");

  Yaml::Window window = Yaml::Window::Builder()
                            .setTitle("Hello World")
                            .setSize(800,800)
                            .build();


  return EXIT_SUCCESS;
}