#include "invaders.h"
#ifndef beta_H
#define beta_H
class Beta : public Invaders
{

public:
	Beta(){
		tex.loadFromFile("img/PNG/Enemies/enemyBlue2.png");
		sprite.setTexture(tex);
		x=330;y=200;
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
	virtual ~Beta()
	{
		if (b != nullptr)
		{
			if (num_bomb == 1)
				delete b;
			else
				delete[] b;
			b = nullptr;
		}
	}
};
#endif
