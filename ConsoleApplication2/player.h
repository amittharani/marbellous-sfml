#include<SFML/Graphics.hpp>
class player
{
public:

	sf::Sprite sp;
	sf::Vector2f position;
	float bottom, left, right, top;
	int dir = 0;
	int type;

	player(sf::Sprite sprite, sf::Vector2f pos, int typ);
	void update();
	player();

};