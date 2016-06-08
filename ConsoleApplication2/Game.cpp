#pragma once
#include<iostream>
#include<fstream>
#include "player.h"
#include "header.h"

int map[10][10];
float const movespeed = 1.25f;
enum { none,le, ri, to, bo };
int movement=none;
bool matchColor;
int (*playerConfig)[3];
int ballcount;
int unmatched;

sf::Vector2f *velocity,pvelocity;

bool zeroVelocity()
{
	
	for (int i = 0; i < ballcount; i++)
		if (velocity[i].x != 0 || velocity[i].y != 0)
			return false;
	return true;
}

void tilecollision(player &p1, sf::Vector2i loadcounter)
{
	float bottom, left, right, top;
	for (int i = 1; i <= loadcounter.x; i++)
	{
		for (int j = 0; j < loadcounter.y; j++)
		{
			if (map[i-1 ][j] == 0)
			{
				bottom = j * 75 + 75;
				top = j * 75;
				left = i * 75;
				right = i * 75 + 75;
				//std::cout << left << "  " << right << "  " << top << "  " << bottom << std::endl;

				if (!(p1.right <= left || p1.left >= right || p1.bottom <= top || p1.top >= bottom))

				{

					if (p1.left + 4 >= right)
					{
						p1.dir = 1;
						std::cout << "left collision" << std::endl;
						//p1.collided = le;

					}
					else	if (p1.right - 4 <= left)
					{
						p1.dir = 2;
						std::cout << "right collision" << std::endl;
						//p1.collided = ri;

					}
					else if (p1.bottom - 4 <= top)
					{
						p1.dir = 3;
						std::cout << "bottom collision" << std::endl;
						//p1.collided = bo;
					}
					else if (p1.top + 4 >= bottom)
					{
						p1.dir = 4;
						std::cout << "top collision" << std::endl;
						//p1.collided = to;
					}
					goto here;

				}

				else
				{
					p1.dir = 0;

				}

			}
		}
	}
here:
	;
}

void direction(player &p1, sf::Vector2f &velocity)
{
	if (p1.dir != 0)
	{
		velocity = sf::Vector2f(0, 0);
		if (p1.dir == 1)
			p1.sp.move(movespeed, 0);
		else if (p1.dir == 2)
			p1.sp.move(-movespeed, 0);
		else if (p1.dir == 3)
			p1.sp.move(0, -movespeed);
		else if (p1.dir == 4)
			p1.sp.move(0, movespeed);
	}
}

void loadmap(int l, sf::Vector2i &loadcounter)
{
	std::string s = "maps/map";
	s += (l + 49);
	std::ifstream openfile(s + ".txt");

	//loadcounter = sf::Vector2i(0, 0);
	if (openfile.is_open())
	{
		int x;
		while (!openfile.eof())
		{
			openfile >> x;
			map[loadcounter.x][loadcounter.y] = x;
			if (openfile.peek() == '\n')
			{
				loadcounter.y++;
				loadcounter.x = 0;
			}
			else
				loadcounter.x++;
		}
		loadcounter.y++;
	}
}

void loadconfig(int l,int star[])
{
	std::string s = "balls/ball";
	s += (l+49);
	std::ifstream ballconfig(s+".txt");

	if (ballconfig.is_open())
	{
		int a, b;
		ballconfig >> b;
		playerConfig = new int[b][3];
		velocity = new sf::Vector2f[b];

		ballcount = b;
		for (int i = 0; i < 3; i++)
		{
			ballconfig >> a;
			star[i] = a;
		}

		for (int i = 0; i < ballcount; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ballconfig >> a;
				playerConfig[i][j] = a;
			}

		}
		ballconfig.close();
	}
}
void new_function(player *p,sf::Sprite *sprite){
	for (int i = 0; i < ballcount; i++)
	{
		p[i] = player(sprite[playerConfig[i][2]-1], sf::Vector2f((playerConfig[i][0]+1) * 75, playerConfig[i][1] * 75), playerConfig[i][2]);
	}
}

