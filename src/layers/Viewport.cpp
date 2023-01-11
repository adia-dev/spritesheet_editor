//
// Created by abdoulayedia on 09.01.2023
//
#include "Viewport.h"

#include "Application.h"

namespace sse {
	void Viewport::OnHandleSFMLEvent(sf::Event& event) {
		ImVec2 mousePos = Application::GetMousePos();

		if (_viewportRect.Contains(mousePos)) {
			if (event.type == sf::Event::MouseWheelScrolled) {
				std::cout << "Mouse Delta: \n"
				          << " - x: " << event.mouseWheelScroll.x << ", y: " << event.mouseWheelScroll.y << std::endl;
				_view.setCenter(_view.getCenter() + sf::Vector2f(event.mouseWheelScroll.delta * 10, 0));
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::Up) {
					_cellSize = std::min(100.f, _cellSize + 5.f);
				}
				if (event.key.code == sf::Keyboard::F2 || event.key.code == sf::Keyboard::Down) {
					_cellSize = std::max(5.f, _cellSize - 5.f);
				}
			}
		}
	}

	void Viewport::OnUpdate(float dt) {
		// std::cout << "Update from the viewport: " << dt << std::endl;
		_zoom = smoothstep(_zoom, _targetZoom, _zoomSpeed * dt);
	}
	void Viewport::OnRenderUI() {
		ImGui::Begin("Viewport", &(this->_visible), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		ImVec2 viewportSize = ImGui::GetWindowSize();
		ImVec2 viewportPos  = ImGui::GetWindowPos();
		ImVec2 mousePos     = Application::GetMousePos();

		_view.zoom(_zoom);

		_viewportRect =
		    ImRect(viewportPos,
		           {viewportPos.x + viewportSize.x, viewportPos.y + viewportSize.y + ImGui::GetFrameHeight()});

		_view.reset(sf::FloatRect(0, 0, viewportSize.x, viewportSize.y));
		_renderTexture.setView(_view);

		sf::Vector2f relativeMousePos(mousePos.x - viewportPos.x, mousePos.y - viewportPos.y - ImGui::GetFrameHeight());
		_renderTexture.create(viewportSize.x, viewportSize.y);
		_renderTexture.clear(sf::Color(11, 11, 11));

		RenderGrid(_renderTexture, _cellSize);

		ImGui::Image(_renderTexture);

		ImGui::End();
	}

	float Viewport::smoothstep(float edge0, float edge1, float x) {
		// Scale, and clamp x to 0..1 range
		x = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		// Evaluate polynomial
		return x * x * (3 - 2 * x);
	}

	float Viewport::lerp(float left, float right, float x) {
		return left + x * (right - left);
	}

	void Viewport::RenderGrid(sf::RenderTarget& target, float cellSize, sf::Color color) {
		sf::RectangleShape grid;
		grid.setFillColor(sf::Color::Transparent);
		grid.setOutlineColor(color);
		grid.setOutlineThickness(1);
		grid.setSize(sf::Vector2f(cellSize, cellSize));
		for (int i = 0; i < target.getSize().x / cellSize; i++) {
			for (int j = 0; j < target.getSize().y / cellSize; j++) {
				grid.setPosition(i * cellSize, j * cellSize);
				target.draw(grid);
			}
		}
	}
} // namespace sse