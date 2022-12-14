#include "GameObjectInterface.h"
#include <Windows.h>
#include "Runtime/Utility/Utility.h"

namespace Twinkle
{
	IGameObject::IGameObject()
	{
		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		m_guid = guidStr;
	}

	IGameObject::~IGameObject()
	{
		SAFE_DELETE_SETNULL(m_transformComponent);
		SAFE_DELETE_SETNULL(m_meshComponent);
	}

	std::string IGameObject::getGuid() const
	{
		return m_guid;
	}

	TransformComponent * IGameObject::getTransformComponent() const
	{
		return m_transformComponent;
	}

	MeshComponent * IGameObject::getMeshComponent() const
	{
		return m_meshComponent;
	}
}