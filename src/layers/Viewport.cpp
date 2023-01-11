//
// Created by abdoulayedia on 09.01.2023
//
#include "Viewport.h"

#include "Application.h"

namespace sse {
	void Viewport::OnAttach() {
		_view.reset(sf::FloatRect(0, 0, 1000, 1000));
		_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	}

	void Viewport::OnHandleSFMLEvent(sf::Event& event) {
		ImVec2 mousePos = Application::GetMousePos();

		if (_viewportRect.Contains(mousePos)) {
			if (event.type == sf::Event::MouseWheelScrolled) {
				_targetZoom = std::max(0.1f, std::min(10.f, _targetZoom + event.mouseWheelScroll.delta * 0.1f));
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_isLeftMousePressed             = true;
					_leftMouseButtonPressedStartPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				}
			}

			if (event.type == sf::Event::MouseMoved) {
				if (_isLeftMousePressed) {
					_desiredViewCenter =
					    _view.getCenter() - sf::Vector2f(event.mouseMove.x - _leftMouseButtonPressedStartPos.x,
					                                     event.mouseMove.y - _leftMouseButtonPressedStartPos.y);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_isLeftMousePressed = false;
				}
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::Up) {
					_cellSize = std::min(100.f, _cellSize + 5.f);
				}
				if (event.key.code == sf::Keyboard::F2 || event.key.code == sf::Keyboard::Down) {
					_cellSize = std::max(5.f, _cellSize - 5.f);
				}
			}
		} else {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_isLeftMousePressed = false;
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_isLeftMousePressed = false;
				}
			}
		}
	}

	void Viewport::OnUpdate(float dt) {
		// std::cout << "Update from the viewport: " << dt << std::endl;
		_zoom = smoothstep(_zoom, _targetZoom, _zoomSpeed * dt);

		_view.setCenter(lerp(_view.getCenter().x, _desiredViewCenter.x, _zoomSpeed * dt),
		                lerp(_view.getCenter().y, _desiredViewCenter.y, _zoomSpeed * dt));

		_view.setSize(_viewportRect.GetWidth() * _zoom, _viewportRect.GetHeight() * _zoom);
	}
	void Viewport::OnRenderUI() {
		ImGui::Begin("Viewport", &(this->_visible), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		RenderOverlay();

		ImVec2 viewportSize = ImGui::GetWindowSize();
		ImVec2 viewportPos  = ImGui::GetWindowPos();
		ImVec2 mousePos     = Application::GetMousePos();

		_viewportRect =
		    ImRect(viewportPos,
		           {viewportPos.x + viewportSize.x, viewportPos.y + viewportSize.y + ImGui::GetFrameHeight()});

		if (_desiredViewCenter == sf::Vector2f(-1.f, -1.f)) _desiredViewCenter = _view.getCenter();

		_view.setSize(viewportSize.x * _zoom, viewportSize.y * _zoom);
		_renderTexture.setView(_view);

		sf::Vector2f relativeMousePos(mousePos.x - viewportPos.x, mousePos.y - viewportPos.y - ImGui::GetFrameHeight());
		_renderTexture.create(viewportSize.x, viewportSize.y);
		_renderTexture.clear(sf::Color(11, 11, 11));

		RenderGrid(_renderTexture, _cellSize);

		sf::CircleShape circle(50);
		circle.setFillColor(sf::Color::Red);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(_view.getCenter() + sf::Vector2f(100.f, 100.f));

		_renderTexture.draw(circle);

		_renderTexture.display();

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
	void Viewport::RenderOverlay() {
		static int       location     = 0;
		ImGuiIO&         io           = ImGui::GetIO();
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
		ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
		if (ImGui::Begin("Example: Simple overlay", NULL, window_flags)) {
			ImGui::Text("Simple overlay\n"
			            "(right-click to change position)");
			ImGui::Separator();
			if (ImGui::IsMousePosValid())
				ImGui::Text("Mouse Position: (%.1f, %.1f)", io.MousePos.x, io.MousePos.y);
			else
				ImGui::Text("Mouse Position: <invalid>");

			ImGui::Text("View Center: (%.1f, %.1f)", _view.getCenter().x, _view.getCenter().y);
			ImGui::Text("View Size: (%.1f, %.1f)", _view.getSize().x, _view.getSize().y);
			ImGui::Text("View Zoom: %.1f", _zoom);

			if (ImGui::BeginPopupContextWindow()) {
				if (ImGui::MenuItem("Custom", NULL, location == -1)) location = -1;
				if (ImGui::MenuItem("Center", NULL, location == -2)) location = -2;
				if (ImGui::MenuItem("Top-left", NULL, location == 0)) location = 0;
				if (ImGui::MenuItem("Top-right", NULL, location == 1)) location = 1;
				if (ImGui::MenuItem("Bottom-left", NULL, location == 2)) location = 2;
				if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
} // namespace sse