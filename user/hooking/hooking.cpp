#include "hooking.h"

namespace Small {
	Hooking::Hooking() {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		hooking = this;
	}

	Hooking::~Hooking() {
		SetWindowLongPtr(renderer->window_, GWLP_WNDPROC, (LONG_PTR)this->original_wndproc_);
		hooking = nullptr;
	}

	void Hooking::AddHook(PVOID* original_function, PVOID detour_function, std::string hook_name) {
		this->hooks_.push_back(std::tuple<std::string, PVOID*, PVOID>(hook_name, original_function, detour_function));
	}

	void Hooking::ApplyHooks() {
		for (auto const& hook : this->hooks_) {
			std::ostringstream oss;
			oss << "Applying hook: " << std::get<0>(hook) << std::endl;
			logger->LogInfo(oss.str());

			DetourAttach(std::get<1>(hook), std::get<2>(hook));
		}
		DetourTransactionCommit();
	}

	void Hooking::RemoveHooks() {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		for (auto const& hook : this->hooks_) {
			std::ostringstream oss;
			oss << "Restoring hook: " << std::get<0>(hook) << std::endl;
			logger->LogInfo(oss.str());

			DetourDetach(std::get<1>(hook), std::get<2>(hook));
		}
		DetourTransactionCommit();
	}
}