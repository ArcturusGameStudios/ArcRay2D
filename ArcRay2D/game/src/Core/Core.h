#pragma once

#include <memory>

#ifdef DEBUG
	#if defined(_WIN32)
		#define ARC_DEBUGBREAK() __debugbreak()
	#elif defined (_GNU_SOURCE)
		#include <signal.h>
		#define ARC_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ARC_ENABLE_ASSERTS
#else
	#define ARC_DEBUGBREAK()
#endif

#define ARC_EXPAND_MACRO(x) x
#define ARC_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define ARC_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

#include <filesystem>
#ifdef ARC_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define ARC_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ARC##type##ERROR(msg, __VA_ARGS__); ARC_DEBUGBREAK(); } }
#define ARC_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ARC_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define ARC_INTERNAL_ASSERT_NO_MSG(type, check) ARC_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ARC_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define ARC_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define ARC_INTERNAL_ASSERT_GET_MACRO(...) ARC_EXPAND_MACRO( ARC_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ARC_INTERNAL_ASSERT_WITH_MSG, ARC_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define ARC_ASSERT(...) ARC_EXPAND_MACRO( ARC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define ARC_CORE_ASSERT(...) ARC_EXPAND_MACRO( ARC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define ARC_ASSERT(...)
#define ARC_CORE_ASSERT(...)
#endif