#include <format>
#include <iostream>


int main() {
  std::puts(std::format("Hello, {}!", "World").c_str());
  return EXIT_SUCCESS;
}