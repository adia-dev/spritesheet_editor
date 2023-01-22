//
// Created by abdoulayedia on 22.01.2023
//
#pragma once

#include "Tool.h"

namespace sse {
	// SelectionTool
	class SelectionTool: public Tool {
	  public:
		SelectionTool() = default;
		SelectionTool(std::shared_ptr<SpriteEntity>& entity): Tool(entity) {}
		SelectionTool(std::shared_ptr<SpriteEntity>& entity, const std::string& name): Tool(entity, name) {}

		// void OnAttach() override;
		// void OnDetach() override;

		void OnMouseMove() override;
		void OnMouseLeave() override;
		void OnMouseEnter() override;

		void OnMouseButtonUp(sf::Mouse::Button button) override;
		void OnMouseButtonDown(sf::Mouse::Button button) override;
		void OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) override;

		void OnKeyDown(sf::Keyboard::Key key) override;
		void OnKeyUp(sf::Keyboard::Key key) override;

		void OnRender(sf::RenderTarget& target) override;
		void OnUpdate(float dt) override;

	  private:
		sf::FloatRect _selectionRect;
	};
} // namespace sse
