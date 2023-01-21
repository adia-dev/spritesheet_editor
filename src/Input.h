//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include "constants.h"

#include <chrono>

namespace sse {

	enum class KeyState {
		NONE = -1,
		PRESSED,
		RELEASED,
		DOWN,
	};

	struct MouseState {
		sf::Vector2f downPosition;
		KeyState     state;
	};

	// Inputs
	class Input {
	  public:
		static void HandleEvents(sf::Event& event);
		static bool IsKeyDown(sf::Keyboard::Key key);
		static bool IsMouseButtonDown(sf::Mouse::Button button);

		static sf::Vector2f                             GetDirection();
		static std::map<sf::Keyboard::Key, KeyState>&   GetKeyboardInputs() { return GetInstance()->_keyboardInputs; }
		static std::map<sf::Mouse::Button, MouseState>& GetMouseInputs() { return GetInstance()->_mouseInputs; }

		static sf::Vector2f& GetMousePosition() { return GetInstance()->_mousePos; }
		static sf::Vector2f  GetMouseDelta() { return GetInstance()->_mousePos - GetInstance()->_lastMousePos; }
		static sf::Vector2f& GetMouseDownPosition(sf::Mouse::Button button) {
			return GetInstance()->_mouseInputs[button].downPosition;
		}

		static ImVec2 GetMousePositionImGui() { return ImVec2(GetInstance()->_mousePos.x, GetInstance()->_mousePos.y); }

	  private:
		std::map<sf::Keyboard::Key, KeyState>   _keyboardInputs;
		std::map<sf::Mouse::Button, MouseState> _mouseInputs;
		sf::Vector2f                            _mousePos;
		sf::Vector2f                            _lastMousePos;

		inline static Input* _instance = nullptr;

	  public:
		static Input* GetInstance() {
			if (!_instance) _instance = new Input();

			return _instance;
		}

		static std::string KeyToString(sf::Keyboard::Key key);
		static std::string MouseButtonToString(sf::Mouse::Button button);
	};
} // namespace sse
