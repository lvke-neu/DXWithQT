#pragma once
/***************************************************************************************
Author: lvke
Date:2022/11/12 10:43
Description:
Manage the scene's light
****************************************************************************************/

/*
		     normal    camera pos
ambient        no          no
diffuse		   yes		   no
specular	   no          yes
*/

#include "../../Core/base/ManagerInterface.h"
#include "../../Core/base/SingletonInterface.h"

namespace LkEngine
{
	
	struct DirectionLight;
	class LightManager : public ISingleton<LightManager>, public IManager
	{
	public:
		virtual void init() override;
		virtual ~LightManager();
		void setDirLight(const DirectionLight& dirLight);
	private:
		ComPtr<ID3D11Buffer> m_pSceneDirLightCB;
	};
}