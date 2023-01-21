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
		ImVec2 mousePos = Input::GetMousePositionImGui();

		if (_viewportRect.Contains(mousePos)) {
			if (event.type == sf::Event::MouseWheelScrolled) {
				_targetZoom =
				    std::max(0.1f, std::min(10.f, _targetZoom + event.mouseWheelScroll.delta * _zoomDeltaMultiplier));
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_isLeftMousePressed = true;
					_leftMouseButtonPressedStartPos =
					    sf::Vector2f(event.mouseButton.x - ImGui::GetStyle().WindowPadding.x,
					                 event.mouseButton.y - ImGui::GetStyle().WindowPadding.y - ImGui::GetFrameHeight());

					if (Application::GetCurrentTool() != nullptr)
						Application::GetCurrentTool()->OnMouseDown(sf::Vector2f(
						    event.mouseButton.x - ImGui::GetStyle().WindowPadding.x,
						    event.mouseButton.y - ImGui::GetStyle().WindowPadding.y - ImGui::GetFrameHeight()));
				}

				if (event.mouseButton.button == sf::Mouse::Middle) {
					_isMiddleMousePressed = true;
					_middleMouseButtonPressedStartPos =
					    sf::Vector2f(event.mouseButton.x - ImGui::GetStyle().WindowPadding.x,
					                 event.mouseButton.y - ImGui::GetStyle().WindowPadding.y - ImGui::GetFrameHeight());
				}
			}

			if (event.type == sf::Event::MouseMoved) {
				if (_isMiddleMousePressed) {
					_desiredViewCenter =
					    _view.getCenter() - sf::Vector2f(event.mouseMove.x - _middleMouseButtonPressedStartPos.x,
					                                     event.mouseMove.y - _middleMouseButtonPressedStartPos.y);
				} else if (_isLeftMousePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					_desiredViewCenter =
					    _view.getCenter() - sf::Vector2f(event.mouseMove.x - _leftMouseButtonPressedStartPos.x,
					                                     event.mouseMove.y - _leftMouseButtonPressedStartPos.y);
				}

				if (Application::GetCurrentTool() != nullptr)
					Application::GetCurrentTool()->OnMouseMove(
					    sf::Vector2f(event.mouseMove.x - ImGui::GetStyle().WindowPadding.x,
					                 event.mouseMove.y - ImGui::GetStyle().WindowPadding.y - ImGui::GetFrameHeight()));
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_isLeftMousePressed = false;
				}

				if (event.mouseButton.button == sf::Mouse::Middle) {
					_isMiddleMousePressed = false;
				}

				if (Application::GetCurrentTool() != nullptr)
					Application::GetCurrentTool()->OnMouseUp(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::Up) {
					// _cellSize = std::min(100.f, _cellSize + 5.f);
				}
				if (event.key.code == sf::Keyboard::F2 || event.key.code == sf::Keyboard::Down) {
					// _cellSize = std::max(5.f, _cellSize - 5.f);
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
		if (_desiredViewCenter == sf::Vector2f(-1.f, -1.f)) _desiredViewCenter = _view.getCenter();

		float currentZoomSpeed = _zoomSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			currentZoomSpeed *= 2.f;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			currentZoomSpeed = 0.1f;
		}

		if (Application::GetCurrentTool() != nullptr) Application::GetCurrentTool()->OnUpdate(dt);

		// move the view
		_desiredViewCenter += Input::GetDirection() * _viewSpeed * dt;

		// zoom the view
		if (Input::IsKeyDown(sf::Keyboard::LBracket)) {
			_targetZoom =
			    std::max(0.1f, std::min(10.f, lerp(_zoom, _targetZoom, currentZoomSpeed * dt) - _zoomDeltaMultiplier));
		}
		if (Input::IsKeyDown(sf::Keyboard::RBracket)) {
			_targetZoom =
			    std::max(0.1f, std::min(10.f, lerp(_zoom, _targetZoom, currentZoomSpeed * dt) + _zoomDeltaMultiplier));
		}

		_zoom = lerp(_zoom, _targetZoom, currentZoomSpeed * dt);

		_view.setCenter(lerp(_view.getCenter().x, _desiredViewCenter.x, currentZoomSpeed * dt),
		                lerp(_view.getCenter().y, _desiredViewCenter.y, currentZoomSpeed * dt));

		_view.setSize(_view.getSize().x * _zoom, _view.getSize().y * _zoom);
	}

	void Viewport::OnRenderUI() {
		ImGui::Begin("Viewport", &(this->_visible), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		RenderOverlay([&](bool& visible, int& location) {
			ImVec2 mousePos = Input::GetMousePositionImGui();
			ImGui::Text("Info\n"
			            "(right-click to change position)");
			ImGui::Separator();
			if (ImGui::IsMousePosValid())
				ImGui::Text("Mouse Position: (%.1f, %.1f)", mousePos.x, mousePos.y);
			else
				ImGui::Text("Mouse Position: <invalid>");

			if (_isLeftMousePressed)
				ImGui::Text("Left Mouse Button Pressed: (%.1f, %.1f)",
				            _leftMouseButtonPressedStartPos.x,
				            _leftMouseButtonPressedStartPos.y);
			else
				ImGui::Text("Left Mouse Button Pressed: <not pressed>");

			if (_isMiddleMousePressed)
				ImGui::Text("Middle Mouse Button Pressed: (%.1f, %.1f)",
				            _middleMouseButtonPressedStartPos.x,
				            _middleMouseButtonPressedStartPos.y);
			else
				ImGui::Text("Middle Mouse Button Pressed: <not pressed>");

			ImGui::Separator();

			ImGui::Text("Viewport Pos: (%.1f, %.1f)", _viewportRect.Min.x, _viewportRect.Min.y);
			ImGui::Text("Viewport Size: (%.1f, %.1f)", _viewportRect.Max.x, _viewportRect.Max.y);

			ImGui::Separator();

			ImGui::Text("View Center: (%.1f, %.1f)", _view.getCenter().x, _view.getCenter().y);
			ImGui::Text("View Size: (%.1f, %.1f)", _view.getSize().x, _view.getSize().y);
			ImGui::Text("View Zoom: %.1f", _zoom);

			ImGui::Checkbox("Snap Zoom: ", &(this->_snapZoom));
			ImGui::Checkbox("Snap Movement: ", &(this->_snapMovement));
			ImGui::Checkbox("Show Grid: ", &(this->_showGrid));

			ImGui::Separator();

			ImGui::Text("Selection Rectangle: (x: %.1f, y: %.1f, w: %.1f, h: %.1f)\n\n",
			            _selectionRect.left,
			            _selectionRect.top,
			            _selectionRect.width,
			            _selectionRect.height);

			ImGui::Separator();

			if (ImGui::TreeNode("Sprite")) {
				float width  = ImGui::GetContentRegionAvail().x / 2.f;
				float height = width / Application::GetSpriteEntity()->GetSprite().getTexture()->getSize().x *
				               Application::GetSpriteEntity()->GetSprite().getTexture()->getSize().y;
				ImGui::Image(Application::GetSpriteEntity()->GetSprite(), sf::Vector2f(width, height));
				ImGui::TreePop();
			}

			if (ImGui::BeginPopupContextWindow()) {
				if (ImGui::MenuItem("Custom", NULL, location == -1)) location = -1;
				if (ImGui::MenuItem("Center", NULL, location == -2)) location = -2;
				if (ImGui::MenuItem("Top-left", NULL, location == 0)) location = 0;
				if (ImGui::MenuItem("Top-right", NULL, location == 1)) location = 1;
				if (ImGui::MenuItem("Bottom-left", NULL, location == 2)) location = 2;
				if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
				if (ImGui::MenuItem("Close")) visible = false;
				ImGui::EndPopup();
			}
		});

		ImVec2 viewportSize = ImGui::GetWindowSize();
		ImVec2 viewportPos  = ImGui::GetWindowPos();
		ImVec2 mousePos     = Input::GetMousePositionImGui();
		_viewMousePos =
		    sf::Vector2f(mousePos.x - viewportPos.x - ImGui::GetStyle().WindowPadding.x,
		                 mousePos.y - viewportPos.y - ImGui::GetStyle().WindowPadding.y - ImGui::GetFrameHeight());
		// _viewMousePos -= _view.getCenter();

		_viewportRect =
		    ImRect(viewportPos,
		           {viewportPos.x + viewportSize.x, viewportPos.y + viewportSize.y + ImGui::GetFrameHeight()});

		_view.setSize(viewportSize.x * _zoom, viewportSize.y * _zoom);

		_renderTexture.create(viewportSize.x, viewportSize.y);
		_renderTexture.clear(sf::Color(0, 0, 0));

		_renderTexture.setView(_view);
		Application::GetSpriteEntity()->OnRender(_renderTexture);

		_renderTexture.setView(_renderTexture.getDefaultView());

		sf::CircleShape mouseCircle(5);
		mouseCircle.setFillColor(sf::Color::Red);
		mouseCircle.setPosition(_viewMousePos);
		_renderTexture.draw(mouseCircle);

		RenderGrid(_renderTexture, _cellSize, sf::Color(100, 100, 100, 50));
		RenderSelection();

		if (Application::GetCurrentTool() != nullptr) Application::GetCurrentTool()->OnRender(_renderTexture);

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
		if (!_showGrid) return;

		sf::RectangleShape grid;
		grid.setFillColor(sf::Color::Transparent);
		grid.setOutlineColor(color);
		grid.setOutlineThickness(1);
		grid.setSize(sf::Vector2f(cellSize, cellSize));

		for (int i = 0; i < target.getSize().x / cellSize; i++) {
			for (int j = 0; j < target.getSize().y / cellSize; j++) {
				grid.setPosition(i * cellSize, j * cellSize);

				// if (grid.getGlobalBounds().contains(_viewMousePos))
				// 	grid.setOutlineColor(sf::Color::Red);
				// else {
				// 	grid.setOutlineColor(color);
				// 	grid.setFillColor(sf::Color::Transparent);
				// }

				target.draw(grid);
			}
		}
	}

	void Viewport::RenderSelection() {
		if (_isLeftMousePressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			_selectionRect =
			    sf::FloatRect(_leftMouseButtonPressedStartPos, _viewMousePos - _leftMouseButtonPressedStartPos);

			sf::RectangleShape rect;
			rect.setPosition(_leftMouseButtonPressedStartPos);
			rect.setSize(sf::Vector2f(_selectionRect.width, _selectionRect.height));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::Blue);
			rect.setOutlineThickness(2.f);

			_renderTexture.draw(rect);
		}
	}

	template<typename Callback>
	void Viewport::RenderOverlay(Callback&& callback) {
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

} // namespace sse