//
// Created by abdoulayedia on 22.01.2023
//
#include "ExtractTool.h"

#include "Application.h"
#include "ImageHandler.h"

namespace sse {
	void ExtractTool::OnDetach() {
		_selectionRect.width  = 0;
		_selectionRect.height = 0;
	}

	void ExtractTool::OnMouseMove() {
		if (!Toolbox::GetWorkspaceRect().contains(Input::GetMousePosition())) return;

		if (Input::IsMouseButtonDown(sf::Mouse::Left)) {
			_selectionRect.width  = Application::WorldToRenderTarget(Input::GetMousePosition()).x - _selectionRect.left;
			_selectionRect.height = Application::WorldToRenderTarget(Input::GetMousePosition()).y - _selectionRect.top;
		}

		if (_selectionRect.width > 0 && _selectionRect.height > 0) {
			for (auto& entity : Toolbox::GetSelectedEntities()) {
				if (entity->GetBounds().intersects(_selectionRect)) {
					// I want to draw a rectangle that is the intersection of the entity and the selection rectangle
					sf::FloatRect area       = Maths::IntersectedArea(entity->GetBounds(), _selectionRect);
					auto          frameRects = ImageHandler::ExtractFrames(
                        AssetManager::GetTexture("../assets/images/spritesheets/goku/ssjg.png"),
                        sf::IntRect(area.left - entity->GetPosition().x,
                                    area.top - entity->GetPosition().y,
                                    area.width,
                                    area.height));

					std::vector<Frame> frames;
					int                i = 0;
					for (auto& frameRect : frameRects) {
						frameRect.left += _selectionRect.left;
						frameRect.top += _selectionRect.top;
						frames.emplace_back(Frame(frameRect, "Frame_" + std::to_string(i++)));
					}
					Application::GetSpriteEntity()->SetFrames(frames);
				}
			}
		}
	}

	void ExtractTool::OnMouseLeave() {
		SelectionTool::OnMouseLeave();
	}

	void ExtractTool::OnMouseEnter() {
		SelectionTool::OnMouseEnter();
	}

	void ExtractTool::OnMouseButtonUp(sf::Mouse::Button button) {
		SelectionTool::OnMouseButtonUp(button);
	}

	void ExtractTool::OnMouseButtonDown(sf::Mouse::Button button) {
		if (!Toolbox::GetWorkspaceRect().contains(Input::GetMousePosition())) return;

		if (button == sf::Mouse::Left) {
			_selectionRect.left   = Application::WorldToRenderTarget(Input::GetMousePosition()).x;
			_selectionRect.top    = Application::WorldToRenderTarget(Input::GetMousePosition()).y;
			_selectionRect.width  = 0;
			_selectionRect.height = 0;
		}
	}

	void ExtractTool::OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {
		SelectionTool::OnMouseWheelScroll(event);
	}

	void ExtractTool::OnKeyDown(sf::Keyboard::Key key) {
		SelectionTool::OnKeyDown(key);
	}

	void ExtractTool::OnKeyUp(sf::Keyboard::Key key) {
		SelectionTool::OnKeyUp(key);
	}

	void ExtractTool::OnRender(sf::RenderTarget& target) {
		if (_selectionRect.width == 0 || _selectionRect.height == 0) return;

		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(1);
		rect.setPosition(_selectionRect.left, _selectionRect.top);
		rect.setSize(sf::Vector2f(_selectionRect.width, _selectionRect.height));
		target.draw(rect);

		sf::RectangleShape intersectRect;
		intersectRect.setFillColor(sf::Color(0, 0, 255, 100));
		intersectRect.setOutlineColor(sf::Color::Red);
		intersectRect.setOutlineThickness(1);

		for (auto entity : Toolbox::GetSelectedEntities()) {
			if (entity->GetBounds().intersects(_selectionRect)) {
				// I want to draw a rectangle that is the intersection of the entity and the selection rectangle
				sf::FloatRect area = Maths::IntersectedArea(entity->GetBounds(), _selectionRect);
				if (area.width == 0 || area.height == 0) continue;
				intersectRect.setPosition(area.left, area.top);
				intersectRect.setSize(sf::Vector2f(area.width, area.height));

				target.draw(intersectRect);
			}
		}
	}

	void ExtractTool::OnUpdate(float dt) {
		for (auto entity : Toolbox::GetSelectedEntities())
			if (entity->IsHovered(Application::WorldToRenderTarget(Input::GetMousePosition()))) entity->OnHover();
	}
} // namespace sse