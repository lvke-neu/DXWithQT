#include "ImGuiManager.h"
#include "Runtime/Platform/Windows/RenderSystem.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Twinkle
{
	void ImGuiManager::Initialize(void* hwnd)
	{
		//Destroy();

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

		ImGui::Begin("trans");
		static float trans1[3];
		static float trans2[3];
		static float trans3[3];
		ImGui::Text("Scale:    ");
		ImGui::SameLine();
		ImGui::DragFloat3("1", trans1, 0.01f, 0.0f, 10.0f);
		ImGui::Text("Rotation: ");
		ImGui::SameLine();
		ImGui::DragFloat3("2", trans2, 0.01f, 0.0f, 10.0f);
		ImGui::Text("Position: ");
		ImGui::SameLine();
		ImGui::DragFloat3("3", trans3, 0.01f, 0.0f, 10.0f);
		//ImGui::SliderFloat3("slider float3", trans, 0.0f, 1.0f);
		ImGui::End();


		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	IMGUI_IMPL_API LRESULT ImGuiManager::WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
	}
}


