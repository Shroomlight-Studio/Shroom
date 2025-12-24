#pragma once

#include "Shroom/Core/Memory.h"

#include <spdlog/spdlog.h>

namespace Shroom {

	class Log {
	public:
		static void Init();
		static void Shutdown();

		inline static Shared<spdlog::logger>& GetCoreLogger() { return _CoreLogger; }
		inline static Shared<spdlog::logger>& GetClientLogger() { return _ClientLogger; }

	private:
		static Shared<spdlog::logger> _CoreLogger;
		static Shared<spdlog::logger> _ClientLogger;
	};

} // namespace Shroom

// Core log macros
#define SCORE_TRACE(...)	::Shroom::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SCORE_INFO(...)		::Shroom::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SCORE_WARN(...)		::Shroom::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SCORE_ERROR(...)	::Shroom::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SCORE_CRITICAL(...)	::Shroom::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define STRACE(...)			::Shroom::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SINFO(...)			::Shroom::Log::GetClientLogger()->info(__VA_ARGS__)
#define SWARN(...)			::Shroom::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SERROR(...)			::Shroom::Log::GetClientLogger()->error(__VA_ARGS__)
#define SCRITICAL(...)		::Shroom::Log::GetClientLogger()->critical(__VA_ARGS__)
