//
// Created by abdoulayedia on 04.01.2023
//
#include "Application.h"

#include "components.h"
#include "tools.h"

#include <assert.h>

namespace sse {

	Application::Application() {
		std::cout << "Application Starting up" << std::endl;
	}

	Application::~Application() {
		Shutdown();
	}

	void Application::setFancyImguiStyle() {
		ImVec4 *colors                         = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg]              = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg]               = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border]                = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
		colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg]               = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive]         = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark]             = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_SliderGrab]            = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header]                = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_HeaderHovered]         = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		colors[ImGuiCol_HeaderActive]          = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip]            = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab]                   = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabHovered]            = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive]             = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		colors[ImGuiCol_TabUnfocused]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_DockingPreview]        = ImVec4(0.61f, 0.61f, 0.61f, 0.41f);
		colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
		colors[ImGuiCol_PlotLines]             = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
		colors[ImGuiCol_PlotHistogram]         = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderLight]      = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_TableRowBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight]          = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.35f, 0.35f, 0.35f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.36f, 0.36f, 0.36f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.34f, 0.34f, 0.34f, 0.35f);

		ImGuiStyle &style       = ImGui::GetStyle();
		style.WindowPadding     = ImVec2(8.00f, 8.00f);
		style.FramePadding      = ImVec2(20.00f, 10.00f);
		style.CellPadding       = ImVec2(6.00f, 6.00f);
		style.ItemSpacing       = ImVec2(6.00f, 6.00f);
		style.ItemInnerSpacing  = ImVec2(6.00f, 6.00f);
		style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
		style.IndentSpacing     = 25;
		style.ScrollbarSize     = 15;
		style.GrabMinSize       = 10;
		style.WindowBorderSize  = 0;
		style.ChildBorderSize   = 0;
		style.PopupBorderSize   = 0;
		style.FrameBorderSize   = 0;
		style.TabBorderSize     = 1;
		style.WindowRounding    = 0;
		style.ChildRounding     = 4;
		style.FrameRounding     = 7;
		style.PopupRounding     = 12;
		style.ScrollbarRounding = 9;
		style.GrabRounding      = 3;
		style.LogSliderDeadzone = 4;
		style.TabRounding       = 4;

		style.WindowMenuButtonPosition = ImGuiDir_None;
	}

	void Application::HandleEvents() {
		if (_window == nullptr) return;

		sf::Event event;

		while (_window->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			Input::HandleEvents(event);
			if (_currentTool != nullptr) _currentTool->HandleSFMLEvent(event);

			for (auto &layer : _layers) {
				if (layer->OnHandleSFMLEvent(event)) break;
			}

			if (event.type == sf::Event::Closed) {
				_window->close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					_window->close();
				}
			}
		}
	}

	void Application::Update() {
		if (_window == nullptr) return;

		float deltaTime = _imIO->DeltaTime;

		for (auto entitiy : _entities) {
			entitiy->OnUpdate(deltaTime);
		}

		if (_currentTool != nullptr) _currentTool->OnUpdate(deltaTime);

		for (auto &layer : _layers) {
			layer->OnUpdate(deltaTime);
		}

		ImGui::SFML::Update(*_window, _clock.restart());
	}

	void Application::Render() {
		ImGui::PushFont(_imFont);
		ImGui::DockSpaceOverViewport();

		for (auto &layer : _layers) layer->OnRenderUI();

		// ImGui::ShowDemoWindow();
		// Components::ShowBezierDemo();

		// ImGui::PopStyleVar();
		ImGui::PopFont();

		_window->clear();
		ImGui::SFML::Render(*_window);
		_window->display();
	}

	void Application::Shutdown() {
		ImGui::SFML::Shutdown();

		std::cout << "Shutting the Application\n";

		delete _window;
		_window = nullptr;
		_imFont = nullptr;
		_imIO   = nullptr;
	}

	sf::Color Application::ImVec4toSFColor(ImVec4 color) {
		return sf::Color(color.x * 255, color.y * 255, color.z * 255, color.w * 255);
	}

	int Application::Run() {
		auto instance = Application::GetInstance();

		if (instance == nullptr) return -1;

		if (!instance->InitImGuiSFML()) return -1;
		if (!instance->InitEntities()) return -1;
		if (!instance->InitLayers()) return -1;
		if (!instance->InitTool()) return -1;

		while (instance->_window->isOpen()) {
			instance->HandleEvents();
			instance->Update();
			instance->Render();
		}

		return 0;
	}

	int Application::InitImGuiSFML() {
		_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ImGui SFML", sf::Style::Default);
		if (_window == nullptr) {
			std::cerr << "Could not create the window instance.\n";
			return -1;
		}

		if (!ImGui::SFML::Init(*_window)) {
			std::cerr << "Could not init the ImGui SFML window.\n";
			return -1;
		}

		_imIO = &ImGui::GetIO();
		_imIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// _imIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		_imIO->FontGlobalScale = 1.5f;
		_imIO->MouseDrawCursor = true;

		static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
		ImFontConfig         icons_config;
		icons_config.MergeMode  = true;
		icons_config.PixelSnapH = true;
		_imFont                 = _imIO->Fonts->AddFontFromFileTTF("../assets/fonts/FontAwesome/fa-solid-900.ttf",
                                                   32.0f,
                                                   &icons_config,
                                                   icons_ranges);

		_imIO->Fonts->AddFontFromFileTTF("../assets/fonts/Operator-Mono/Fonts/OperatorMono-Medium.otf", 20.f);
		_font.loadFromFile("../assets/fonts/Operator-Mono/Fonts/OperatorMono-Medium.otf");
		_text.setFont(_font);

		_imIO->IniFilename = "../resources/layouts/default.ini";

		setFancyImguiStyle();

		if (!ImGui::SFML::UpdateFontTexture()) {
			std::cerr << "Could not update the font texture.\n";
			return -1;
		}

		return 1;
	}

	int Application::InitEntities() {
		_spriteEntity =
		    std::make_shared<SpriteEntity>(AssetManager::GetTexture("../assets/images/spritesheets/broly/1.png"));
		_spriteEntity->SetName("Broly");

		PushEntity(_spriteEntity);

		return 1;
	}

	int Application::InitLayers() {
		std::shared_ptr<Layer> viewport = std::make_shared<Viewport>(_renderTexture);
		PushLayer(viewport);
		PushLayer<Hierarchy>();

		return 1;
	}

	int Application::InitTool() {
		_tools.emplace_back(std::make_shared<MoveTool>(_spriteEntity, "Move Tool"));
		_tools.emplace_back(std::make_shared<SelectionTool>(_spriteEntity, "Selection Tool"));

		_currentTool = _tools[0];

		return 1;
	}

	//* Thanks TheCherno learned a lot right there eheh
	template<typename T>
	void Application::PushLayer() {
		static_assert(std::is_base_of<Layer, T>::value, "Pushed type that is not subclass of the Layer Class !");
		_layers.emplace_back(std::make_shared<T>())->OnAttach();
	}

	void Application::PushLayer(const std::shared_ptr<Layer> &layer) {
		_layers.emplace_back(layer)->OnAttach();
	}

	template<typename T>
	void Application::PushEntity() {
		static_assert(std::is_base_of<Entity, T>::value, "Pushed type that is not subclass of the Entity Class !");
		_entities.emplace_back(std::make_shared<T>())->OnAwake();
	}

	void Application::PushEntity(const std::shared_ptr<Entity> &entity) {
		_entities.emplace_back(entity)->OnAwake();
	}
} // namespace sse
