#include "ImGuiManager.h"

#include "Runtime/Platform/Windows/RenderSystem.h"
#include "Runtime/Scene/Camera/CameraController.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"
#include "Runtime/Core/Serialization/SerializationManager.h"
#include "Runtime/Core/Engine/Engine.h"
#include "Runtime/Platform/Windows/RenderSystem.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Twinkle
{
	void ImGuiManager::Initialize(void* hwnd)
	{
		if (!Singleton<RenderSystem>::GetInstance().GetDevice() || !Singleton<RenderSystem>::GetInstance().GetDeviceContent())
			return;

		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		////io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		////io.ConfigViewportsNoAutoMerge = true;
		////io.ConfigViewportsNoTaskBarIcon = true;
		////io.ConfigViewportsNoDefaultParent = true;
		////io.ConfigDockingAlwaysTabBar = true;
		////io.ConfigDockingTransparentPayload = true;
		////io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
		////io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

		//// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		////ImGui::StyleColorsClassic();

		//// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		//ImGuiStyle& style = ImGui::GetStyle();
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	style.WindowRounding = 0.0f;
		//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		//}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO&    io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigDockingAlwaysTabBar = true;
		io.ConfigWindowsMoveFromTitleBarOnly = true;


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

		showDockSpace();
		
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

	void ImGuiManager::showDockSpace()
	{
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		static bool b_open = true;
		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &b_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					Singleton<Engine>::GetInstance().ShutDown();
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		//draw dock window
		showScenePropertyWindow();

		//render widnow
		ImGui::Begin("render widow", &b_open);
		//ImGui::Image(Singleton<Engine>::GetInstance().m_pOutputTextureSRV, ImVec2{256, 256});
		ImGui::End();

		//demo window
		ImGui::ShowDemoWindow();
		

		ImGui::End();

	}

	void ImGuiManager::showScenePropertyWindow()
	{
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

		static bool b = true;
		ImGui::Begin("Scene Property", &b);

		ImGui::Text(("FPS:" + fps + ", DeltaTime:" + deltaTime).c_str());
		showCamera();
		showGameObjects();

		ImGui::End();
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

	void ImGuiManager::showGameObjects()
	{
		if (ImGui::TreeNode("Scene GameObject")) 
		{
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


