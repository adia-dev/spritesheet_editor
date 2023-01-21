//
// Created by abdoulayedia on 14.01.2023
//
#pragma once

#include "Visitor.h"
#include "constants.h"

namespace sse {

	class Visitor;

	// Entity
	class Entity {
	  public:
		Entity()          = default;
		virtual ~Entity() = default;

		virtual void Accept(Visitor& v) const = 0;
		virtual void OnAwake() {}
		virtual void OnDestroy() {}

		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() {}
		virtual void OnRender(sf::RenderTarget& target) {}
		virtual void OnRenderProperties() {}

		virtual bool IsHovered(const sf::Vector2f mousePos) const { return _bounds.contains(mousePos); }

		virtual void SetPosition(const sf::Vector2f position) { _position = position; }
		virtual void SetScale(const sf::Vector2f scale) { _scale = scale; }
		virtual void SetRotation(const float rotation) { _rotation = rotation; }

		virtual sf::Vector2f GetPosition() const { return _position; }
		virtual sf::Vector2f GetScale() const { return _scale; }
		virtual float        GetRotation() const { return _rotation; }

		virtual void          SetBounds(const sf::FloatRect bounds) { _bounds = bounds; }
		virtual sf::FloatRect GetBounds() const { return _bounds; }

	  protected:
		sf::Vector2f  _position;
		sf::Vector2f  _scale;
		float         _rotation;
		sf::FloatRect _bounds;
	};
} // namespace sse
