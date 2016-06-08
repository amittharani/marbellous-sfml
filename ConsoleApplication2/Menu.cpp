#include "Header.h"
#include<SFML/Audio.hpp>
int main()
{
	sf::Font font;
	sf::Music music;
	font.loadFromFile("resources/BELLB.TTF");
	sf::Text title,how_to,exit,level;
	sf::Color custom(100, 100, 100, 100), selection(0, 0, 0, 50);
	title.setColor(custom);
	title.setFont(font);
	title.setCharacterSize(50);
	how_to.setFont(font);
	how_to.setColor(custom);
	exit.setFont(font);
	exit.setColor(custom);
	level.setFont(font);
	level.setColor(custom);
	
	music.openFromFile("resources/music.ogg");
	music.play();
	music.setLoop(true);
	
	title.setString("marbellous");
	how_to.setString("How to play");
	exit.setString("exit");
	level.setString("play");

	title.setPosition(220, 80);
	//how_to.setPosition(220, 260);
	level.setPosition(220, 310);
	exit.setPosition(220, 410);

	int selected=0;
	sf::Vector2f boxsize(300, 80);
	sf::RectangleShape box(boxsize), box1(boxsize), box2(boxsize);
	//box.setPosition(200, 250);
	box1.setPosition(200, 300);
	box2.setPosition(200, 400);
	box.setOutlineThickness(2);
	box1.setOutlineThickness(2);
	box2.setOutlineThickness(2);
	box1.setFillColor(selection);
	//box1.setFillColor(sf::Color::Transparent);
	box2.setFillColor(sf::Color::Transparent);
	
	sf::RenderWindow rw(sf::VideoMode(700, 600),"");
	rw.setFramerateLimit(630);
	//sf::View rwview;
	//rwview.setCenter(350, 300);
	//rw.setView(rwview);
	while (rw.isOpen())
	{
		sf::Event event;
		while (rw.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				rw.close();
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code==(sf::Keyboard::Down))
					selected++;
				if (event.key.code == (sf::Keyboard::Up))
				{
					selected--;
					if (selected < 0)
						selected = 1;
				}
				if (event.key.code == (sf::Keyboard::Return))
				{
					if (selected == 1)
						rw.close();
					if (selected == 0)
					{
						levelselect(rw);
					}
				}
				selected %= 2;

				if (selected == 0)
					box1.setFillColor(selection);
				else
					box1.setFillColor(sf::Color::Transparent);
				if (selected == 1)
					box2.setFillColor(selection);
				else
					box2.setFillColor(sf::Color::Transparent);
				/*if (selected == 2)
					box2.setFillColor(selection);
				else
					box2.setFillColor(sf::Color::Transparent);	*/
			}

		}
		
		//rw.draw(box);	
		rw.draw(box1);	
		rw.draw(box2);

		rw.draw(title);
		//rw.draw(how_to);
		rw.draw(level);
		rw.draw(exit);

		rw.display();
		rw.clear(sf::Color(228, 228, 228));
	}
	return 0;
}