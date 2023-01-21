//
// Created by abdoulayedia on 21.01.2023
//
#pragma once

#include "Tool.h"

namespace sse {
	// MoveTool
	class MoveTool: public Tool {
	  public:
		MoveTool() = default;
		MoveTool(std::shared_ptr<SpriteEntity>& entity): Tool(entity) {}

		// virtual bool HandleSFMLEvent(sf::Event& event) override;

		virtual void OnMouseDown() override;
		virtual void OnMouseUp() override;
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

	  private:
		sf::Vector2f _desiredMoveDirection = sf::Vector2f(0.0f, 0.0f);
		float        _currentSpeed         = 0.0f;
		float        _speed                = 1000.0f;
		bool         _snap                 = false;
		float        _snapSize             = 10.0f;
	};
} // namespace sse
