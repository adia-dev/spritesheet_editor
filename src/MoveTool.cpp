//
// Created by abdoulayedia on 21.01.2023
//
#include "MoveTool.h"

namespace sse {

	void MoveTool::OnMouseDown(const sf::Vector2f mousePos) {
		Tool::OnMouseDown(mousePos);

		ImGui::GetIO().MouseDrawCursor = true;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	void MoveTool::OnMouseUp(const sf::Vector2f mousePos) {
		Tool::OnMouseUp(mousePos);

		ImGui::GetIO().MouseDrawCursor = false;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
	}

	void MoveTool::OnMouseMove(const sf::Vector2f mousePos) {
		Tool::OnMouseMove(mousePos);
	}

	void MoveTool::OnRender(sf::RenderTarget& target) {}

	void MoveTool::OnUpdate(float dt) {
		if (_entity == nullptr) return;
	}

} // namespace sse