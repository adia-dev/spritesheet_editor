//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include "constants.h"

namespace sse {

	enum class KeyState {
		NONE = -1,
		PRESSED,
		RELEASED,
		DOWN,
	};

	// Inputs
	class Input {
	  public:
		static void         HandleEvents(sf::Event& event);
		static bool         IsKeyDown(sf::Keyboard::Key key);
		static bool         IsMouseButtonDown(sf::Mouse::Button button);
		static sf::Vector2f GetDirection();

		static std::map<sf::Keyboard::Key, KeyState>& GetKeyboardInputs() { return GetInstance()->_keyboardInputs; }
		static std::map<sf::Mouse::Button, KeyState>& GetMouseInputs() { return GetInstance()->_mouseInputs; }
		static sf::Vector2f&                          GetMousePosition() { return GetInstance()->_mousePos; }
		static ImVec2 GetMousePositionImGui() { return ImVec2(GetInstance()->_mousePos.x, GetInstance()->_mousePos.y); }

		static void SetMousePosition(const sf::Vector2f& mousePos) { GetInstance()->_mousePos = mousePos; }
		static void SetViewportMousePosition(const sf::Vector2f& mousePos) {
			GetInstance()->_viewportMousePos = mousePos;
		}

	  private:
		std::map<sf::Keyboard::Key, KeyState> _keyboardInputs;
		std::map<sf::Mouse::Button, KeyState> _mouseInputs;
		sf::Vector2f                          _mousePos;
		sf::Vector2f                          _viewportMousePos;

		inline static Input* _instance = nullptr;

	  public:
		static Input* GetInstance() {
			if (!_instance) _instance = new Input();

			return _instance;
		}

		friend std::ostream& operator<<(std::ostream& os, const Input& input) {
			os << "Keyboard Inputs:" << std::endl;
			for (const auto& [key, state] : input.GetKeyboardInputs()) {
				os << "  " << KeyToString(key) << ": ";
				switch (state) {
					case KeyState::NONE:
						os << "NONE";
						break;
					case KeyState::PRESSED:
						os << "PRESSED";
						break;
					case KeyState::RELEASED:
						os << "RELEASED";
						break;
					case KeyState::DOWN:
						os << "DOWN";
						break;
				}
				os << std::endl;
			}

			os << "\nMouse Inputs:" << std::endl;
			for (const auto& [button, state] : input.GetMouseInputs()) {
				os << "  " << Input::MouseButtonToString(button) << ": ";
				switch (state) {
					case KeyState::NONE:
						os << "NONE";
						break;
					case KeyState::PRESSED:
						os << "PRESSED";
						break;
					case KeyState::RELEASED:
						os << "RELEASED";
						break;
					case KeyState::DOWN:
						os << "DOWN";
						break;
				}
				os << std::endl;
			}

			os << "\nMouse Position: " << input.GetMousePosition().x << ", " << input.GetMousePosition().y << std::endl;

			return os;
		}

		static std::string KeyToString(sf::Keyboard::Key key);
		static std::string MouseButtonToString(sf::Mouse::Button button);
	};
} // namespace sse
