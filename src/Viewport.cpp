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

	bool Viewport::OnHandleEvents(sf::Event& event) {
		if (!_viewportRect.Contains(Input::GetMousePositionImGui())) return false;

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::G) {
				_showGrid = !_showGrid;
				return true;
			}

			if (event.key.code == sf::Keyboard::Tab) {
				_showDebug = !_showDebug;
				return true;
			}

			// Numpad keys to change tool
			if (event.key.code >= sf::Keyboard::Numpad1 && event.key.code <= sf::Keyboard::Numpad9) {
				if (Toolbox::SetCurrentTool(event.key.code - sf::Keyboard::Numpad1)) {
					std::cout << "Changing tool to " << Toolbox::GetCurrentTool()->GetName() << std::endl;
				} else {
					std::cout << "Tool " << event.key.code - sf::Keyboard::Numpad1 << " is not available" << std::endl;
				}
				return true;
			}

			// Numpad keys to change tool
			if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
				if (Toolbox::SetCurrentTool(event.key.code - sf::Keyboard::Num1)) {
					std::cout << "Changing tool to " << Toolbox::GetCurrentTool()->GetName() << std::endl;
				} else {
					std::cout << "Tool " << event.key.code - sf::Keyboard::Num1 << " is not available" << std::endl;
				}
				return true;
			}
		}

		return false;
	}

	void Viewport::OnUpdate(float dt) {
		_renderTexture.setView(_view);
		_viewMousePos = Application::WorldToRenderTarget(Input::GetMousePosition());
		_renderTexture.setView(_renderTexture.getDefaultView());
		_viewportMousePos =
		    Input::GetMousePosition() - sf::Vector2f(ImGui::GetStyle().WindowPadding.x,
		                                             ImGui::GetStyle().WindowPadding.y + ImGui::GetFrameHeight());
	}

	void Viewport::OnRenderUI() {
		ImGui::Begin("Viewport", &(this->_visible), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		if (_showDebug) RenderDebug();

		RenderViewport();
		RenderToolbox();

		ImGui::End();
	}

	void Viewport::RenderViewport() {
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		_viewportRect       = ImRect(
            ImGui::GetCursorScreenPos(),
            ImVec2(ImGui::GetCursorScreenPos().x + viewportSize.x, ImGui::GetCursorScreenPos().y + viewportSize.y));
		if (Toolbox::GetCurrentTool() != nullptr)
			Toolbox::SetWorkspaceRect(
			    sf::FloatRect(_viewportRect.Min.x, _viewportRect.Min.y, viewportSize.x, viewportSize.y));
		_view.setSize(viewportSize.x, viewportSize.y);

		_renderTexture.clear(sf::Color::Transparent);
		_renderTexture.create(viewportSize.x, viewportSize.y);
		RenderGrid(_renderTexture, 32.f, sf::Color(255, 255, 255, 50));

		_renderTexture.setView(_view);

		Application::GetSpriteEntity()->OnRender(_renderTexture);

		Toolbox::OnRender(_renderTexture);

		// _renderTexture.setView(_renderTexture.getDefaultView());

		ImGui::Image(_renderTexture);
	}

	void Viewport::RenderDebug() {
		RenderOverlay([&](bool& visible, int& location) {
			ImVec2 mousePos = Input::GetMousePositionImGui();
			ImGui::Text("Info\n"
			            "(right-click to change position)");
			ImGui::Separator();
			if (ImGui::IsMousePosValid())
				ImGui::Text("Mouse Position: (%.1f, %.1f)", mousePos.x, mousePos.y);
			else
				ImGui::Text("Mouse Position: <invalid>");

			if (Input::IsMouseButtonDown(sf::Mouse::Left))
				ImGui::Text("Left Mouse Button Pressed At: (%.1f, %.1f)",
				            Input::GetMouseDownPosition(sf::Mouse::Left).x,
				            Input::GetMouseDownPosition(sf::Mouse::Left).y);
			else
				ImGui::Text("Left Mouse Button Pressed: <not pressed>");

			if (Input::IsMouseButtonDown(sf::Mouse::Middle))
				ImGui::Text("Middle Mouse Button Pressed At: (%.1f, %.1f)",
				            Input::GetMouseDownPosition(sf::Mouse::Middle).x,
				            Input::GetMouseDownPosition(sf::Mouse::Middle).y);
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
				if (ImGui::MenuItem("Follow mouse", NULL, location == 4)) location = 4;
				if (ImGui::MenuItem("Close")) visible = false;
				ImGui::EndPopup();
			}
		});
	}

	void Viewport::RenderToolbox() {
		RenderOverlay(
		    [&](bool& visible, int& location) {
			    ImGui::Text("Toolbox");
			    ImGui::Separator();

			    if (Toolbox::GetCurrentTool() != nullptr)
				    ImGui::Text("Current Tool: %s", Toolbox::GetCurrentTool()->GetName().c_str());
			    else
				    ImGui::Text("Current Tool: <none>");

			    ImGui::Separator();

			    ImGui::Text("Tools");
			    ImGui::Separator();

			    for (auto& tool : Toolbox::GetTools()) {
				    ImGui::PushID(tool->GetName().c_str());
				    if (ImGui::Button(tool->GetName().c_str())) {
					    Toolbox::SetCurrentTool(tool);
				    }
				    ImGui::PopID();
			    }

			    if (ImGui::BeginPopupContextWindow()) {
				    if (ImGui::MenuItem("Custom", NULL, location == -1)) location = -1;
				    if (ImGui::MenuItem("Center", NULL, location == -2)) location = -2;
				    if (ImGui::MenuItem("Follow mouse", NULL, location == -3)) location = -3;
				    if (ImGui::MenuItem("Top-left", NULL, location == 0)) location = 0;
				    if (ImGui::MenuItem("Top-right", NULL, location == 1)) location = 1;
				    if (ImGui::MenuItem("Bottom-left", NULL, location == 2)) location = 2;
				    if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
				    if (ImGui::MenuItem("Close")) visible = false;
				    ImGui::EndPopup();
			    }
		    },
		    "Toolbox");
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

				if (grid.getGlobalBounds().contains(_viewportMousePos))
					grid.setOutlineColor(sf::Color::Red);
				else {
					grid.setOutlineColor(color);
					grid.setFillColor(sf::Color::Transparent);
				}

				target.draw(grid);
			}
		}
	}

	void Viewport::RenderSelection() {}

	float Viewport::smoothstep(float edge0, float edge1, float x) {
		// Scale, and clamp x to 0..1 range
		x = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		// Evaluate polynomial
		return x * x * (3 - 2 * x);
	}

	float Viewport::lerp(float left, float right, float x) {
		return left + x * (right - left);
	}

	template<typename Callback>
	void Viewport::RenderOverlay(Callback&& callback, const char* id) {
		static int  location  = 0;
		static bool visible   = true;
		ImVec2      mouse_pos = Input::GetMousePositionImGui();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
		                                ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
		                                ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

		if (location == -3) {
			ImGui::SetNextWindowPos(mouse_pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
			window_flags |= ImGuiWindowFlags_NoMove;
		} else if (location >= 0) {
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
		const char name[256] = {0};
		if (ImGui::Begin(id, &visible, window_flags)) {
			callback(visible, location);
		}
		ImGui::End();
	}

} // namespace sse