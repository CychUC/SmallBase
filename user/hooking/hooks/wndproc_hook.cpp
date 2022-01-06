#include <common.h>
#include <hooking/hooking.h>
#include <menu/menu.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Small {
	LRESULT Hooks::HookWndProc(HWND hwnd_, UINT msg_, WPARAM wparam_, LPARAM lparam_) {

		if (msg_ == WM_KEYUP && wparam_ == VK_INSERT)
		{
			menu.opened_ = !menu.opened_;
		}

		if (menu.opened_)
		{
			ImGui_ImplWin32_WndProcHandler(hwnd_, msg_, wparam_, lparam_);
			return true;
		}

		return CallWindowProc(hooking->original_wndproc_, hwnd_, msg_, wparam_, lparam_);
	}
}