#pragma once

#include <common.h>
#include <d3d11.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")

namespace Small {
	typedef HRESULT(__stdcall* ID3DPresent)(IDXGISwapChain* this_, UINT sync_, UINT flags_);
	class Renderer {
	public:
		explicit Renderer();
		~Renderer();
		bool GetSwapchain(IDXGISwapChain** swapchain, ID3D11Device** device);
		ID3DPresent GetPresent();
	public:
		static inline IDXGISwapChain* swapchain_;
		static inline HWND window_;
		static inline ID3D11Device* device_;
		static inline ID3D11DeviceContext* context_;
		static inline ID3D11RenderTargetView* target_view_;
	private:
		const D3D_DRIVER_TYPE kDriverType[4] = { D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP };
	};
	inline Renderer* renderer{};
}