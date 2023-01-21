#include "Tool.h"

namespace sse {
	bool Tool::HandleSFMLEvent(sf::Event& event) {
		switch (event.type) {
			case sf::Event::MouseButtonPressed:
				OnMouseButtonDown(event.mouseButton.button);
				break;

			case sf::Event::MouseButtonReleased:
				OnMouseButtonUp(event.mouseButton.button);
				break;

			case sf::Event::MouseMoved:
				OnMouseMove();
				break;

			case sf::Event::MouseEntered:
				OnMouseEnter();
				break;

			case sf::Event::MouseLeft:
				OnMouseLeave();
				break;

			case sf::Event::MouseWheelScrolled:
				OnMouseWheelScroll(event.mouseWheelScroll);
				break;

			case sf::Event::KeyPressed:
				OnKeyDown(event.key.code);
				break;

			case sf::Event::KeyReleased:
				OnKeyUp(event.key.code);
				break;

			default:
				break;
		}
	}
} // namespace sse