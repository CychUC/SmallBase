#include "menu.h"
#include <imgui/imgui.h>

namespace Small {
	void Menu::Init() {
		logger->LogInfo("Menu init!");
	}

	void Menu::Loop() {
		ImGui::SetNextWindowSize(ImVec2(320, 400), ImGuiCond_Once);

		if (ImGui::Begin("SmallBase")) {
			ImGui::Text("Hello, world!");
			if (ImGui::Button("Unload")) {
				global_running_ = false;
			}
		}
		ImGui::End();
	}
}