#pragma once

#include "Shroom/Core/Core.h"
#include "Shroom/Core/Log.h"

#include <filesystem>

#ifdef SHROOM_ENABLE_ASSERTS
	#define SHROOM_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { SHROOM##type##ERROR(msg, __VA_ARGS__); SHROOM_DEBUGBREAK(); } }
	#define SHROOM_INTERNAL_ASSERT_WITH_MSG(type, check, ...) SHROOM_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define SHROOM_INTERNAL_ASSERT_NO_MSG(type, check) SHROOM_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SHROOM_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define SHROOM_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define SHROOM_INTERNAL_ASSERT_GET_MACRO(...) SHROOM_EXPAND_MACRO( SHROOM_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SHROOM_INTERNAL_ASSERT_WITH_MSG, SHROOM_INTERNAL_ASSERT_NO_MSG) )

	#define SASSERT(...) SHROOM_EXPAND_MACRO( SHROOM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define SCORE_ASSERT(...) SHROOM_EXPAND_MACRO( SHROOM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define SASSERT(...)
	#define SCORE_ASSERT(...)
#endif