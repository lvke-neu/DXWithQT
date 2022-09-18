//copy from pilot engine

#pragma once

#include <type_traits>


namespace LkEngine
{

	template<typename T>
	class ISingleton
	{
	protected:
		ISingleton() = default;

	public:
		static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
		{
			static T instance;
			return instance;
		}
		virtual ~ISingleton() noexcept = default;
		ISingleton(const ISingleton&) = delete;
		ISingleton& operator=(const ISingleton&) = delete;
	};
}
