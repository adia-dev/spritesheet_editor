//
// Created by abdoulayedia on 15.01.2023
//
#pragma once

#include <exception>
#include <stdexcept>

namespace sse {

	class Entity;
	class SpriteEntity;
	// Visitor
	class Visitor {
	  public:
		Visitor()  = default;
		~Visitor() = default;

		virtual void Visit(const Entity* e) { throw std::runtime_error("Not implemented yet !"); }
		virtual void Visit(const SpriteEntity* se) { throw std::runtime_error("Not implemented yet !"); }

	  private:
	};
} // namespace sse
