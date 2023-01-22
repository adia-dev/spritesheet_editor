//
// Created by abdoulayedia on 09.01.2023
//
#pragma once

#include "Layer.h"
#include "constants.h"

namespace sse {
	// Viewport
	class Viewport: public Layer {
	  public:
		// Viewport() = default;
		Viewport(sf::RenderTexture& renderTexture): _renderTexture(renderTexture) {}
		~Viewport() = default;

		void OnAttach() override;
		bool OnHandleSFMLEvent(sf::Event& event) override;
		void OnUpdate(float dt) override;
		void OnRenderUI() override;

	  private:
		// Viewport
		ImRect _viewportRect;

		// Rendering
		sf::RenderTexture& _renderTexture;
		sf::Texture        _texture;
		float              _cellSize = 25.f;

		// View
		sf::View     _view;
		sf::Vector2f _viewportMousePos;
		sf::Vector2f _viewMousePos;

		// Camera movement and zoom
		float _viewSpeed           = 500.f;
		float _zoom                = 1.f;
		float _targetZoom          = 1.f;
		float _zoomSpeed           = 2.f;
		float _zoomDeltaMultiplier = 0.5f;

		bool _snapMovement = false;
		bool _snapZoom     = false;
		bool _showGrid     = true;
		bool _showDebug    = false;

		// Events
		sf::FloatRect _selectionRect;

		float smoothstep(float edge0, float edge1, float x);
		float lerp(float left, float right, float x);

		template<typename T>
		inline sf::Vector2<T> lerp(sf::Vector2<T> left, sf::Vector2<T> right, float x) {
			return sf::Vector2<T>(lerp(left.x, right.x, x), lerp(left.y, right.y, x));
		}

		void RenderViewport();
		void RenderDebug();
		void RenderToolbox();
		void RenderGrid(sf::RenderTarget& target, float cellSize = 25.f, sf::Color color = sf::Color::White);
		void RenderSelection();

		template<typename Callback>
		static void RenderOverlay(Callback&& callback, const char* id = "Overlay");
	};
} // namespace sse
