//
// Created by abdoulayedia on 14.01.2023
//
#include "Hierarchy.h"

#include "Application.h"

namespace sse {
	Hierarchy::Hierarchy() {}

	void Hierarchy::OnAttach() {}

	bool Hierarchy::OnHandleSFMLEvent(sf::Event& event) {
		return false;
	}

	void Hierarchy::OnUpdate(float dt) {}

	void Hierarchy::OnRenderUI() {
		ImGui::Begin("Hierarchy");
		auto entities = Application::GetEntities();

		for (auto& entity : entities) entity->OnRenderProperties();

		ImGui::End();
	}
} // namespace sse