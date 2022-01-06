#include <common.h>
#include <hooking/hooking.h>
#include <menu/menu.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

namespace Small {
	bool once = false;
	HRESULT Hooks::HookPresent(IDXGISwapChain* this_, UINT sync_, UINT flags_) {
		if (!menu.initialized_) {
			renderer->swapchain_ = this_;
			this_->GetDevice(__uuidof(ID3D11Device), (void**)&renderer->device_);
			renderer->device_->GetImmediateContext(&renderer->context_);

			DXGI_SWAP_CHAIN_DESC description;

			this_->GetDesc(&description);

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			renderer->window_ = description.OutputWindow;

			ImGui_ImplWin32_Init(renderer->window_);
			ImGui_ImplDX11_Init(renderer->device_, renderer->context_);
			ImGui::GetIO().ImeWindowHandle = renderer->window_;

			ID3D11Texture2D* back_buffer;

			this_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
			renderer->device_->CreateRenderTargetView(back_buffer, NULL, &renderer->target_view_);
			back_buffer->Release();

			menu.Init();

			hooking->original_wndproc_ = (WNDPROC)SetWindowLongPtr(renderer->window_, GWLP_WNDPROC, (LONG_PTR)HookWndProc);

			menu.initialized_ = true;
		}

		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX11_NewFrame();

		ImGui::NewFrame();

		if (menu.opened_)
		{
			menu.Loop();
		}
		ImGui::EndFrame();

		ImGui::Render();

		renderer->context_->OMSetRenderTargets(1, &renderer->target_view_, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return hooking->original_present_(this_, sync_, flags_);
	}
}