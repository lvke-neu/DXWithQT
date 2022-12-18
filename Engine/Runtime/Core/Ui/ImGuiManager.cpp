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

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	IMGUI_IMPL_API LRESULT ImGuiManager::WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
	}
}


