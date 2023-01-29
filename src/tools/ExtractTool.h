//
// Created by abdoulayedia on 22.01.2023
//
#pragma once

#include "Tool.h"
#include "tools/SelectionTool.h"

namespace sse {
	// ExtractTool
	class ExtractTool: public SelectionTool {
	  public:
		ExtractTool(): SelectionTool() {}
		ExtractTool(std::shared_ptr<SpriteEntity>& entity): SelectionTool(entity) {}
		ExtractTool(std::shared_ptr<SpriteEntity>& entity, const std::string& name): SelectionTool(entity, name) {}

		//  bool OnHandleEvents(sf::Event& event) override;

		void OnDetach() override;

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
	};
} // namespace sse
