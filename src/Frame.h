//
// Created by abdoulayedia on 16.01.2023
//
#pragma once

#include "constants.h"

namespace sse {
	// Frame
	struct Frame {
	  public:
		Frame() = default;
		Frame(const sf::IntRect& rect, const std::string& name = "Frame", bool isFlipped = false, float duration = 0.0f)
		    : Rect(rect), Name(name), IsFlipped(isFlipped), Duration(duration) {}
		~Frame() = default;

		bool operator==(const Frame& other) const {
			return Rect == other.Rect && Name == other.Name && IsFlipped == other.IsFlipped &&
			       Duration == other.Duration;
		}

		// Frame data
		std::string Name;
		sf::IntRect Rect;
		bool        IsFlipped;
		float       Duration;
		Frame*      NextFrame     = nullptr;
		Frame*      PreviousFrame = nullptr;
	};
} // namespace sse
