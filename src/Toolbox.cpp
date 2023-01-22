//
// Created by abdoulayedia on 22.01.2023
//
#include "Toolbox.h"

#include "Application.h"

namespace sse {
	std::shared_ptr<Tool>& Toolbox::GetCurrentTool() {
		return GetInstance()->_currentTool;
	}

	bool Toolbox::OnHandleEvents(sf::Event& event) {
		if (GetInstance()->_currentTool != nullptr) return GetInstance()->_currentTool->OnHandleEvents(event);
		return false;
	}

	void Toolbox::OnRender(sf::RenderTarget& target) {
		if (GetInstance()->_currentTool != nullptr) GetInstance()->_currentTool->OnRender(target);
	}

	void Toolbox::OnUpdate(float dt) {
		if (GetInstance()->_currentTool != nullptr) GetInstance()->_currentTool->OnUpdate(dt);
	}

	bool Toolbox::SetCurrentTool(std::shared_ptr<Tool> tool) {
		if (GetInstance()->_currentTool != nullptr) GetInstance()->_currentTool->OnDetach();
		GetInstance()->_currentTool = tool;
		if (GetInstance()->_currentTool != nullptr) GetInstance()->_currentTool->OnAttach();
		return true;
	}

	bool Toolbox::SetCurrentTool(int index) {
		if (index < 0 || index >= GetInstance()->_tools.size()) return false;

		if (GetInstance()->_currentTool != nullptr) GetInstance()->_currentTool->OnDetach();
		GetInstance()->_currentTool = GetInstance()->_tools[index];
		if (GetInstance()->_currentTool != nullptr) GetInstance()->_currentTool->OnAttach();

		return true;
	}

	std::vector<std::shared_ptr<Entity>>& Toolbox::GetSelectedEntities() {
		return GetInstance()->_selectedEntities;
	}

	void Toolbox::ClearSelectedEntities() {
		GetInstance()->_selectedEntities.clear();
	}

	void Toolbox::AddSelectedEntity(std::shared_ptr<Entity> entity) {
		GetInstance()->_selectedEntities.push_back(entity);
	}

	void Toolbox::RemoveSelectedEntity(std::shared_ptr<Entity> entity) {
		auto it = std::find(GetInstance()->_selectedEntities.begin(), GetInstance()->_selectedEntities.end(), entity);
		if (it != GetInstance()->_selectedEntities.end()) {
			GetInstance()->_selectedEntities.erase(it);
		}
	}

	void Toolbox::RemoveSelectedEntity(int index) {
		if (index < 0 || index >= GetInstance()->_selectedEntities.size()) return;
		GetInstance()->_selectedEntities.erase(GetInstance()->_selectedEntities.begin() + index);
	}

	bool Toolbox::PushTool(const std::shared_ptr<Tool>& tool, bool setCurrent) {
		GetInstance()->_tools.push_back(tool);
		if (setCurrent) SetCurrentTool(tool);
		return true;
	}

	bool Toolbox::RemoveTool(const std::shared_ptr<Tool>& tool) {
		auto it = std::find(GetInstance()->_tools.begin(), GetInstance()->_tools.end(), tool);
		if (it != GetInstance()->_tools.end()) {
			GetInstance()->_tools.erase(it);
			return true;
		}
		return false;
	}
} // namespace sse