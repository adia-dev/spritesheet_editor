//
// Created by abdoulayedia on 12.01.2023
//
#pragma once

#include "constants.h"

namespace sse {
	// AssetManager
	class AssetManager {
	  public:
		static AssetManager& GetInstance() {
			static AssetManager instance;
			return instance;
		}

		static sf::Texture& GetTexture(const std::string& id) {
			auto& instance = GetInstance();
			auto& texMap   = instance._textures;
			auto  find     = texMap.find(id);
			if (find != texMap.end()) {
				return find->second;
			}

			sf::Texture newTexture;
			newTexture.loadFromFile(id);
			texMap.emplace(id, newTexture);
			return texMap[id];
		}

	  private:
		std::map<std::string, sf::Texture> _textures;
	};
} // namespace sse
