//
// Created by abdoulayedia on 09.01.2023
//
#include "Viewport.h"

namespace sse {
	void Viewport::OnUpdate(float dt) {
		// std::cout << "Update from the viewport: " << dt << std::endl;
	}
	void Viewport::OnRenderUI() {
		ImGui::Begin("Viewport", &(this->_visible));

		ImGui::End();
	}
} // namespace sse