void playercollision(player *p, sf::Vector2f *velocityx,int ballcount)
{
	for (int i = 0; i < ballcount; i++)
	{
		for (int j = i + 1; j < ballcount; j++)
		{
			
			if ((((p[i].right == p[j].left || p[i].left == p[j].right) && p[j].top == p[i].top) || ((p[i].bottom == p[j].top || p[i].top == p[j].bottom) && p[i].right == p[j].right)) && pvelocity.x == 0 && pvelocity.y == 0)
			{
				if (p[i].type == p[j].type)
				{
					matchColor = true;
					p[j].sp.setPosition(75, 500);
					p[i].sp.setPosition(75, 500);
					p[i].sp.setColor(sf::Color::Transparent);
					p[j].sp.setColor(sf::Color::Transparent);
					unmatched -= 2;
					sf::Vector2f velo;
					if (movement == le)
						velo = sf::Vector2f(-movespeed, 0);
					if (movement == ri)
						velo = sf::Vector2f(movespeed, 0);
					if (movement == to)
						velo = sf::Vector2f(0, -movespeed);
					if (movement == bo)
						velo = sf::Vector2f(0, movespeed);


					for (int i = 0; i < ballcount; i++)
						velocity[i] = velo;

				}

			}

			if (!(p[i].right <= p[j].left || p[i].left >= p[j].right || p[i].bottom <= p[j].top || p[i].top >= p[j].bottom))
			{
				//std::cout << "yeh wala nai h\n yeh wala nai h\n";
				if (p[i].left + 4 >= p[j].right)
				{
					std::cout << "left collision p\n" << std::endl;
					if (movement == le)
					{
						p[i].sp.setPosition(p[j].right, p[j].top);
					}
					else if (movement == ri)
						p[j].sp.setPosition(p[i].left - 75, p[i].top);

				}
				else	if (p[i].right - 4 <= p[j].left)
				{

					std::cout << "right collision p" << std::endl;
					if (movement == le)
					{
						p[j].sp.setPosition(p[i].right, p[i].top);
						//if (left - p[i].right < 0)
						//	sp.move(1, 0);
					}
					else if (movement == ri)
						p[i].sp.setPosition(p[j].left - 75, p[j].top);
				}
				else if (p[i].bottom - 4 <= p[j].top)
				{

					std::cout << "bottom collision p" << std::endl;
					if (movement == to)
					{
						p[j].sp.setPosition(p[i].left, p[i].bottom);
					}
					else if (movement == bo)
						p[i].sp.setPosition(p[j].left, p[j].top - 75);

				}
				else if (p[i].top + 4 >= p[j].bottom)
				{

					std::cout << "top collision p" << std::endl;
					if (movement == to)
					{
						p[i].sp.setPosition(p[j].left, p[j].bottom);
					}
					else if (movement == bo)
						p[j].sp.setPosition(p[i].left, p[i].top - 75);
				}
				velocityx[i] = sf::Vector2f(0, 0);
				velocityx[j] = sf::Vector2f(0, 0);
			}
		}
	}
}
void resetscore(sf::RectangleShape *scorebox,  int *star)
{
	for (int i = 0; i < star[0]; i++)
		scorebox[i].setFillColor(sf::Color::White);
	for (int i = star[0]; i < star[1]; i++)
		scorebox[i].setFillColor(sf::Color(0, 0, 0, 60));
	for (int i = star[1]; i < star[2]; i++)
		scorebox[i].setFillColor(sf::Color(0, 0, 0, 150));
}

