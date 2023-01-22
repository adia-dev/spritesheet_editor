//
// Created by abdoulayedia on 21.01.2023
//
#pragma once

#include "Tool.h"

namespace sse {
	// MoveTool
	class MoveTool: public Tool {
	  public:
		MoveTool(): Tool() {}
		MoveTool(std::shared_ptr<SpriteEntity>& entity): Tool(entity) {}
		MoveTool(std::shared_ptr<SpriteEntity>& entity, const std::string& name): Tool(entity, name) {}

		//  bool OnHandleEvents(sf::Event& event) override;

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
		float _currentSpeed = 0.0f;
		float _speed        = 1000.0f;
		bool  _snap         = false;
		float _snapSize     = 10.0f;
	};
} // namespace sse
