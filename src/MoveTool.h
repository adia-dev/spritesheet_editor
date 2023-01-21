//
// Created by abdoulayedia on 21.01.2023
//
#pragma once

#include "Tool.h"

namespace sse {
	// MoveTool
	class MoveTool: public Tool {
	  public:
		MoveTool(): Tool() {}
		MoveTool(std::shared_ptr<SpriteEntity>& entity): Tool(entity) {}
		~MoveTool() = default;

		void OnMouseDown(const sf::Vector2f mousePos) override;
		void OnMouseUp(const sf::Vector2f mousePos) override;
		void OnMouseMove(const sf::Vector2f mousePos) override;
		void OnRender(sf::RenderTarget& target) override;
		void OnUpdate(float dt) override;

	  private:
	};
} // namespace sse
