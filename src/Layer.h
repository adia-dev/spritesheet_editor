//
// Created by abdoulayedia on 09.01.2023
//
#pragma once

#include "constants.h"

namespace sse {
	// Layer
	class Layer {
	  public:
		Layer()          = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual bool OnHandleEvents(sf::Event& event) { return false; }
		virtual void OnHandleImGuiEvent(ImGuiIO& io) {}
		virtual void OnUpdate(float dt) {}
		virtual void OnRenderUI() {}

		void Show() { _visible = true; }

		void Hide() { _visible = false; }

		bool IsVisible() const { return _visible; }

	  protected:
		bool _visible = true;
	};
} // namespace sse
