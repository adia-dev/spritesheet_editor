//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include "Input.h"
#include "SpriteEntity.h"
#include "constants.h"

namespace sse {
	// Tool
	class Tool {
	  public:
		Tool(): _entity(nullptr) {}
		Tool(std::shared_ptr<SpriteEntity>& entity) { _entity = entity; }
		virtual ~Tool() = default;

		virtual bool HandleSFMLEvent(sf::Event& event);

		virtual void OnMouseDown() {}
		virtual void OnMouseUp() {}
		virtual void OnMouseMove() {}
		virtual void OnMouseLeave() {}
		virtual void OnMouseEnter() {}

		virtual void OnMouseButtonUp(sf::Mouse::Button button) {}
		virtual void OnMouseButtonDown(sf::Mouse::Button button) {}
		virtual void OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {}

		virtual void OnKeyDown(sf::Keyboard::Key key) {}
		virtual void OnKeyUp(sf::Keyboard::Key key) {}

		virtual void OnRender(sf::RenderTarget& target) = 0;
		virtual void OnUpdate(float dt) {}

		void SetEntity(std::shared_ptr<SpriteEntity>& entity) { _entity = entity; }

	  protected:
		std::shared_ptr<SpriteEntity> _entity;
		bool                          _canInteract = false;
	};
} // namespace sse
