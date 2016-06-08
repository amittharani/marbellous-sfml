#include "player.h"

player::player(sf::Sprite sprite, sf::Vector2f pos, int typ)
	{
		sp = sprite;
		position = pos;
		sp.setPosition(position);
		type = typ;

	}
	
void player::update()
	{
		bottom = sp.getPosition().y + 75;
		right = sp.getPosition().x + 75;
		left = sp.getPosition().x;
		top = sp.getPosition().y;
	}

player::player(){}
