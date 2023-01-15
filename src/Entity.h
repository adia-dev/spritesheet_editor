//
// Created by abdoulayedia on 14.01.2023
//
#pragma once

#include "constants.h"

namespace sse {

	class Visitor;

	// Entity
	class Entity {
	  public:
		Entity()          = default;
		virtual ~Entity() = default;

		virtual void Accept(Visitor& v) const = 0;

	  protected:
		sf::Vector2f _position;
		sf::Vector2f _scale;
		float        _rotation;
	};
} // namespace sse
