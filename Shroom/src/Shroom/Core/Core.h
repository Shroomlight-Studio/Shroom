#pragma once

#include "Shroom/Core/PlatformDetection.h"

#include "Shroom/Core/Types.h"

#include "Shroom/Core/Memory.h"

#if defined(SHROOM_DEBUG)
	#if defined(SHROOM_PLATFORM_WINDOWS)
		#define SHROOM_DEBUGBREAK() __debugbreak()
	#else
		#define SHROOM_DEBUGBREAK() __builtin_trap()
	#endif

	#define SHROOM_ENABLE_ASSERTS
#else
	#define SHROOM_DEBUGBREAK()
#endif // SHROOM_DEBUG

#define SHROOM_EXPAND_MACRO(x) x
#define SHROOM_STRINGIFY_MACRO(x) #x

#define BIT(x) 1 << x

#define SHROOM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "Shroom/Core/Asserts.h"
