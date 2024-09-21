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

#if defined(YAML_DEBUG_BUILD)
#define YAML_ASSERTIONS_ENABLED
#define YAML_LOGGING_ENABLED
#endif

#define BIT(x) (1 << x)

#endif // __DEFINES_HPP