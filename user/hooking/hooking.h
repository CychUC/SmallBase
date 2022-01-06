#pragma once
#include <common.h>

#include <detours/detours.h>

namespace Small {
	struct Hooks {
		static HRESULT HookPresent(IDXGISwapChain* this_, UINT sync_, UINT flags_);
		static LRESULT HookWndProc(HWND hwnd_, UINT msg_, WPARAM wparam_, LPARAM lparam_);
	};

	class Hooking {
		friend Hooks;
	public:
		explicit Hooking();
		~Hooking();
		void AddHook(PVOID* original_function, PVOID detour_function, std::string hook_name);
		void ApplyHooks();
		void RemoveHooks();

	public:
		ID3DPresent original_present_{};
		WNDPROC original_wndproc_{};
	private:
		std::vector<std::tuple<std::string, PVOID*, PVOID>> hooks_;
	};
	inline Hooking* hooking{};
}