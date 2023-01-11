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

		void OnAttach() override;
		void OnHandleSFMLEvent(sf::Event& event) override;
		void OnUpdate(float dt) override;
		void OnRenderUI() override;

	  private:
		// Viewport
		ImRect _viewportRect;

		// Rendering
		sf::RenderTexture _renderTexture;
		float             _cellSize = 25.f;

		// View
		sf::View     _view;
		float        _viewSpeed         = 0.5f;
		float        _zoom              = 1.f;
		float        _targetZoom        = 1.f;
		float        _zoomSpeed         = 2.f;
		sf::Vector2f _desiredViewCenter = {-1.f, -1.f};

		// Events
		bool         _isLeftMousePressed = false;
		sf::Vector2f _leftMouseButtonPressedStartPos;

		float smoothstep(float edge0, float edge1, float x);
		float lerp(float left, float right, float x);

		template<typename T>
		inline sf::Vector2<T> lerp(sf::Vector2<T> left, sf::Vector2<T> right, float x) {
			return sf::Vector2<T>(lerp(left.x, right.x, x), lerp(left.y, right.y, x));
		}

		void
		RenderGrid(sf::RenderTarget& target, float cellSize = 25.f, sf::Color color = sf::Color(111, 111, 111, 111));

		void RenderOverlay();
	};
} // namespace sse
