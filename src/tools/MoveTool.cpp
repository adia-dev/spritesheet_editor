//
// Created by abdoulayedia on 21.01.2023
//
#include "MoveTool.h"

#include "Application.h"

namespace sse {

	void MoveTool::OnMouseLeave() {}

	void MoveTool::OnMouseMove() {}

	void MoveTool::OnMouseEnter() {}

	void MoveTool::OnMouseButtonUp(sf::Mouse::Button button) {}

	void MoveTool::OnMouseButtonDown(sf::Mouse::Button button) {}

	void MoveTool::OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {}

	void MoveTool::OnKeyDown(sf::Keyboard::Key key) {}

	void MoveTool::OnKeyUp(sf::Keyboard::Key key) {}

	void MoveTool::OnRender(sf::RenderTarget& target) {
		sf::RectangleShape rect;

		for (auto entity : Toolbox::GetSelectedEntities()) {
			bool hovered = entity->IsHovered(Application::WorldToRenderTarget(Input::GetMousePosition()));
			rect.setSize(sf::Vector2f(entity->GetWidth(), entity->GetHeight()));
			rect.setFillColor(hovered ? sf::Color(0, 0, 0, 100) : sf::Color::Transparent);
			rect.setOutlineColor(hovered ? sf::Color::Yellow : sf::Color::Red);
			rect.setOutlineThickness(2.0f);
			rect.setPosition(entity->GetPosition());
			target.draw(rect);
		}
	}

	void MoveTool::OnUpdate(float dt) {
		if (!Toolbox::GetWorkspaceRect().contains(Input::GetMousePosition())) return;

		float targetSpeed = Maths::Magnitude(Input::GetDirection()) * _speed;

		_currentSpeed = Maths::Lerp(_currentSpeed, targetSpeed, 100.f * dt);

		for (auto entity : Toolbox::GetSelectedEntities()) entity->Move(Input::GetDirection() * _currentSpeed * dt);

		for (auto entity : Toolbox::GetSelectedEntities()) {
			if (entity->IsHovered(Application::WorldToRenderTarget(Input::GetMousePosition()))) {
				if (Input::IsMouseButtonDown(sf::Mouse::Left)) {
					entity->Move(Input::GetMouseDelta() * entity->GetScale().x);
				}
			}
		}
	}

} // namespace sse