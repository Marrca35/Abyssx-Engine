#pragma once

#include <spdlog/logger.h>

namespace walnut {
	class Logger {
	public:
		static void Init();
		static void Destroy();
	private:
		Logger() = delete;
	private:
		static spdlog::logger log;
	};
}

