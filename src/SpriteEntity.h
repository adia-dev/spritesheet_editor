//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include "Entity.h"

#include <filesystem>

namespace sse {
	// SpriteEntity
	class SpriteEntity: public Entity {
	  public:
		SpriteEntity() = default;
		SpriteEntity(const std::filesystem::path& path);
		SpriteEntity(sf::Sprite& sprite);
		SpriteEntity(sf::Texture& texture);
		~SpriteEntity() = default;

		void OnUpdate(float dt) override;
		void OnRender(sf::RenderTarget& target) override;
		void OnRenderProperties() override;

		sf::Sprite& GetSprite();
		void        SetSprite(const sf::Sprite& sprite);

		sf::Texture& GetTexture();
		void         SetTexture(const sf::Texture& texture);

	  private:
		sf::Sprite  _sprite;
		sf::Texture _texture;

	  public:
		void Accept(Visitor& v) const override { v.Visit(this); }
	};
} // namespace sse
