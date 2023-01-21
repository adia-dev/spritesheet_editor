//
// Created by abdoulayedia on 21.01.2023
//
#pragma once

#include "Tool.h"

namespace sse {
	// SelectTool
	class SelectTool: public Tool {
	  public:
		SelectTool(): Tool() {}
		SelectTool(std::shared_ptr<SpriteEntity>& entity): Tool(entity) {}
		~SelectTool() = default;

		void OnMouseDown(const sf::Vector2f mousePos) override;
		void OnMouseUp(const sf::Vector2f mousePos) override;
		void OnMouseMove(const sf::Vector2f mousePos) override;
		void OnRender(sf::RenderTarget& target) override;
		void OnUpdate(float dt) override;

	  private:
		sf::RectangleShape _selectionRect;
	};
} // namespace sse
