/***************************************************************************************
Author: lvke
Date:2022/11/28 21:56
Description:
Serialization Manager
****************************************************************************************/
#pragma once

#include "../Interface/SingletonInterface.h"
#include "DataStream.h"

namespace Twinkle
{
	class SerializationManager
	{
		FRIEND_SINGLETON(SerializationManager);
	public:
		template<class T>
		void Serialize(const T& t_In, DataStream& dataStream_Out);

		template<class T>
		void UnSerialize(DataStream& dataStream_In, T& t_Out);
	};


	template<class T>
	void SerializationManager::Serialize(const T& t_In, DataStream& dataStream_Out)
	{
		dataStream_Out << t_In;
	}

	template<class T>
	void SerializationManager::UnSerialize(DataStream& dataStream_In, T& t_Out)
	{
		dataStream_In >> t_Out;
	}
}
