cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

file(GLOB_RECURSE SOURCES "src/*.cpp")

project(
  Yaml
  VERSION 0.0.1
  DESCRIPTION "Yet another model loader."
  LANGUAGES CXX C)

find_package(spdlog CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_compile_options(-Wall)

option(FORCE_COLORED_OUTPUT
  "Always produce ANSI-colored output (GNU/Clang only)" TRUE)

if(${FORCE_COLORED_OUTPUT})
  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
  endif()

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
  endif()
endif()

add_executable(yaml)
target_sources(yaml PUBLIC ${SOURCES})
target_include_directories(yaml PUBLIC src/)
target_link_libraries(yaml PUBLIC spdlog::spdlog EnTT::EnTT SDL2::SDL2)
target_precompile_headers(yaml PUBLIC "src/core/pch.hpp")

# ##############################################################################
# copies compile_commands.json to the source cmake directory for clang support.
# ##############################################################################
if(NOT MSVC)
  add_custom_target(
    copy_compile_commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_LIST_DIR})
endif()
