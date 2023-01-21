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

		virtual void OnMouseDown(const sf::Vector2f mousePos) {
			_mouseDownPos = mousePos;
			_isMouseDown  = true;
		}
		virtual void OnMouseUp(const sf::Vector2f mousePos) {
			_mouseUpPos  = mousePos;
			_isMouseDown = false;
			_canInteract = false;
		}
		virtual void OnMouseMove(const sf::Vector2f mousePos) {
			_lastMousePos = _mousePos;
			_mousePos     = mousePos;
			_mouseDelta   = _mousePos - _lastMousePos;
		}
		virtual void OnRender(sf::RenderTarget& target) = 0;
		virtual void OnUpdate(float dt) {}

		void SetEntity(std::shared_ptr<SpriteEntity>& entity) { _entity = entity; }

	  protected:
		std::shared_ptr<SpriteEntity> _entity;
		sf::Vector2f                  _mousePos, _mouseDownPos, _mouseUpPos;
		sf::Vector2f                  _lastMousePos, _mouseDelta;
		bool                          _isMouseDown = false;
		bool                          _canInteract = false;
	};
} // namespace sse
