#include <SFML/Graphics.hpp>
#include <iostream> //for debugging
#include "Enemy.h"
#include "Player.h"
#include <vector>

int main()
{
	std::string fileLoc = "C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Textures\\";//Texture File Location
	int res[2] = { 1000, 800 }; // set resolution
	srand(time(0)); //seed rand() ?
	sf::RenderWindow window(sf::VideoMode(res[0], res[1]), "SFML works!");//create game window
	sf::RectangleShape windRect(sf::Vector2f(res[0], res[1]));//background
	//windRect.setFillColor(sf::Color::Green);
	sf::Texture background;
	if (!background.loadFromFile(fileLoc + "Space.png"))
	{
		std::cout << "ERROR IN SPACE TEXTURE LOADING\n";
	}
	windRect.setTexture(&background);

	sf::FloatRect windBound = windRect.getGlobalBounds();//get bounds for windows

	sf::Texture enTexture; //85 x 107
	if (!enTexture.loadFromFile(fileLoc + "koreaEnemy.png"))
	{
		std::cout << "ERROR IN ENEMY TEXTURE LOADING\n";
	}

	sf::Texture plTexture; //78 x 108
	if (!plTexture.loadFromFile(fileLoc + "playerChar.png"))
	{
		std::cout << "ERROR IN PLAYER TEXTURE LOADING\n";
	}
	
	std::vector<Enemy> enVector;
	for (int i = 0; i < 3; i++) //will generate multiple enemies with random positions
	{
		Enemy enemy(res[0] ,res[1], 0.5 , enTexture); //create new enemy
		enemy.setSize(85, 107); //set size of enemy based on png texture
		enVector.push_back(enemy); //plug it into vector
	}

	Player player(res[0] / 2, 900, 0.2f, res[0], res[1], 0.5, plTexture); //xpos, ypos, speed, xbound, ybound, scale, texture
	player.setSize(78, 108); //set size of player based on png texture
	while (window.isOpen()) //Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(windRect);
		//draw all elements here RENDERING WORKS :D
		for (std::vector<Enemy>::iterator i = enVector.begin(); i != enVector.end(); ++i) //Iterating through vectors
		{
			i->main();
			for (std::vector<Enemy>::iterator k = enVector.begin(); k != enVector.end(); ++k)
			{
				if (k != i)//only check against other enemy ERROR HERE
				{
					if (i->getBoundBox().intersects(k->getBoundBox()))//intersects other enemy
					{
						i->randPos();
					}
				}
				if (i->getBoundBox().intersects(player.getBoundBox())) // intersects player
				{
					i->randPos();
				}
			}
			window.draw(i->getSprite());//draw Enemies
		}
		player.main();
		window.draw(player.getSprite()); //draw Player
		 
		window.display();
	}

	return 0;
}