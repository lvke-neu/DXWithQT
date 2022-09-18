/***************************************************************************************
Author: lvke
Date:2022/9/18 01:19
Description:
The LogManager is implemented by spdlog
****************************************************************************************/

#pragma once
#include "../base/SingletonInterface.h"

#include "spdlog/spdlog.h"

#include <cstdint>
#include <stdexcept>

namespace LkEngine
{
	class LogManager : public ISingleton<LogManager>
	{
	public:
		enum LogLevel
		{
			debug,
			info,
			warn,
			error,
			fatal
		};
	public:
		LogManager();
		~LogManager();

	public:
		template<typename... TARGS>
		void log(LogLevel level, TARGS&&... args)
		{
			switch (level)
			{
			case LogLevel::debug:
				m_logger->debug(std::forward<TARGS>(args)...);
				break;
			case LogLevel::info:
				m_logger->info(std::forward<TARGS>(args)...);
				break;
			case LogLevel::warn:
				m_logger->warn(std::forward<TARGS>(args)...);
				break;
			case LogLevel::error:
				m_logger->error(std::forward<TARGS>(args)...);
				break;
			case LogLevel::fatal:
				m_logger->critical(std::forward<TARGS>(args)...);
				fatalCallback(std::forward<TARGS>(args)...);
				break;
			default:
				break;
			}
		}
		template<typename... TARGS>
		void fatalCallback(TARGS&&... args)
		{
			const std::string format_str = fmt::format(std::forward<TARGS>(args)...);
			throw std::runtime_error(format_str);
		}

	private:
		std::shared_ptr<spdlog::logger> m_logger;

	};
}
