#include "main.h"



void Origins::UpdateWindow(bool *open) {
	ImGuiWindowFlags WindowFlags = 0;
	WindowFlags |= ImGuiWindowFlags_MenuBar;
	WindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::Begin("Origins datapacks", open, WindowFlags);

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Load...")) {
				// TODO
			}

			if (ImGui::MenuItem("Save...")) {
				// TODO
			}

			if (ImGui::MenuItem("Save as...")) {
				// TODO
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("TODO");

	ImGui::End();
}

