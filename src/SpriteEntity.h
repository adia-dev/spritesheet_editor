//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include "Entity.h"

namespace sse {
	// SpriteEntity
	class SpriteEntity: public Entity {
	  public:
		SpriteEntity()  = default;
		~SpriteEntity() = default;

		virtual void Accept(Visitor& v) const = 0;

	  private:
		sf::Sprite   _sprite;
		sf::Texture* _texture;
	};
} // namespace sse
