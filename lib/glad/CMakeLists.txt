cmake_minimum_required(VERSION 3.21)

project(glad)

add_library(glad STATIC)
target_sources(glad PUBLIC src/glad.c)
target_include_directories(glad PUBLIC include)
