#include <SFML/Graphics.hpp>
using namespace sf;
#include "enemy.h"
class Monster : public Enemy
{
public:
	Monster()
	{
		tex.loadFromFile("img/enemy_2.png");
		sprite.setTexture(tex);
		x=700;y=100;
		sprite.setPosition(x,y);
		sprite.setScale(1.5,1.5);
		b = nullptr;
	}
	void set_position (float x_change, float y_change)
	{
		sprite.move(x_change, y_change);
		x += x_change;
		y += y_change;
	}
	void drop_bomb()	//Function to drop the bomb when time interval comes...
	{
		b = new Bomb (x+80, y+80, "img/PNG/Lasers/laserRed01.png");
		b->setScale(2.25, 8.75);
	}
	void delete_bomb(int position)	//Function to delete the bomb when it goes out of range...
	{
		//Here not concerned with position as its a continous flash of light
		if (b != nullptr)
		{
			delete b;
			b = nullptr;
		}
	}
	void move_bombs()	//Its a continous flash of light that moves along with the monster..
	{
		b->bomb_spr.setPosition (x+80, y+80);
	}
	void display_bombs(sf::RenderWindow& window)	//To display bombs on screen...
	{
		if (b != nullptr)
			window.draw (b->bomb_spr);
	}
	virtual ~Monster()
	{
		if (b != nullptr)
		{
			delete b;
			b = nullptr;
		}
	}
};
