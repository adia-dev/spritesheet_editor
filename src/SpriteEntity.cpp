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

	std::vector<Frame>& SpriteEntity::GetFrames() {
		return _frames;
	}

	Frame& SpriteEntity::GetFrame(int pos) {
		if (pos < 0 || pos >= _frames.size())
			throw std::out_of_range("No frame were found at this pos: " + std::to_string(pos));

		return _frames[pos];
	}

	void SpriteEntity::SetFrames(const std::vector<Frame>& frames) {
		_frames = frames;
	}

	void SpriteEntity::AddFrame(const Frame& frame) {
		_frames.push_back(frame);
	}

	void SpriteEntity::AddFrame(const Frame& frame, int pos) {
		if (pos < 0 || pos >= _frames.size())
			throw std::out_of_range("Cannot add a frame at the position: " + std::to_string(pos));

		_frames.emplace(_frames.begin() + pos, frame);
	}

	void SpriteEntity::RemoveFrame(int pos) {
		if (pos < 0 || pos >= _frames.size())
			throw std::out_of_range("No frame were found at this pos: " + std::to_string(pos));

		_frames.erase(_frames.begin() + pos);
	}

	void SpriteEntity::RemoveFrame(const Frame& frame) {
		std::remove_if(_frames.begin(), _frames.end(), [&](const Frame& f) { return f == frame; });
	}

	void SpriteEntity::SwapFrames(int lhs, int rhs) {
		if ((lhs < 0 || lhs >= _frames.size()) || (rhs < 0 || rhs >= _frames.size()))
			throw std::out_of_range("Could not swap the frames because the given positions were incorrect: (" +
			                        std::to_string(lhs) + ", " + std::to_string(rhs) + ")");

		auto temp    = _frames[lhs];
		_frames[lhs] = _frames[rhs];
		_frames[rhs] = temp;
	}
} // namespace sse
