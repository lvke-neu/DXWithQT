#include "ImGuiManager.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Runtime/Platform/Windows/RenderSystem.h"
#include "Runtime/Core/Serialization/SerializationManager.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Twinkle
{
	void ImGuiManager::Initialize(void* hwnd)
	{
		if (!Singleton<RenderSystem>::GetInstance().GetDevice() || !Singleton<RenderSystem>::GetInstance().GetDeviceContent())
			return;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigWindowsMoveFromTitleBarOnly = true;

		ImGui::StyleColorsDark();
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

		ImGui::ShowAboutWindow();
		ImGui::ShowDemoWindow();
		ImGui::ShowUserGuide();


		showSceneGameObjects();
		showSelectedGameObjectDetail();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	__int64 ImGuiManager::WndProcHandler(void* hwnd, unsigned int msg, unsigned __int64 wParam, __int64 lParam)
	{
		return ImGui_ImplWin32_WndProcHandler((HWND)hwnd, msg, wParam, lParam);
	}

	void ImGuiManager::setSceneGameObjects(const std::vector<IGameObject*>& sceneGameObjects)
	{
		m_sceneGameObjects = sceneGameObjects;
	}

	void ImGuiManager::showSceneGameObjects()
	{
		ImGui::Begin("Scene GameObject");

		static std::string selected{ "" };
		for (auto& go : m_sceneGameObjects)
		{
			if (ImGui::Selectable(go->getGuid().c_str(), selected == go->getGuid()))
			{
				m_currentSelectedGo = go;
				selected = go->getGuid();
			}
		}

		ImGui::End();
	}

	void ImGuiManager::showSelectedGameObjectDetail()
	{
		ImGui::Begin("GameObject Detail");
		if (!m_currentSelectedGo)
		{
			ImGui::End();
			return;
		}

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

		ImGui::End();
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


