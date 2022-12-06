/***************************************************************************************
Author: lvke
Date:2022/11/28 21:48
Description:
Singleton template
****************************************************************************************/
#pragma once

namespace Twinkle
{
	template<typename T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}
	private:
		Singleton() = default;
		virtual ~Singleton() noexcept = default;
		Singleton(const Singleton&) = default;
		Singleton& operator=(const Singleton&) = default;
	};

#define FRIEND_SINGLETON(T) \
	friend class Singleton<T>;

#define PRIVATE_CONSTRUCTOR(T) \
	private: \
		T() = default; \
		virtual ~T() = default; \
		T(const T&) = default; \
		T& operator=(const T&) = default;

}
