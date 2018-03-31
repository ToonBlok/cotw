#include "item.h"

using namespace std;

namespace cotw {

Item::Item(std::string _name, sf::Image& _image, bool collected)
{
	name = _name;
	image = _image;
}

Item::~Item()
{
}

}
