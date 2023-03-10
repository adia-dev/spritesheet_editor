//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include "Entity.h"
#include "Frame.h"

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

		void OnAwake() override;
		void OnUpdate(float dt) override;
		void OnRender(sf::RenderTarget& target) override;
		void OnHover() override;
		void OnRenderProperties() override;

		sf::Sprite& GetSprite();
		void        SetSprite(const sf::Sprite& sprite);

		sf::Texture& GetTexture();
		sf::Texture& GetOriginalTexture();
		void         SetTexture(const sf::Texture& texture);

		void Move(const sf::Vector2f delta) override;

		// Frame management
		std::vector<Frame>& GetFrames();
		Frame&              GetFrame(int pos);
		void                SetFrames(const std::vector<Frame>& frames);
		void                AddFrame(const Frame& frame);
		void                AddFrame(const Frame& frame, int pos);
		void                RemoveFrame(int pos);
		void                RemoveFrame(const Frame& frame);
		void                SwapFrames(int lhs, int rhs);

		bool HasFrames() const { return _frames.size() > 0; }

	  private:
		sf::Sprite  _sprite;
		sf::Texture _texture;
		sf::Texture _originalTexture;

		std::vector<Frame> _frames;
		ImColor            _colorToReplace = ImColor(1.f, 1.f, 1.f, 1.f);
		ImColor            _newColor       = ImColor(0.f, 0.f, 0.f, 0.f);
		Frame*             _currentFrame   = nullptr;

		// Frame management
		void OnRenderFrames(sf::RenderTarget& target);

	  public:
		void Accept(Visitor& v) const override { v.Visit(this); }
	};
} // namespace sse
