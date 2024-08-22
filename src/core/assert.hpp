#ifndef __ASSERT_HPP
#define __ASSERT_HPP

#define YAML_ASSERTIONS_ENABLED

#ifdef YAML_ASSERTIONS_ENABLED
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
      YAML_CRITICAL(std::format("{}, {}, {}", #expr, __FILE__, __LINE__));     \
      debugBreak();                                                            \
    }                                                                          \
  }

#define YAML_ASSERTM(expr, msg)                                                \
  {                                                                            \
    if (expr) {                                                                \
    } else {                                                                   \
      YAML_CRITICAL(                                                           \
          std::format("{}, {}, {}, {}", #expr, msg, __FILE__, __LINE__));      \
      debugBreak();                                                            \
    }                                                                          \
  }

#else

#define YAML_ASSERT(expr)
#define YAML_ASSERTM(expr, msg)

#endif // YAML_ASSERTIONS_ENABLED

#endif // __ASSERT_HPP