#include "ImGuiManager.h"

#include "Runtime/Platform/Windows/RenderSystem.h"
#include "Runtime/Scene/Camera/CameraController.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"
#include "Runtime/Core/Serialization/SerializationManager.h"
#include "Runtime/Core/Engine/Engine.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Twinkle
{
	void ImGuiManager::Initialize(void* hwnd)
	{
		if (!Singleton<RenderSystem>::GetInstance().GetDevice() || !Singleton<RenderSystem>::GetInstance().GetDeviceContent())
			return;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		//io.ConfigViewportsNoDefaultParent = true;
		//io.ConfigDockingAlwaysTabBar = true;
		//io.ConfigDockingTransparentPayload = true;
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}


		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(Singleton<RenderSystem>::GetInstance().GetDevice(), Singleton<RenderSystem>::GetInstance().GetDeviceContent());
	}

	void ImGuiManager::Destroy()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiManager::Tick()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		static std::string fps = "";
		static std::string deltaTime = "";
		static float sumDeltaTime = 0.0f;
		sumDeltaTime += Singleton<Engine>::GetInstance().GetDeltaTime();

		if (sumDeltaTime > 1.0f)
		{
			fps = std::to_string((uint32_t)(1 / Singleton<Engine>::GetInstance().GetDeltaTime()));
			deltaTime = std::to_string(Singleton<Engine>::GetInstance().GetDeltaTime());
			sumDeltaTime = 0.0f;
		}

		ImGui::ShowAboutWindow();
		ImGui::ShowDemoWindow();
		ImGui::ShowUserGuide();

		showMenuBar();
		bool b = true;
		ImGui::Begin("Scene Property", &b);
		ImGui::Text(("FPS:" + fps + ", DeltaTime:" + deltaTime).c_str());
		showCamera();
		showSceneGameObjects();
		ImGui::End();


		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	__int64 ImGuiManager::WndProcHandler(void* hwnd, unsigned int msg, unsigned __int64 wParam, __int64 lParam)
	{
		return ImGui_ImplWin32_WndProcHandler((HWND)hwnd, msg, wParam, lParam);
	}

	void ImGuiManager::setSceneGameObjects(const std::vector<IGameObject*>& sceneGameObjects)
	{
		m_sceneGameObjects = sceneGameObjects;
	}

	void ImGuiManager::showMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{
				
				}
				if (ImGui::MenuItem("Save")) 
				{

				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void ImGuiManager::showCamera()
	{
		if (ImGui::TreeNode("Camera"))
		{
			if (ImGui::TreeNode("Transform")) {
				float scale[3];
				float rotation[3];
				float position[3];
				scale[0] = { Singleton<PerspectiveCamera>::GetInstance().getTransform().getScale().x };
				scale[1] = {  Singleton<PerspectiveCamera>::GetInstance().getTransform().getScale().y };
				scale[2] = {  Singleton<PerspectiveCamera>::GetInstance().getTransform().getScale().z };

				rotation[0] = { Singleton<PerspectiveCamera>::GetInstance().getTransform().getRotation().x };
				rotation[1] = { Singleton<PerspectiveCamera>::GetInstance().getTransform().getRotation().y };
				rotation[2] = { Singleton<PerspectiveCamera>::GetInstance().getTransform().getRotation().z };

				position[0] = {  Singleton<PerspectiveCamera>::GetInstance().getTransform().getPosition().x };
				position[1] = {  Singleton<PerspectiveCamera>::GetInstance().getTransform().getPosition().y };
				position[2] = {  Singleton<PerspectiveCamera>::GetInstance().getTransform().getPosition().z };

				ImGui::DragFloat3("Scale", scale, 0.1f, -9999.0f, 9999.0f);
				ImGui::DragFloat3("Rotation", rotation, 0.1f, -9999.0f, 9999.0f);
				ImGui::DragFloat3("Position", position, 0.1f, -9999.0f, 9999.0f);
				ImGui::TreePop();

				Singleton<PerspectiveCamera>::GetInstance().setTransform(Transform({ scale[0], scale[1], scale[2] }, { rotation[0], rotation[1], rotation[2] }, { position[0], position[1], position[2] }));
			}
			float moveSpeed = Singleton<CameraController>::GetInstance().getMoveSpeed();
			ImGui::InputFloat("Move Speed", &moveSpeed);
			Singleton<CameraController>::GetInstance().setMoveSpeed(moveSpeed);

			ImGui::TreePop();
		}
	}

	void ImGuiManager::showSceneGameObjects()
	{
		if (ImGui::TreeNode("Scene GameObject")) 
		{
			//static std::string selected{ "" };
			//for (auto& go : m_sceneGameObjects)
			//{
			//	if (ImGui::Selectable(go->getGuid().c_str(), selected == go->getGuid()))
			//	{
			//		m_currentSelectedGo = go;

			//		selected = go->getGuid();
			//	}
			//}


			for (auto& go : m_sceneGameObjects)
			{
				if (ImGui::TreeNode(go->getGuid().c_str()))
				{
					m_currentSelectedGo = go;
					rttr::type type = rttr::type::get_by_name(m_currentSelectedGo->getType());
					for (auto& prop : type.get_properties())
					{
						if (prop.get_type().get_name().to_string() == "TransformComponent" ||
							prop.get_type().get_name().to_string() == "TransformComponent*")
						{
							showTransformComponent();
						}
						if (prop.get_type().get_name().to_string() == "MeshComponent" ||
							prop.get_type().get_name().to_string() == "MeshComponent*")
						{
							showMeshComponent();
						}
					}
					ImGui::TreePop();
				}
			}



			ImGui::TreePop();
		}
	}

	void ImGuiManager::showTransformComponent()
	{
		if (!m_currentSelectedGo)
			return;
		if (ImGui::TreeNode("TransformComponent")) {
			if (ImGui::TreeNode("Transform")) {
				float scale[3];
				float rotation[3];
				float position[3];
				scale[0] = { m_currentSelectedGo->getTransformComponent()->getTransform().getScale().x };
				scale[1] = { m_currentSelectedGo->getTransformComponent()->getTransform().getScale().y };
				scale[2] = { m_currentSelectedGo->getTransformComponent()->getTransform().getScale().z };

				rotation[0] = { m_currentSelectedGo->getTransformComponent()->getTransform().getRotation().x };
				rotation[1] = { m_currentSelectedGo->getTransformComponent()->getTransform().getRotation().y };
				rotation[2] = { m_currentSelectedGo->getTransformComponent()->getTransform().getRotation().z };

				position[0] = { m_currentSelectedGo->getTransformComponent()->getTransform().getPosition().x };
				position[1] = { m_currentSelectedGo->getTransformComponent()->getTransform().getPosition().y };
				position[2] = { m_currentSelectedGo->getTransformComponent()->getTransform().getPosition().z };

				ImGui::DragFloat3("Scale", scale, 0.1f, -9999.0f, 9999.0f);
				ImGui::DragFloat3("Rotation", rotation, 0.1f, -9999.0f, 9999.0f);
				ImGui::DragFloat3("Position", position, 0.1f, -9999.0f, 9999.0f);
				ImGui::TreePop();

				m_currentSelectedGo->getTransformComponent()->setTransform(Transform({ scale[0], scale[1], scale[2] }, { rotation[0], rotation[1], rotation[2] }, { position[0], position[1], position[2] }));
			}
			ImGui::TreePop();
		}
	}

	void ImGuiManager::showMeshComponent()
	{
		if (!m_currentSelectedGo)
			return;
		if (ImGui::TreeNode("MeshComponent")) {

			char bufVsShaderPath[256] = "";
			char bufPsShaderPath[256] = "";
			char bufTexturePath[256] = "";
			memcpy_s(bufVsShaderPath, sizeof(bufVsShaderPath), m_currentSelectedGo->getMeshComponent()->getVsShader().c_str(), m_currentSelectedGo->getMeshComponent()->getVsShader().size());
			memcpy_s(bufPsShaderPath, sizeof(bufVsShaderPath), m_currentSelectedGo->getMeshComponent()->getPsShader().c_str(), m_currentSelectedGo->getMeshComponent()->getPsShader().size());
			memcpy_s(bufTexturePath, sizeof(bufVsShaderPath), m_currentSelectedGo->getMeshComponent()->getTexture().c_str(), m_currentSelectedGo->getMeshComponent()->getTexture().size());

			ImGui::InputText("VsShaderPath", bufVsShaderPath, IM_ARRAYSIZE(bufVsShaderPath));
			ImGui::InputText("PsShaderPath", bufPsShaderPath, IM_ARRAYSIZE(bufPsShaderPath));
			ImGui::InputText("TexturePath", bufTexturePath, IM_ARRAYSIZE(bufTexturePath));
			ImGui::TreePop();

			m_currentSelectedGo->getMeshComponent()->setVsShader(bufVsShaderPath);
			m_currentSelectedGo->getMeshComponent()->setPsShader(bufPsShaderPath);
			m_currentSelectedGo->getMeshComponent()->setTexture(bufTexturePath);
		}
	}
}


