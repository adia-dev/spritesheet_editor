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

	void SpriteEntity::OnUpdate(float dt) {}

	void SpriteEntity::OnRender(sf::RenderTarget& target) {}

	void SpriteEntity::OnRenderProperties() {
		if (ImGui::TreeNode("Sprite Entity")) {
			{
				ImVec2 position(_sprite.getPosition().x, _sprite.getPosition().y);
				float  scale = _sprite.getScale().x;

				if (ImGui::SliderFloat("X", &position.x, -1000.f, 1000.f)) {
					_sprite.setPosition(position.x, _sprite.getPosition().y);
				}
				if (ImGui::SliderFloat("Y", &position.y, -1000.f, 1000.f)) {
					_sprite.setPosition(_sprite.getPosition().x, position.y);
				}

				ImGui::Separator();

				if (ImGui::SliderFloat("Scale", &scale, -1.f, 10.f)) {
					_sprite.setScale(scale, scale);
				}
			}
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
