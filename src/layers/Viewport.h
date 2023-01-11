//
// Created by abdoulayedia on 09.01.2023
//
#pragma once

#include "constants.h"
#include "layers/Layer.h"

namespace sse {
	// Viewport
	class Viewport: public Layer {
	  public:
		Viewport()  = default;
		~Viewport() = default;

		void OnHandleSFMLEvent(sf::Event& event) override;
		void OnUpdate(float dt) override;
		void OnRenderUI() override;

	  private:
		ImRect _viewportRect;

		sf::RenderTexture _renderTexture;
		sf::View          _view;
		float             _cellSize   = 25.f;
		float             _zoom       = 1.f;
		float             _targetZoom = 1.f;
		float             _zoomSpeed  = 2.f;

		float smoothstep(float edge0, float edge1, float x);
		float lerp(float left, float right, float x);

		void
		RenderGrid(sf::RenderTarget& target, float cellSize = 25.f, sf::Color color = sf::Color(111, 111, 111, 111));
	};
} // namespace sse
