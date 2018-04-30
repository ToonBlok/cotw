#include <iostream>
#include "TextureManager.h"

using namespace std;

namespace cotw {

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){}

void TextureManager::set_texture(std::string filename) 
{
	//for (unsigned int i = 0; i < textures.size(); i++)
	//{
	//	cout << textures[i].first << endl;
	//}
	//for (auto it : textures) 
	//	std::cout << it.first << endl;;

}

sf::Texture& TextureManager::get_texture(std::string filename)
{
	//for (auto it : textures) 
	//	if (filename == it.first)
	//		found = true;

	std::unordered_map<std::string, sf::Texture>::const_iterator got = textures.find (filename);


	if ( got == textures.end() )
	{
		sf::Texture texture;
		sf::Image image;
		image.loadFromFile(filename);

		if (!texture.loadFromImage(image))
			cout << "texture \"" + filename + "\" was not found!" << endl; 

		textures[filename] = texture;
	}
	return textures[filename];
}

}
