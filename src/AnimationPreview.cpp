//
// Created by abdoulayedia on 28.01.2023
//
#include "AnimationPreview.h"

namespace sse {
	AnimationPreview::AnimationPreview() {}
	void AnimationPreview::OnAttach() {
		auto spriteEntity = Application::GetSpriteEntity();

		if (spriteEntity == nullptr || spriteEntity->GetSprite().getTexture() == nullptr) return;

		_sprite.setTexture(*spriteEntity->GetSprite().getTexture());
	}
	bool AnimationPreview::OnHandleEvents(sf::Event& event) {
		return false;
	}
	void AnimationPreview::OnUpdate(float dt) {
		auto spriteEntity = Application::GetSpriteEntity();

		if (spriteEntity == nullptr || !spriteEntity->HasFrames()) return;

		_timer += dt;

		if (_timer >= _delay) {
			_currentIndex = (_currentIndex + 1) % spriteEntity->GetFrames().size();
			_sprite.setTextureRect(spriteEntity->GetFrame(_currentIndex).Rect);
			_sprite.setOrigin(_sprite.getGlobalBounds().width / 2.f, 0.f);
			_timer = 0.f;
		}
	}
	void AnimationPreview::OnRenderUI() {
		ImGui::Begin("Animation Preview");

		ImGui::SliderFloat("Delay", &_delay, 0.1f, 5.f);
		ImGui::SliderFloat("Scale", &_scaleFactor, 0.1f, 5.f);

		auto spriteEntity = Application::GetSpriteEntity();
		if (spriteEntity == nullptr || !spriteEntity->HasFrames()) {
			ImGui::End();
			return;
		}

		ImVec2 animationPreviewSize = ImGui::GetContentRegionAvail();
		_animationPreviewRect       = ImRect(ImGui::GetCursorScreenPos(),
                                       ImVec2(ImGui::GetCursorScreenPos().x + animationPreviewSize.x,
                                              ImGui::GetCursorScreenPos().y + animationPreviewSize.y));

		_renderTexture.clear(sf::Color::Transparent);
		_renderTexture.create(animationPreviewSize.x, animationPreviewSize.y);

		_sprite.setPosition(animationPreviewSize.x / 2.f, animationPreviewSize.y / 2.f);
		_sprite.setScale(_scaleFactor, _scaleFactor);
		_renderTexture.draw(_sprite);

		ImGui::Image(_renderTexture);

		ImGui::End();
	}
} // namespace sse