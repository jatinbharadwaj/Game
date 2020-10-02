#include<iostream>
// #include "./SFML/Graphics.hpp"
// #include"./SFML/Window.hpp"
// #include"./SFML/System.hpp"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<math.h>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<string>
#include<ctime>
#include <unistd.h>

//LENGTH OF VECTOR: |V| = sqrt(V.x^2 + V.y^2)
//NORMALIZE VECTOR: U = V / |V|

using namespace sf;

class Bullet
{
public:
	CircleShape shape;
	Vector2f currVelocity; 
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(10.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};

int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "Asteroids", Style::Default);
	window.setFramerateLimit(60);


	int score=0;
	time_t start,finish;
	time(&start);
	Text text;
	Font font;
	font.loadFromFile("consola.ttf");
	text.setFont(font);
	text.setPosition(40.f,50.f);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);




	//Player
	CircleShape player(20.f);
	player.setFillColor(Color::Transparent);
	player.setPointCount(3);
	player.setOutlineThickness(5.f);
	player.setOutlineColor(Color::Yellow);
	player.setPosition(window.getSize().x/2, window.getSize().y/2);

	//Bullets
	Bullet b1;
	std::vector<Bullet> bullets;

	//Enemy
	CircleShape enemy(40.f);
	// enemy.setFillColor(Color(rand()%255,rand()%255,rand()%255));
	// enemy.setSize(Vector2f(50.f, 50.f));
	int spawnCounter = 20;

	std::vector<CircleShape> enemies;

	//Vectors
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	while (window.isOpen())
	{
		Event event;
		enemy.setFillColor(Color(rand()%255,rand()%255,rand()%255));
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Update
		//Vectors
		playerCenter = Vector2f(player.getPosition().x-player.getRadius() , player.getPosition().y-player.getRadius());   //<-
		//playerCenter = player.getOrigin();
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		float PI = 3.14159265f;
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		player.setRotation(deg + 90);

		//Set Final Rotation of Ship
		// std::cout << deg << "\n";

		//Player
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.move(-10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.move(10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.move(0.f, -10.f);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.move(0.f, 10.f);

		//Enemies
		if (spawnCounter < 30)
			spawnCounter++;

		if(spawnCounter >= 30 && enemies.size() < 50) 
		{				
			enemy.setPosition(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));    // <-
			enemies.push_back(CircleShape(enemy));
			spawnCounter = 0;
		}

        // MOVEMENT OF ASTEROIDS
        for (size_t i = 0; i < enemies.size(); i++)
		{
            float movex = rand()%2 - rand()%3;
            float movey = rand()%6 - rand()%3;

			enemies[i].move(movex, movey);

			if (enemies[i].getPosition().y > window.getSize().y)
				enemies.erase(enemies.begin() + i);
		}

		//Shooting
		if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Space))
		{
			b1.shape.setPosition(playerCenter);
			b1.currVelocity = aimDirNorm * b1.maxSpeed;
			bullets.push_back(Bullet(b1));
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].shape.move(bullets[i].currVelocity);

			//Out of bounds
			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
			{
				bullets.erase(bullets.begin() + i);
				
			}
			else
			{
				//Enemy collision
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + k);
						score++;
						break;
					}


					if (player.getGlobalBounds().intersects(enemies[k].getGlobalBounds())){
						// std::cout<<"Collided";
						window.clear();
						text.setString("GameOver!!");
						window.draw(text);

						window.display();
						sleep(5);

						window.close();
					}

            
				}
			}
		}
		

		//Draw
		window.clear();
		
		time(&finish);
		std::string timeNow = "Time:" + std::to_string(difftime(finish,start)) + " Score:" + std::to_string(score);
		text.setString(timeNow);



		window.draw(text);

		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}

        // BOUNDARY FOR PLAYER
        if(player.getPosition().y>window.getSize().y-5){
            player.setPosition(player.getPosition().x,window.getSize().y-10);
        }
        if(player.getPosition().x>window.getSize().x-5){
            player.setPosition(window.getSize().x-10,player.getPosition().y);
        }
        if(player.getPosition().y<0){
            player.setPosition(player.getPosition().x,60.f);
        }
        if(player.getPosition().x<0){
            player.setPosition(60.f,player.getPosition().y);
        }
        
		window.draw(player);

		for (size_t i = 0; i < bullets.size(); i++)
		{
			window.draw(bullets[i].shape);
		}


		window.display();
	}

	return 0;
}


