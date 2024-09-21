#ifndef __ASSERT_HPP
#define __ASSERT_HPP

#include "pch.hpp"

#if defined(YAML_ASSERTIONS_ENABLED) && defined(NDEBUG)
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

#define YAML_ASSERT(expr)                                                      \
  {                                                                            \
    if (expr) {                                                                \
    } else {                                                                   \
      YAML_CRITICAL(std::format(                                               \
          "{}, {}, {}", #expr,                                                 \
          std::string(__FILE__).substr(std::string(__FILE__).find("src")),     \
          __LINE__));                                                          \
      debugBreak();                                                            \
    }                                                                          \
  }

#define YAML_ASSERTM(expr, msg)                                                \
  {                                                                            \
    if (expr) {                                                                \
    } else {                                                                   \
      YAML_CRITICAL(std::format(                                               \
          "{}, {}, {}, {}", #expr, msg,                                        \
          std::string(__FILE__).substr(std::string(__FILE__).find("src")),     \
          __LINE__));                                                          \
      debugBreak();                                                            \
    }                                                                          \
  }

#else

#define YAML_ASSERT(expr)
#define YAML_ASSERTM(expr, msg)

#endif // YAML_ASSERTIONS_ENABLED

#endif // __ASSERT_HPP