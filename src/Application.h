//
// Created by abdoulayedia on 04.01.2023
//
#pragma once

#include "layers/Viewport.h"

namespace sse {
	// Application
	class Application {
	  public:
		static Application* GetInstance() {
			if (_instance == nullptr) {
				_instance = std::make_shared<Application>();
			}
			return _instance.get();
		}

		int Run();

		template<typename T>
		void PushLayer();
		void PushLayer(const std::shared_ptr<Layer>& layer);

		Application();
		virtual ~Application();

	  private:
		inline static std::shared_ptr<Application> _instance = nullptr;
		void                                       setFancyImguiStyle();

		int InitImGuiSFML();
		int InitLayers();

		void HandleEvents();
		void Update();
		void Render();
		void Shutdown();

		// SFML
		sf::RenderWindow* _window = nullptr;
		sf::RenderTexture _renderTexture;
		sf::Clock         _clock;
		sf::Shader        _shader;

		// ImGui
		ImFont*  _imFont = nullptr;
		ImGuiIO* _imIO   = nullptr;
		sf::Font _font;
		sf::Text _text;

		// Application variables
		ImVec2 _mousePos;

		std::vector<std::shared_ptr<Layer>> _layers;

	  public:
		Application(Application const&)            = delete;
		Application& operator=(const Application&) = delete;

		static sf::Color ImVec4toSFColor(ImVec4 color);
	};

} // namespace sse
