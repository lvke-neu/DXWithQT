/***************************************************************************************
Author: lvke
Date:2022/12/18 14:47
Description:
ImGui Manager
****************************************************************************************/
#pragma once
#include "Runtime/Interface/SingletonInterface.h"
#include <vector>
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Runtime/Platform/Windows/RenderSystem.h"

namespace Twinkle
{
	class IGameObject;
	class ImGuiManager
	{
		FRIEND_SINGLETON(ImGuiManager);
		PRIVATE_CONSTRUCTOR(ImGuiManager);
	public:
		void Initialize(void* hwnd);
		void Destroy();
		void Tick();
		__int64 WndProcHandler(void* hwnd, unsigned int msg, unsigned __int64 wParam, __int64 lParam);

		void setSceneGameObjects(const std::vector<IGameObject*>& sceneGameObjects);

		void Begin();
		void End();
		void ResizeRenderWindow();
	private:
		void showDockSpace();
		void showScenePropertyWindow();
		void showCamera();
		void showGameObjects();
		void showTransformComponent();
		void showMeshComponent();
	private:
		IGameObject* m_currentSelectedGo{ nullptr };
		std::vector<IGameObject*> m_sceneGameObjects;


		ID3D11ShaderResourceView*	m_pOutputTextureSRV{ nullptr };
		ID3D11DepthStencilView*		m_pOutputTextureDSV{ nullptr };
		ID3D11RenderTargetView*		m_pOutputTextureRTV{ nullptr };
		D3D11_VIEWPORT						m_OutputViewPort;

		ID3D11RenderTargetView*	m_pCacheRTV{ nullptr };
		ID3D11DepthStencilView*	m_pCacheDSV{ nullptr };
		D3D11_VIEWPORT						m_CacheViewPort;

		bool								m_GenerateMips = false;
		bool								m_ShadowMap = false;

		ImVec2 m_renderWindowViewPort{ 0,0 };
	};
}