#include "invaders.h"
#ifndef alpha_H
#define alpha_H
class Alpha : public Invaders
{
public:
	Alpha(){
		tex.loadFromFile("img/PNG/Enemies/enemyBlack1.png");
		sprite.setTexture(tex);
		x=330;y=200;
		sprite.setPosition(x, y);
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
	virtual ~Alpha()
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
