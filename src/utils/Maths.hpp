//
// Created by abdoulayedia on 22.01.2023
//
#pragma once

#include "constants.h"

namespace sse {
	// Maths
	class Maths {
	  public:
		template<typename T>
		static T Clamp(T value, T min, T max) {
			if (value < min) {
				return min;
			}
			if (value > max) {
				return max;
			}
			return value;
		}

		template<typename T>
		static T Lerp(T a, T b, float t) {
			return a + (b - a) * t;
		}

		template<typename T>
		static sf::Vector2<T> Lerp(sf::Vector2<T> a, sf::Vector2<T> b, float t) {
			return sf::Vector2<T>(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
		}

		template<typename T>
		static T Map(T value, T min, T max, T newMin, T newMax) {
			return Lerp(newMin, newMax, (value - min) / (max - min));
		}

		template<typename T>
		static T Smoothstep(T edge0, T edge1, T x) {
			T t = Clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
			return t * t * (3 - 2 * t);
		}

		template<typename T>
		static T Smoothstep(T edge0, T edge1, T x, T min, T max) {
			return Map(Smoothstep(edge0, edge1, x), 0.f, 1.f, min, max);
		}

		template<typename T>
		static float Magnitude(sf::Vector2<T> vector) {
			return std::sqrt(vector.x * vector.x + vector.y * vector.y);
		}

		template<typename T>
		static float Distance(sf::Vector2<T> a, sf::Vector2<T> b) {
			return Magnitude(a - b);
		}

		template<typename T>
		static float Dot(sf::Vector2<T> a, sf::Vector2<T> b) {
			return a.x * b.x + a.y * b.y;
		}

		template<typename T>
		static float Angle(sf::Vector2<T> a, sf::Vector2<T> b) {
			return std::acos(Dot(a, b) / (Magnitude(a) * Magnitude(b)));
		}

		template<typename T>
		static sf::Vector2<T> Normalize(sf::Vector2<T> vector) {
			return sf::Vector2<T>(vector.x / Magnitude(vector), vector.y / Magnitude(vector));
		}

		template<typename T>
		static sf::Rect<T> ImRectToSFRect(const ImRect& rect) {
			return sf::Rect<T>(rect.Min.x, rect.Min.y, rect.Max.x - rect.Min.x, rect.Max.y - rect.Min.y);
		}

		template<typename T>
		static sf::Vector2f WorldToRenderTarget(sf::Vector2<T> worldPos, const sf::RenderTarget& renderTarget) {
			return renderTarget.mapPixelToCoords(
			    sf::Vector2i(worldPos.x - ImGui::GetStyle().WindowPadding.x,
			                 worldPos.y - ImGui::GetStyle().WindowPadding.y - ImGui::GetFrameHeight()));
		}

		static sf::Vector2f WorldToRenderTarget(ImVec2 worldPos, const sf::RenderTarget& renderTarget) {
			return renderTarget.mapPixelToCoords(
			    sf::Vector2i(worldPos.x - ImGui::GetStyle().WindowPadding.x,
			                 worldPos.y - ImGui::GetStyle().WindowPadding.y - ImGui::GetFrameHeight()));
		}

		static sf::FloatRect IntersectedArea(const sf::FloatRect& a, const sf::FloatRect& b) {
			sf::FloatRect result;
			result.left   = std::max(a.left, b.left);
			result.top    = std::max(a.top, b.top);
			result.width  = std::min(a.left + a.width, b.left + b.width) - result.left;
			result.height = std::min(a.top + a.height, b.top + b.height) - result.top;
			return result;
		}

		static sf::IntRect FloatToIntRect(const sf::FloatRect& rect) {
			return sf::IntRect(rect.left, rect.top, rect.width, rect.height);
		}

		static sf::FloatRect IntToFloatRect(const sf::IntRect& rect) {
			return sf::FloatRect(rect.left, rect.top, rect.width, rect.height);
		}
	};
} // namespace sse
