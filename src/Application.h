//
// Created by abdoulayedia on 04.01.2023
//
#pragma once

#include "constants.h"

namespace sse {
	// Application
	class Application {
	  public:
		static Application* GetInstance() {
			if (_instance == nullptr) {
				_instance = new Application();
			}
			return _instance;
		}

		int Run();
		int InitImGuiSFML();

	  private:
		Application();
		virtual ~Application();
		inline static Application* _instance = nullptr;
		void                       setFancyImguiStyle();

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

	  public:
		Application(Application const&)            = delete;
		Application& operator=(const Application&) = delete;

		static sf::Color ImVec4toSFColor(ImVec4 color);
	};
} // namespace sse
