//
// Created by abdoulayedia on 15.01.2023
//
#include "SpriteEntity.h"

#include "Application.h"

namespace sse {

	SpriteEntity::SpriteEntity(const std::filesystem::path& path) {
		_texture = AssetManager::GetTexture(path);
	}

	SpriteEntity::SpriteEntity(sf::Sprite& sprite): _sprite(sprite) {
		const sf::Texture* spriteTex = _sprite.getTexture();
		if (spriteTex != nullptr) _texture = *spriteTex;
	}

	SpriteEntity::SpriteEntity(sf::Texture& texture): _texture(texture) {
		_sprite.setTexture(_texture);
	}

	void SpriteEntity::Accept(Visitor& v) const {
		v.Visit(this);
	}

	void SpriteEntity::OnUpdate(float dt) {}

	void SpriteEntity::OnRender(sf::RenderTarget& target) {}

	void SpriteEntity::OnRenderProperties() {
		if (ImGui::TreeNode("Sprite Entity")) {
			ImGui::Text("eheh");
			ImGui::TreePop();
		}
	}

	sf::Sprite& SpriteEntity::GetSprite() {
		return _sprite;
	}

	void SpriteEntity::SetSprite(const sf::Sprite& sprite) {
		_sprite = sprite;

		const sf::Texture* spriteTex = sprite.getTexture();
		if (spriteTex != nullptr) _texture = *spriteTex;
	}

	sf::Texture& SpriteEntity::GetTexture() {
		return _texture;
	}

	void SpriteEntity::SetTexture(const sf::Texture& texture) {
		_texture = texture;
		_sprite.setTexture(_texture);
	}
} // namespace sse
