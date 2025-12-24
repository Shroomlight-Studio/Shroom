#include "Log.h"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Shroom {

	Shared<spdlog::logger> Log::_CoreLogger;
	Shared<spdlog::logger> Log::_ClientLogger;

	void Log::Init() {
		// thread pool
		
		constexpr size_t QUEUE_SIZE = 8192;
		constexpr size_t THREAD_COUNT = 1;

		spdlog::init_thread_pool(QUEUE_SIZE, THREAD_COUNT);

		// sinks

		auto consoleSink = Share<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S] %n: %v%$");
		auto fileSink = Share<spdlog::sinks::basic_file_sink_mt>("Codi.log", true);
		fileSink->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%l] %n: %v%$");

		std::vector<spdlog::sink_ptr> sinks{ consoleSink, fileSink };

		// loggers

		_CoreLogger = Share<spdlog::async_logger>(
			"CODI",
			sinks.begin(),
			sinks.end(),
			spdlog::thread_pool(),
			spdlog::async_overflow_policy::block
		);
		_ClientLogger = Share<spdlog::async_logger>(
			"APP",
			sinks.begin(),
			sinks.end(),
			spdlog::thread_pool(),
			spdlog::async_overflow_policy::block
		);

		_CoreLogger->set_level(spdlog::level::trace);
		_ClientLogger->set_level(spdlog::level::trace);

		spdlog::register_logger(_CoreLogger);
		spdlog::register_logger(_ClientLogger);
	}

	void Log::Shutdown() {
		spdlog::shutdown();

		_CoreLogger.reset();
		_ClientLogger.reset();
	}

} // namespace Shroom
