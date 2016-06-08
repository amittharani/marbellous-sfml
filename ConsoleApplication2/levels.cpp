#include "Header.h"
#include<fstream>
#include<iostream>
void levelselect(sf::RenderWindow &window)
{
	std::vector <int> levelscore;
	//int levelscore[9];
	std::ifstream levels("resources/levels.txt");
	if (levels.is_open())
	{
		int x;
		while (!levels.eof())
		{
			levels >> x;
			levelscore.push_back(x);
		}
		levelscore.pop_back();		//for the trailing space
	}
	

	sf::Text numbers[9];
	sf::Font font;
	std::string empty;
	font.loadFromFile("resources/HARNGTON.TTF");
	for (int i = 0; i < 9; i++)
	{
		empty = "";
		//if (i>9)
			//empty += (i / 10)+49;
		empty += (i % 10)+49;
		numbers[i].setFont(font);
		numbers[i].setString(empty);
		numbers[i].setCharacterSize(40);
		numbers[i].setPosition(120 + (i % 4) * 145, 140 + (i / 4) * 135);
	}
	sf::RectangleShape box[9];
	for (int i = 0; i < 9; i++)
	{
		box[i].setFillColor(sf::Color(176, 196, 222));	//b0c4de
		box[i].setSize(sf::Vector2f(85, 85));
		box[i].setPosition(90 + (i % 4) * 145, 125 + (i / 4) * 135);	
	}
	sf::Texture startexture;
	startexture.loadFromFile("marbles/starlevel.png");
	sf::Sprite starsprite[9];
	for (int i = 0; i < 9; i++)
	{
		starsprite[i].setTexture(startexture);
		
		starsprite[i].setPosition(90 + (i % 4) * 145, 210 + (i / 4) * 135);
	}

	int levelselect = 0;
	
	sf::RectangleShape select(sf::Vector2f(85, 85));
	select.setFillColor(sf::Color(0, 0, 0, 45));
	select.setPosition(90, 125);
	while (window.isOpen())
	{
		/*
		for (int i = 0; i < levelscore.size(); i++)
			std::cout << levelscore[i] << " ";
		std::cout << "\n";	
		*/
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased)
			{
				
				if (event.key.code == (sf::Keyboard::Right))
					levelselect++;
				if (event.key.code == (sf::Keyboard::Left))				
					levelselect--;								
				if (event.key.code == (sf::Keyboard::Down))
					levelselect+=4;
				if (event.key.code == (sf::Keyboard::Up))
					levelselect -= 4;

				if (event.key.code == (sf::Keyboard::Return))								
						play(window,levelselect,levelscore);
									
				if (levelselect < 0)
					levelselect +=9;

				levelselect %= 9;			
				select.setPosition(90 + (levelselect % 4) * 145, 125 + (levelselect / 4) * 135);
			}
		}
		

		for (int i = 0; i < 9; i++)
		{			
			window.draw(box[i]);
			window.draw(numbers[i]);
			starsprite[i].setTextureRect(sf::IntRect(0, 0, levelscore[i] * 28, 26));
			window.draw(starsprite[i]);
		}

		window.draw(select);
		window.display();
		window.clear((sf::Color(228, 228, 228)));
	}

		
}