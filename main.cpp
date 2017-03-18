#include <SFML/Graphics.hpp>
#include <iostream> //for debugging
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include <vector>

int main()
{
	std::string fileLoc = "C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Textures\\";//Texture File Location
	int res[2] = { 1000, 800 }; // set resolution
	srand(time(0)); //seed rand() 
	sf::RenderWindow window(sf::VideoMode(res[0], res[1]), "SFML works!");//create game window
	
	sf::Texture bgText;
	if (!bgText.loadFromFile(fileLoc + "Space.png"))
	{
		std::cout << "ERROR IN SPACE TEXTURE LOADING\n";
	}
	Background background(bgText, 0.1, 0, 0, 1);
	/*sf::RectangleShape windRect(sf::Vector2f(res[0], res[1]));//background
	//windRect.setFillColor(sf::Color::Green);
	sf::Texture background;
	if (!background.loadFromFile(fileLoc + "Space.png"))
	{
		std::cout << "ERROR IN SPACE TEXTURE LOADING\n";
	}
	windRect.setTexture(&background);

	sf::FloatRect windBound = windRect.getGlobalBounds();//get bounds for windows*/

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
		enVector.push_back(enemy); //plug it into vector
		enVector[i].setPos(i * 100, 0);
	}

	Player player(res[0] / 2, 900, 0.2f, res[0], res[1], 0.5, plTexture); //xpos, ypos, speed, xbound, ybound, scale, texture
	player.setPos(200, 200);

	while (window.isOpen()) //Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		//draw all elements here

		for (int i = 0; i != background.getSpriteVector().size(); i++)//draw background
		{
			if (background.getSprite(1).getGlobalBounds().height >= res[1] && background.getOrient()) //background 1 is at bottom, and orient is 1
			{
				background.resetIter();//reverse background formation
			}
			if (background.getSprite(0).getGlobalBounds().height >= res[1] && !background.getOrient()) //background 0 is at bottom, and orient is 0
			{
				background.resetIter();
			}
			background.main();
			window.draw(background.getSprite(i));
		}

		for (std::vector<Enemy>::iterator i = enVector.begin(); i != enVector.end(); ++i) //draw enemies
		{
			i->main();
			for (std::vector<Enemy>::iterator k = enVector.begin(); k != enVector.end(); ++k)
			{
				if (k != i)//only check against other enemy ERROR HERE
				{
					if (i->getBoundBox().intersects(k->getBoundBox()))//intersects other enemy (always true, need to check for fix)
					{
						std::cout << "intersecting enemy" << std::endl;
						//i->randPos();
					}
				}
				if (i->getBoundBox().intersects(player.getBoundBox())) // intersects player
				{
					std::cout << "intersecting player" << std::endl;
					//i->randPos();
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