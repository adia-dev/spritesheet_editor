//
// Created by abdoulayedia on 22.01.2023
//
#pragma once

#include "tools.h"

namespace sse {
	// Toolbox
	class Toolbox {
	  public:
		Toolbox() {}
		~Toolbox() {}

		static Toolbox* GetInstance() {
			if (_instance == nullptr) {
				_instance = std::make_shared<Toolbox>();
			}
			return _instance.get();
		}

		static bool OnHandleEvents(sf::Event& event);
		static void OnRender(sf::RenderTarget& target);
		static void OnUpdate(float dt);

		static bool SetCurrentTool(std::shared_ptr<Tool> tool);
		static bool SetCurrentTool(int index);

		static std::vector<std::shared_ptr<Entity>>& GetSelectedEntities();
		static void                                  ClearSelectedEntities();
		static void                                  AddSelectedEntity(std::shared_ptr<Entity> entity);
		static void                                  RemoveSelectedEntity(std::shared_ptr<Entity> entity);
		static void                                  RemoveSelectedEntity(int index);

		static bool                   PushTool(const std::shared_ptr<Tool>& tool, bool setCurrent = false);
		static bool                   RemoveTool(const std::shared_ptr<Tool>& tool);
		static std::shared_ptr<Tool>& GetCurrentTool();

		static std::vector<std::shared_ptr<Tool>> GetTools() { return GetInstance()->_tools; }

		static void SetWorkspaceRect(const sf::FloatRect& rect) { GetInstance()->_workspaceRect = rect; }
		static const sf::FloatRect& GetWorkspaceRect() { return GetInstance()->_workspaceRect; }

	  private:
		std::vector<std::shared_ptr<Tool>>     _tools;
		std::shared_ptr<Tool>                  _currentTool = nullptr;
		inline static std::shared_ptr<Toolbox> _instance    = nullptr;

		sf::FloatRect                        _workspaceRect;
		std::vector<std::shared_ptr<Entity>> _selectedEntities;

	  public:
		Toolbox(const Toolbox&)            = delete;
		Toolbox& operator=(const Toolbox&) = delete;
	};
} // namespace sse
