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

	  protected:
		sf::Vector2f _position;
		sf::Vector2f _scale;
		float        _rotation;
	};
} // namespace sse
