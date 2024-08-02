#ifndef __DEFINES_HPP
#define __DEFINES_HPP

#include "pch.hpp"

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

#define YAML_WARN(...) ::Yaml::Logger::get().warn(__VA_ARGS__);
#define YAML_CRITICAL(...) ::Yaml::Logger::get().critical(__VA_ARGS__);
#define YAML_INFO(...) ::Yaml::Logger::get().info(__VA_ARGS__);
#define YAML_DEBUG(...) ::Yaml::Logger::get().debug(__VA_ARGS__);
#define YAML_TRACE(...) ::Yaml::Logger::get().trace(__VA_ARGS__);
#define YAML_ERROR(...) ::Yaml::Logger::get().error(__VA_ARGS__);

#endif // __DEFINES_HPP