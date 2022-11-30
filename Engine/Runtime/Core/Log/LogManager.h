/***************************************************************************************
Author: lvke
Date:2022/9/18 01:19
Description:
The LogManager is implemented by spdlog
****************************************************************************************/
#pragma once

#include "spdlog/spdlog.h"
#include <cstdint>
#include <stdexcept>
#include "../Interface/SingletonInterface.h"

namespace Twinkle
{
	class LogManager 
	{
		FRIEND_SINGLETON(LogManager)
	public:
		enum LogLevel
		{
			debug,
			info,
			warn,
			error,
			fatal
		};
	private:
		LogManager();
		~LogManager();
		LogManager(const LogManager&) = delete;
		LogManager& operator=(const LogManager&) = delete;

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


	#define LOG_HELPER(LOG_LEVEL, ...) \
		Singleton<Twinkle::LogManager>::GetInstance().log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

	#define LOG_DEBUG(...) LOG_HELPER(Twinkle::LogManager::LogLevel::debug, __VA_ARGS__);

	#define LOG_INFO(...) LOG_HELPER(Twinkle::LogManager::LogLevel::info, __VA_ARGS__);

	#define LOG_WARN(...) LOG_HELPER(Twinkle::LogManager::LogLevel::warn, __VA_ARGS__);

	#define LOG_ERROR(...) LOG_HELPER(Twinkle::LogManager::LogLevel::error, __VA_ARGS__);

	#define LOG_FATAL(...) LOG_HELPER(Twinkle::LogManager::LogLevel::fatal, __VA_ARGS__);

}
