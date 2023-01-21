//
// Created by abdoulayedia on 21.01.2023
//
#include "SelectTool.h"

namespace sse {
	void SelectTool::OnMouseDown(const sf::Vector2f mousePos) {
		Tool::OnMouseDown(mousePos);
	}
	void SelectTool::OnMouseUp(const sf::Vector2f mousePos) {
		Tool::OnMouseUp(mousePos);
	}
	void SelectTool::OnMouseMove(const sf::Vector2f mousePos) {
		Tool::OnMouseMove(mousePos);
	}
	void SelectTool::OnRender(sf::RenderTarget& target) {
		if (_entity != nullptr && _isMouseDown) {
			_selectionRect.setPosition(_mouseDownPos);
			_selectionRect.setSize(sf::Vector2f(_mousePos.x - _mouseDownPos.x, _mousePos.y - _mouseDownPos.y));
			_selectionRect.setFillColor(sf::Color::Transparent);
			_selectionRect.setOutlineColor(sf::Color::Red);
			_selectionRect.setOutlineThickness(2);
			target.draw(_selectionRect);
		}
	}
	void SelectTool::OnUpdate(float dt) {}
} // namespace sse