void play(sf::RenderWindow &window,int level,std::vector<int> &levelscore)
{
	bool updatescore = true;
	int currentscore = 0;
	float col = 250;
	int count = 0;
	int star[3];
	sf::Vector2i loadcounter(0, 0);

	sf::RectangleShape rect(sf::Vector2f(75, 75));
	sf::Texture tex[4],startex;
	sf::Sprite sprite[4],spstar[3];

	tex[0].loadFromFile("marbles/marble1.png");
	tex[1].loadFromFile("marbles/marble2.png");
	tex[2].loadFromFile("marbles/marble3.png");
	tex[3].loadFromFile("marbles/marble4.png");
	startex.loadFromFile("marbles/stars.png");

	for (int i = 0; i < 3; i++)
	{
		spstar[i].setTexture(startex);
		spstar[i].setTextureRect(sf::IntRect(0, 0, (i + 1) * 45, 42));
		spstar[i].setPosition(240, 400);
	}


	for (int i = 0; i < 4; i++)
		sprite[i].setTexture(tex[i]);

	rect.setFillColor(sf::Color(253, 253, 253));
	//rect.setOutlineThickness(1);
	//rect.setOutlineColor(sf::Color(243, 243, 243));
	sf::Text gayatu,done,back,reset;
	sf::Font f;
	f.loadFromFile("resources/BELLB.TTF");
	gayatu.setFont(f);
	done.setFont(f);
	back.setFont(f);
	reset.setFont(f);
	done.setCharacterSize(45);

	gayatu.setCharacterSize(45);
	gayatu.setString("out of moves");
	gayatu.setPosition(190,400);
	done.setPosition(240, 400);
	back.setPosition(475, 470);
	reset.setPosition(63, 470);
	reset.setColor(sf::Color(0, 0, 0, 150));
	back.setColor(sf::Color(0, 0, 0, 150));
	back.setString("Menu: Esc");
	reset.setString("Reset: R");

	
	loadmap(level,loadcounter);
	loadconfig(level,star);
	unmatched = ballcount;

	player *p = new player[ballcount];
	new_function(p,sprite);

	 sf::RectangleShape *scorebox;
	 sf::RectangleShape backbutton(sf::Vector2f(145, 40)), resetbutton(sf::Vector2f(130, 40));
	 backbutton.setPosition(470, 470);
	 resetbutton.setPosition(55, 470);
	 backbutton.setFillColor(sf::Color::Transparent);
	 resetbutton.setFillColor(sf::Color::Transparent);
	 resetbutton.setOutlineThickness(2);
	 backbutton.setOutlineThickness(2);


	 scorebox = new sf::RectangleShape[star[2]];
	 for (int i = 0; i < star[2]; i++)
	 {

		 scorebox[i].setSize(sf::Vector2f(30, 15));
		 scorebox[i].setPosition(580, 100+i*30);	
	 }
	 resetscore(scorebox, star);

	//sf::RenderWindow window(sf::VideoMode(700, 600), "game window", sf::Style::Close);
	//window.setFramerateLimit(420);
	 sf::RectangleShape shadow(sf::Vector2f(75, 1));
	 sf::RectangleShape shadow2(sf::Vector2f(1, 75));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			new_function(p,sprite);
			count = 0;
			movement = none;
			unmatched = ballcount;
			resetscore(scorebox, star);
			currentscore = 0;
			updatescore = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//count = 0;
			movement = none;
			return;
		}

		if (matchColor)
			if (col--)
			{
				window.clear(sf::Color(210,210,210));
			}
			else
			{
				matchColor = false;
				col = 200;
			}
		else	
			window.clear(sf::Color(228, 228, 228));

		for (int i = 1; i < loadcounter.x-1 ; i++)
		{
			for (int j = 1; j < loadcounter.y-1 ; j++)
			{
			

				if (map[i][j] == 1)
				{
					rect.setPosition((i+1 ) * 75, j * 75);
					window.draw(rect);
									
					if (map[i + 1][j] == 0)
					{
						for (int x = 0; x < 5; x++)
						{						
							shadow2.setPosition((i + 2) * 75 + x, (j)* 75);
							shadow2.setFillColor(sf::Color(128, 128, 128, 244 - (x * 60)));
							window.draw(shadow2);
						}
					}
					if (map[i][j+1] == 0)
					{
						for (int x = 0; x < 5; x++)
						{
							shadow.setPosition((i + 1) * 75, (j + 1) * 75 + x);
							shadow.setFillColor(sf::Color(128, 128, 128, 234 - (x * 40)));
							window.draw(shadow);
						}
					}
					
				}

			}
		}

		if (zeroVelocity() && count <= star[2])
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && movement!= ri)
			{
				pvelocity = sf::Vector2f(movespeed, 0);
				movement = ri;
				count++;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && movement != to)
			{
				pvelocity = sf::Vector2f(0, -movespeed);
				movement = to;
				count++;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && movement != le)
			{
				pvelocity = sf::Vector2f(-movespeed, 0);
				movement = le;
				count++;
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && movement != bo)
			{
				pvelocity = sf::Vector2f(0, movespeed);
				movement = bo;
				count++;
			}
			else pvelocity = sf::Vector2f(0, 0);

			for (int i = 0; i < ballcount; i++)		
				velocity[i] = pvelocity;
		
		}
	
		for (int i = 0; i < ballcount; i++)
			p[i].update();		
	
		for (int i = 0; i < ballcount; i++)	
			tilecollision(p[i], loadcounter);
		
		for (int i = 0; i < ballcount; i++)	
			direction(p[i], velocity[i]);
			
		playercollision(p, velocity, ballcount);

		for (int i = 0; i < ballcount; i++)
		{
			if (count <= star[2])
				p[i].sp.move(velocity[i]);
		}
		if (count>0 && count <= star[2])
			scorebox[count-1].setFillColor(sf::Color::Transparent);
		
		for (int i = 0; i < ballcount; i++)
			//if (count<=star[2])
			window.draw(p[i].sp);

		for (int i = 0; i < star[2]; i++)
		{
		
			window.draw(scorebox[i]);
		}
		if (!unmatched)
		{
			if (count <= star[0])
			{
				window.draw(spstar[2]);
				currentscore = 3;
			}
			else if (count <= star[1])
			{
				window.draw(spstar[1]);
				currentscore = 2;
			}
			else if (count <= star[2])
			{
				window.draw(spstar[0]);
				currentscore = 1;
			}
			if (levelscore[level] < currentscore)
			{ 
				if (updatescore)
				{
					levelscore[level] = currentscore;
					std::cout << "updated score: " << levelscore[level];

					std::ofstream update("resources/levels.txt");
					for (int i = 0; i < levelscore.size(); i++)
						update << levelscore[i]<<" ";
					update.close();

					updatescore = false;
				}
			}
				
		}
		//std::cout << p[4].sp.getPosition().x << "\t" << p[4].sp.getPosition().y << "\n";
		//std::cout << p1.left << "\t" << p1.right << "\t" << p2.left << "\t" << p2.right << "\n";
		//std::cout << pvelocity.x << pvelocity.y << "\n";
		if (count == ((star[2])+1) && unmatched)
		{
			window.draw(gayatu);
			for (int i = 0; i < ballcount; i++)
				velocity[i] = sf::Vector2f(0, 0);
		}	
		window.draw(backbutton);
		window.draw(resetbutton);
		window.draw(reset);
		window.draw(back);
		window.display();
	}
	
	//return 0;
}