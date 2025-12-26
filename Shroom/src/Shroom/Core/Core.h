#pragma once

#include "Shroom/Core/PlatformDetection.h"

#include "Shroom/Core/Types.h"

#include "Shroom/Core/Memory.h"

#if defined(CODI_DEBUG)
	#if defined(CODI_PLATFORM_WINDOWS)
		#define CODI_DEBUGBREAK() __debugbreak()
	#else
		#define CODI_DEBUGBREAK() __builtin_trap()
	#endif

	#define CODI_ENABLE_ASSERTS
#else
	#define CODI_DEBUGBREAK()
#endif // CODI_DEBUG

#define CODI_EXPAND_MACRO(x) x
#define CODI_STRINGIFY_MACRO(x) #x

#define BIT(x) 1 << x

#define CODI_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "Shroom/Core/Asserts.h"
