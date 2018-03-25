#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

namespace cotw {

class Texture_manager
{
	public:
		Texture_manager();
		~Texture_manager();

		void set_texture(std::string);
		sf::Texture& get_texture(std::string);
	private:
		std::unordered_map<std::string, sf::Texture> textures;
};

}

#endif
