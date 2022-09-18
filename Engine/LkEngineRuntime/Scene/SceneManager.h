/***************************************************************************************
Author: lvke
Date:2022/9/18 12:26
Description:
SceneManager
****************************************************************************************/

#pragma once

#include "../Core/base/SingletonInterface.h"

#include <d3d11_1.h>
#include <wrl/client.h>

#include "TestComponent.h"

namespace LkEngine
{
	class SceneManager : public ISingleton<SceneManager>
	{
	public:
		void initialize(Microsoft::WRL::ComPtr<ID3D11Device> pd3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
		void updateScene(float deltaTime);
		void drawScene();
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };

		TestComponent testComponent;
	};
}