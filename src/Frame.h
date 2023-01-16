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
		Frame(const sf::IntRect& rect, bool isFlipped = false, float duration = 0.2f)
		    : Rect(rect), IsFlipped(isFlipped), Duration(duration) {}
		~Frame() = default;

		bool operator==(const Frame& other) const {
			return Rect == other.Rect && IsFlipped == other.IsFlipped && Duration == other.Duration;
		}

		// Frame data
		sf::IntRect Rect;
		bool        IsFlipped;
		float       Duration;
		Frame*      NextFrame     = nullptr;
		Frame*      PreviousFrame = nullptr;
	};
} // namespace sse
