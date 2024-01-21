#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;
#include "enemy.h"
class Dragon : public Enemy
{
public:
	Dragon()
	{
		tex.loadFromFile("img/dragon.png");
		sprite.setTexture(tex);
		x=300;y=200;
		sprite.setPosition(x,y);
		sprite.setScale(0.75,0.75);
		b = nullptr;
		num_bomb = 0;
	}
	void set_position (float x_change, float y_change)
	{
		sprite.move(x_change, y_change);
		x += x_change;
		y += y_change;
	}
	void drop_bomb()	//Function to drop the bomb when time interval comes...
	{
		b = new Bomb (x+15, y+25, "img/bomb.png");
		b->setScale(0.15, 0.15);
	}
	void delete_bomb(int position)	//Function to delete the bomb when it goes out of range...
	{
		if (b != nullptr)
		{
			delete b;
			b = nullptr;
		}
	}
	void move_bombs() 	//To move the bombs with time...
	{
		if (b != nullptr)
			b->bomb_spr.move(0, 0.1);		//To move the bomb downwards
	}
	void display_bombs(sf::RenderWindow& window)	//To display bombs on screen...
	{
		if (b != nullptr)
			window.draw (b->bomb_spr);
	}
	virtual ~Dragon()
	{
		if (b != nullptr)
		{
			delete b;
			b = nullptr;
		}
	};
};
