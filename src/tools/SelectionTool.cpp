//
// Created by abdoulayedia on 22.01.2023
//
#include "SelectionTool.h"

#include "Application.h"

namespace sse {

	void SelectionTool::OnMouseMove() {
		if (_entity == nullptr) return;

		if (Input::IsMouseButtonDown(sf::Mouse::Left)) {
			_selectionRect.width = Application::WorldToRenderTexture(Input::GetMousePosition()).x - _selectionRect.left;
			_selectionRect.height = Application::WorldToRenderTexture(Input::GetMousePosition()).y - _selectionRect.top;

			if (_selectionRect.width < 0) {
				_selectionRect.left += _selectionRect.width;
				_selectionRect.width = -_selectionRect.width;
			}

			if (_selectionRect.height < 0) {
				_selectionRect.top += _selectionRect.height;
				_selectionRect.height = -_selectionRect.height;
			}
		}
	}

	void SelectionTool::OnMouseLeave() {}

	void SelectionTool::OnMouseEnter() {}

	void SelectionTool::OnMouseButtonDown(sf::Mouse::Button button) {
		if (_entity == nullptr) return;

		if (button == sf::Mouse::Left) {
			_selectionRect.left   = Application::WorldToRenderTexture(Input::GetMousePosition()).x;
			_selectionRect.top    = Application::WorldToRenderTexture(Input::GetMousePosition()).y;
			_selectionRect.width  = 0;
			_selectionRect.height = 0;
		}
	}

	void SelectionTool::OnMouseButtonUp(sf::Mouse::Button button) {
		if (_entity == nullptr) return;
	}

	void SelectionTool::OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {}

	void SelectionTool::OnKeyDown(sf::Keyboard::Key key) {}

	void SelectionTool::OnKeyUp(sf::Keyboard::Key key) {}

	void SelectionTool::OnRender(sf::RenderTarget& target) {
		if (_entity == nullptr || _selectionRect.width == 0 || _selectionRect.height == 0) return;

		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(1);
		rect.setPosition(_selectionRect.left, _selectionRect.top);
		rect.setSize(sf::Vector2f(_selectionRect.width, _selectionRect.height));
		target.draw(rect);
	}

	void SelectionTool::OnUpdate(float dt) {
		if (_entity == nullptr) return;
	}
} // namespace sse