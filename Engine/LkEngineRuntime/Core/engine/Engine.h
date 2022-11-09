/***************************************************************************************
Author: lvke
Date:2022/9/18 11:00
Description:
The Engine is responsible for initializing D3D and building the process of TICK
****************************************************************************************/

#pragma once

#include <d3d11_1.h>
#include <wrl/client.h>
#include "../base/SingletonInterface.h"
#include "../Event/InputEventManager.h"
#include "../Event/FrameMoveEventManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Component/Camera/CameraManager.h"

namespace LkEngine
{
	using namespace Microsoft::WRL;
	class Engine : public ISingleton<Engine>
	{
	public:
		Engine();
		~Engine();
	public:
		void initialize(HWND hInstance, UINT windowWidth, UINT windowHeight);
		void updateScene(float deltaTime);
		void drawScene();
		void onResize(UINT windowWidth, UINT windowHeight);
	public:
		void onKeyPress(const Keys& key) { InputEventManager::getInstance().onKeyPress(key); if (!m_isKeyDown[key]) m_isKeyDown[key] = true;}
		void onKeyRelease(const Keys& key){ InputEventManager::getInstance().onKeyRelease(key); if (m_isKeyDown[key])m_isKeyDown[key] = false;}
		void onMousePress(const MouseState& mouseState) { InputEventManager::getInstance().onMousePress(mouseState); m_bIsMousePress[mouseState.mouseType] = true; }
		void onMouseRelease(const MouseState& mouseState) { InputEventManager::getInstance().onMouseRelease(mouseState); m_bIsMousePress[mouseState.mouseType] = false;}
		void onMouseMove(const MouseState& mouseState) { InputEventManager::getInstance().onMouseMove(mouseState); m_mousePos = mouseState.mousePos;}
		void onMouseWheelEvent(const MouseState& mouseState) { InputEventManager::getInstance().onMouseWheelEvent(mouseState); }
	public:
		std::string getSkyBoxTexture() { return SceneManager::getInstance().getSkyBoxTexture(); }
		void setSkyBoxTexture(const std::string& skyBoxTexture) { SceneManager::getInstance().setSkyBoxTexture(skyBoxTexture); }
		void setWireFrame(bool b) { SceneManager::getInstance().setWireFrame(b); }
		void addComponent(const std::string& componentType, const std::string& modelPath = "") { SceneManager::getInstance().addComponent(componentType, modelPath); }
		void deleteComponent(const std::string& uuid) { SceneManager::getInstance().deleteComponent(uuid); }
		void openSolution(const std::string& filePath) { SceneManager::getInstance().openSolution(filePath); }
		void saveSolution(const std::string& filePath) { SceneManager::getInstance().saveSolution(filePath); }
		void setCameraMoveSpeed(float moveSpeed) { SceneManager::getInstance().setCameraMoveSpeed(moveSpeed); }
		void resetScene() { SceneManager::getInstance().deleteAllComponent(); }
		UINT getTriangleCount() { return SceneManager::getInstance().getTriangleCount(); }
		void setAxisLength(float length) { SceneManager::getInstance().setAxisLength(length); }
		void setMoveScaleCoefficient(float scaleCoefficient) { SceneManager::getInstance().setMoveScaleCoefficient(scaleCoefficient); }

		Transform getCameraTransform() { return CameraManager::getInstance().getTransform(); }
		void setCameraTransform(const Transform& transform) { CameraManager::getInstance().setTransform(transform); }
		void getCameraFrustum(float& FovAngleY, float& AspectRatio, float& NearZ, float& FarZ) { CameraManager::getInstance().getFrustum(FovAngleY, AspectRatio, NearZ, FarZ); }
		void setCameraFrustum(float FovAngleY, float AspectRatio, float NearZ, float FarZ) { CameraManager::getInstance().setFrustum(FovAngleY, AspectRatio, NearZ, FarZ); }
		
		MousePos getCursorPos() { return m_mousePos; }
		bool isMousePress(MouseType mt) { return m_bIsMousePress[mt]; }
		void setMousePress(MouseType mt, bool b) { m_bIsMousePress[mt] = b; }
		bool isKeyPress(Keys key) { return m_isKeyDown[key]; }
	private:
		HWND m_hInstance;
		UINT m_windowWidth;
		UINT m_windowHeight;

		UINT      m_4xMsaaQuality;

		ComPtr<ID3D11Device> m_pd3dDevice { nullptr };
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext { nullptr };
		ComPtr<IDXGISwapChain> m_pSwapChain { nullptr };

		ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer { nullptr };
		ComPtr<ID3D11RenderTargetView> m_pRenderTargetView { nullptr };
		ComPtr<ID3D11DepthStencilView> m_pDepthStencilView { nullptr };

		D3D11_VIEWPORT m_ScreenViewport;

		MousePos m_mousePos;
		std::map<MouseType, bool> m_bIsMousePress;
		std::map<Keys, bool> m_isKeyDown;
	};
}