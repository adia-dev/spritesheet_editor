//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include "Input.h"
#include "SpriteEntity.h"
#include "constants.h"

namespace sse {
	// Tool
	class Tool {
	  public:
		Tool(): _entity(nullptr), _name("Tool") {}
		Tool(std::shared_ptr<SpriteEntity>& entity): _entity(entity) {}
		Tool(std::shared_ptr<SpriteEntity>& entity, const std::string& name): _entity(entity), _name(name) {}
		virtual ~Tool() = default;

		virtual bool HandleSFMLEvent(sf::Event& event);

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnMouseMove() {}
		virtual void OnMouseLeave() {}
		virtual void OnMouseEnter() {}

		virtual void OnMouseButtonUp(sf::Mouse::Button button) {}
		virtual void OnMouseButtonDown(sf::Mouse::Button button) {}
		virtual void OnMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {}

		virtual void OnKeyDown(sf::Keyboard::Key key) {}
		virtual void OnKeyUp(sf::Keyboard::Key key) {}

		virtual void OnRender(sf::RenderTarget& target) = 0;
		virtual void OnUpdate(float dt) {}

		void                          SetEntity(std::shared_ptr<SpriteEntity>& entity) { _entity = entity; }
		std::shared_ptr<SpriteEntity> GetEntity() const { return _entity; }

		void                 SetWorkspaceRect(const sf::FloatRect& rect) { _workspaceRect = rect; }
		const sf::FloatRect& GetWorkspaceRect() const { return _workspaceRect; }

		void               SetName(const std::string& name) { _name = name; }
		const std::string& GetName() const { return _name; }

	  protected:
		std::string                          _name;
		std::shared_ptr<SpriteEntity>        _entity;
		sf::FloatRect                        _workspaceRect;
		std::vector<std::shared_ptr<Entity>> _selectedEntities;
	};
} // namespace sse
