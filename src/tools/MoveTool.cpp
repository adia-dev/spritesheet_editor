//
// Created by abdoulayedia on 21.01.2023
//
#include "MoveTool.h"

#include "Application.h"

namespace sse {

	void MoveTool::OnMouseDown() {}

	void MoveTool::OnMouseUp() {}

	void MoveTool::OnMouseLeave() {}

	void MoveTool::OnMouseMove() {}

	void MoveTool::OnMouseEnter() {}

	void MoveTool::OnMouseButtonUp(sf::Mouse::Button button) {}

	void MoveTool::OnMouseButtonDown(sf::Mouse::Button button) {}

	void MoveTool::OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {}

	void MoveTool::OnKeyDown(sf::Keyboard::Key key) {}

	void MoveTool::OnKeyUp(sf::Keyboard::Key key) {}

	void MoveTool::OnRender(sf::RenderTarget& target) {
		if (_entity == nullptr) return;

		if (_entity->IsHovered(Application::WorldToRenderTexture(Input::GetMousePosition()))) {
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(_entity->GetWidth(), _entity->GetHeight()));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::Yellow);
			rect.setOutlineThickness(2.0f);
			rect.setPosition(_entity->GetPosition());
			target.draw(rect);
		}
	}

	void MoveTool::OnUpdate(float dt) {
		if (_entity == nullptr || !_workspaceRect.contains(Input::GetMousePosition())) return;

		float targetSpeed = Maths::Magnitude(Input::GetDirection()) * _speed;

		_currentSpeed = Maths::Lerp(_currentSpeed, targetSpeed, 100.f * dt);

		_entity->Move(Input::GetDirection() * _currentSpeed * dt);

		if (_entity->IsHovered(Application::WorldToRenderTexture(Input::GetMousePosition()))) {
			if (Input::IsMouseButtonDown(sf::Mouse::Left)) {
				_entity->Move(Input::GetMouseDelta() * _entity->GetScale().x);
			}
		}
	}

} // namespace sse