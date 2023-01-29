//
// Created by abdoulayedia on 28.01.2023
//
#pragma once

#include "Application.h"
#include "Input.h"
#include "Layer.h"

namespace sse {
	// AnimationPreview
	class AnimationPreview: public Layer {
	  public:
		AnimationPreview();
		~AnimationPreview() override = default;

		void OnAttach() override;
		bool OnHandleEvents(sf::Event& event) override;
		void OnUpdate(float dt) override;
		void OnRenderUI() override;

	  private:
		sf::Sprite        _sprite;
		sf::RenderTexture _renderTexture;
		ImRect            _animationPreviewRect;
		float             _scaleFactor = 1.f;

		int   _currentIndex = 0;
		float _delay        = 0.1f;
		float _timer        = 0.f;
		bool  _reverse      = false;
	};
} // namespace sse
