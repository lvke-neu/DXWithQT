/************************************************************************
Author: lvke
Date:2022/11/05 21:57
Description:
Pick Detection(Component in Scene)
************************************************************************/
#pragma once

#include "../../Core/base/SingletonInterface.h"
#include <string>
#include <map>

namespace LkEngine
{
	class IComponent;
	class PickDetection : public ISingleton<PickDetection>
	{
	public:
		std::string pickDetect(uint16_t mouseX, uint16_t mouseY, const std::map<std::string, IComponent*>& componets);

	};

}