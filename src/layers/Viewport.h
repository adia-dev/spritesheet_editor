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
		sf::Sprite        _sprite;
		sf::Texture       _texture;
		float             _cellSize = 25.f;

		// View
		sf::View     _view;
		sf::Vector2f _viewMousePos;
		float        _viewSpeed           = 0.5f;
		float        _zoom                = 1.f;
		float        _targetZoom          = 1.f;
		float        _zoomSpeed           = 2.f;
		float        _zoomDeltaMultiplier = 0.5f;

		sf::Vector2f _desiredViewCenter = {-1.f, -1.f};

		bool _snapMovement = false;
		bool _snapZoom     = false;
		bool _showGrid     = true;

		// Events
		bool          _isLeftMousePressed = false;
		sf::Vector2f  _leftMouseButtonPressedStartPos;
		sf::FloatRect _selectionRect;

		float smoothstep(float edge0, float edge1, float x);
		float lerp(float left, float right, float x);

		template<typename T>
		inline sf::Vector2<T> lerp(sf::Vector2<T> left, sf::Vector2<T> right, float x) {
			return sf::Vector2<T>(lerp(left.x, right.x, x), lerp(left.y, right.y, x));
		}

		void
		RenderGrid(sf::RenderTarget& target, float cellSize = 25.f, sf::Color color = sf::Color(111, 111, 111, 111));

		template<typename Callback>
		inline static void RenderOverlay(Callback&& callback) {
			static int       location     = 0;
			static bool      visible      = true;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
			                                ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
			                                ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

			if (location >= 0) {
				const float          PAD       = 10.0f;
				const ImGuiViewport* viewport  = ImGui::GetMainViewport();
				ImVec2               work_pos  = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
				ImVec2               work_size = viewport->WorkSize;
				ImVec2               window_pos, window_pos_pivot;
				window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
				window_pos.y =
				    (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD + ImGui::GetFrameHeight());
				window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
				window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
				ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
				ImGui::SetNextWindowViewport(viewport->ID);
				window_flags |= ImGuiWindowFlags_NoMove;
			} else if (location == -2) {
				// Center window
				ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
				window_flags |= ImGuiWindowFlags_NoMove;
			}
			ImGui::SetNextWindowBgAlpha(0.75f); // Transparent background
			if (ImGui::Begin("Overlay", &visible, window_flags)) {
				callback(visible, location);
			}
			ImGui::End();
		}
		void RenderSelection();
	};
} // namespace sse
