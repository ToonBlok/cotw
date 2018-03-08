#include <iostream>
#include "texture_manager.h"

using namespace std;

namespace cotw {

Texture_manager::Texture_manager(){}

Texture_manager::~Texture_manager(){}

void Texture_manager::set_texture(std::string filename) 
{

}

sf::Texture Texture_manager::get_texture(std::string filename)
{
	sf::Texture texture;
	sf::Image image;
	image.loadFromFile(filename);

	if (!texture.loadFromImage(image))
		cout << "texture \"" + filename + "\" was not found!" << endl; 

	//textures.insert(filename, texture);
	textures[filename] = texture;
	return textures[filename];
}

}
