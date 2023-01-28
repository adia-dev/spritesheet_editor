//
// Created by abdoulayedia on 22.01.2023
//
#include "SelectionTool.h"

#include "Application.h"

namespace sse {

	void SelectionTool::OnMouseMove() {
		if (!Toolbox::GetWorkspaceRect().contains(Input::GetMousePosition())) return;

		if (Input::IsMouseButtonDown(sf::Mouse::Left)) {
			_selectionRect.width  = Application::WorldToRenderTarget(Input::GetMousePosition()).x - _selectionRect.left;
			_selectionRect.height = Application::WorldToRenderTarget(Input::GetMousePosition()).y - _selectionRect.top;

			auto entities = Application::GetEntities();
			Toolbox::ClearSelectedEntities();
			std::copy_if(
			    entities.begin(),
			    entities.end(),
			    std::back_inserter(Toolbox::GetSelectedEntities()),
			    [&](std::shared_ptr<Entity> entity) { return _selectionRect.intersects(entity->GetBounds()); });
		}
	}

	void SelectionTool::OnMouseLeave() {}

	void SelectionTool::OnMouseEnter() {}

	void SelectionTool::OnMouseButtonDown(sf::Mouse::Button button) {
		if (!Toolbox::GetWorkspaceRect().contains(Input::GetMousePosition())) return;

		if (button == sf::Mouse::Left) {
			_selectionRect.left   = Application::WorldToRenderTarget(Input::GetMousePosition()).x;
			_selectionRect.top    = Application::WorldToRenderTarget(Input::GetMousePosition()).y;
			_selectionRect.width  = 0;
			_selectionRect.height = 0;
		}
	}

	void SelectionTool::OnMouseButtonUp(sf::Mouse::Button button) {}

	void SelectionTool::OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {}

	void SelectionTool::OnKeyDown(sf::Keyboard::Key key) {}

	void SelectionTool::OnKeyUp(sf::Keyboard::Key key) {}

	void SelectionTool::OnRender(sf::RenderTarget& target) {
		if (_selectionRect.width == 0 || _selectionRect.height == 0) return;

		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(1);
		rect.setPosition(_selectionRect.left, _selectionRect.top);
		rect.setSize(sf::Vector2f(_selectionRect.width, _selectionRect.height));
		target.draw(rect);
	}

	void SelectionTool::OnUpdate(float dt) {
		for (auto entity : Toolbox::GetSelectedEntities())
			if (entity->IsHovered(Application::WorldToRenderTarget(Input::GetMousePosition()))) entity->OnHover();
	}
} // namespace sse