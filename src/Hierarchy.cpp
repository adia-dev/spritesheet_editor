//
// Created by abdoulayedia on 14.01.2023
//
#include "Hierarchy.h"

namespace sse {
	Hierarchy::Hierarchy() {}

	void Hierarchy::OnAttach() {}

	void Hierarchy::OnHandleSFMLEvent(sf::Event& event) {}

	void Hierarchy::OnUpdate(float dt) {}

	void Hierarchy::OnRenderUI() {
		ImGui::Begin("Hierarchy");

		ImGui::End();
	}
} // namespace sse