//
// Created by abdoulayedia on 22.01.2023
//
#pragma once

#include "Tool.h"

namespace sse {
	// SelectionTool
	class SelectionTool: public Tool {
	  public:
		SelectionTool(): Tool() {}
		SelectionTool(std::shared_ptr<SpriteEntity>& entity): Tool(entity) {}
		SelectionTool(std::shared_ptr<SpriteEntity>& entity, const std::string& name): Tool(entity, name) {}

		// void OnAttach() override;
		void OnDetach() override;

		virtual void OnMouseMove() override;
		virtual void OnMouseLeave() override;
		virtual void OnMouseEnter() override;

		virtual void OnMouseButtonUp(sf::Mouse::Button button) override;
		virtual void OnMouseButtonDown(sf::Mouse::Button button) override;
		virtual void OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) override;

		virtual void OnKeyDown(sf::Keyboard::Key key) override;
		virtual void OnKeyUp(sf::Keyboard::Key key) override;

		virtual void OnRender(sf::RenderTarget& target) override;
		virtual void OnUpdate(float dt) override;

	  protected:
		sf::FloatRect _selectionRect;
	};
} // namespace sse
