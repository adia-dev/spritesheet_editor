//
// Created by abdoulayedia on 04.01.2023
//
#pragma once

#include "AnimationPreview.h"
#include "AssetManager.h"
#include "Hierarchy.h"
#include "Input.h"
#include "SpriteEntity.h"
#include "Toolbox.h"
#include "Viewport.h"
#include "utils/Maths.hpp"

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

		static int Run();

		template<typename T>
		void PushLayer();
		void PushLayer(const std::shared_ptr<Layer>& layer);

		template<typename T>
		void PushEntity();
		void PushEntity(const std::shared_ptr<Entity>& entity);

		Application();
		virtual ~Application();

		static ImGuiIO           GetImGuiIO() { return *GetInstance()->_imIO; }
		static sf::RenderWindow* GetWindow() { return GetInstance()->_window; }
		static float             GetDeltaTime() { return GetImGuiIO().DeltaTime; }

		static std::vector<std::shared_ptr<Layer>> GetLayers() { return GetInstance()->_layers; }

		static std::vector<std::shared_ptr<Entity>> GetEntities() { return GetInstance()->_entities; }
		static std::shared_ptr<SpriteEntity>        GetSpriteEntity() { return GetInstance()->_spriteEntity; }

		static sf::RenderTexture& GetRenderTexture() { return GetInstance()->_renderTexture; }

		static sf::Vector2f WorldToRenderTarget(const sf::Vector2f& worldPos) {
			return Maths::WorldToRenderTarget(worldPos, GetRenderTexture());
		}

	  private:
		inline static std::shared_ptr<Application> _instance = nullptr;
		void                                       setFancyImguiStyle();

		int InitImGuiSFML();
		int InitEntities();
		int InitLayers();
		int InitToolbox();

		void HandleEvents();
		void Update();
		void Render();
		void Shutdown();

		// SFML
		sf::RenderWindow* _window = nullptr;
		sf::Clock         _clock;
		sf::Shader        _shader;
		sf::RenderTexture _renderTexture;

		// ImGui
		ImFont*  _imFont = nullptr;
		ImGuiIO* _imIO   = nullptr;
		sf::Font _font;
		sf::Text _text;

		// Application variables
		std::vector<std::shared_ptr<Layer>> _layers;

		std::vector<std::shared_ptr<Entity>> _entities;
		std::shared_ptr<SpriteEntity>        _spriteEntity = nullptr;

	  public:
		Application(Application const&)            = delete;
		Application& operator=(const Application&) = delete;

		static sf::Color ImVec4toSFColor(ImVec4 color);
	};

} // namespace sse
