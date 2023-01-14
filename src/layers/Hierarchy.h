//
// Created by abdoulayedia on 14.01.2023
//
#pragma once

#include "Layer.h"

namespace sse {
	// Hierarchy
	class Hierarchy: public Layer {
	  public:
		Hierarchy();
		~Hierarchy() override = default;

		void OnAttach() override;
		void OnHandleSFMLEvent(sf::Event& event) override;
		void OnUpdate(float dt) override;
		void OnRenderUI() override;
	};
} // namespace sse
