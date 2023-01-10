//
// Created by abdoulayedia on 09.01.2023
//
#pragma once

#include "constants.h"
#include "layers/Layer.h"

namespace sse {
	// Viewport
	class Viewport: public Layer {
	  public:
		Viewport()  = default;
		~Viewport() = default;

		void OnUpdate(float dt) override;
		void OnRenderUI() override;
	};
} // namespace sse
