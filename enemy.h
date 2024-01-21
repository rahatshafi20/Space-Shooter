#include "bomb.h"
#ifndef enemy_H
#define enemy_H
class Enemy
{
public:
	Texture tex;
	Sprite sprite;
	Bomb* b;
	int num_bomb;
	float x, y;	//To store the coordinates...
	//virtual void move() = 0;	//Pure vitual function to move the enemy...	
	virtual void set_position(float x, float y) = 0;	//Pure vitual function to move the enemy...	
	virtual void drop_bomb() = 0;	//Pure virtual function to drop the bomb when time interval comes...
	virtual void delete_bomb(int position) = 0;	//Pure virtual function to delete the bomb when it goes out of range...
	virtual void move_bombs() = 0;	//Pure virtual function to move the bombs with time...
	virtual void display_bombs(sf::RenderWindow& window) = 0;	//To display bombs on screen...
	void operator= (Enemy& invader)
	{
		tex = invader.tex;
		sprite.setTexture(tex);
		x=invader.x;y=invader.y;
		sprite.setPosition(invader.x, invader.y);
		sprite.setScale(0.75,0.75);
		if (b == nullptr)
		{
			if (invader.num_bomb == 1 && invader.b != nullptr)
			{
				b = new Bomb;
				*b = *(invader.b);	
			}
			else if (invader.num_bomb > 1)
			{
				b = new Bomb [invader.num_bomb];
				for (int k=0; k<invader.num_bomb; k++)
					b[k] = invader.b[k];
			}
			num_bomb = invader.num_bomb;
		}
		else if (b != nullptr)
		{
			if (num_bomb == 1)
				delete b;
			else if (num_bomb > 1)
				delete[] b;
			b = nullptr;
			num_bomb = 0;
			if (invader.b != nullptr)
			{
				if (invader.num_bomb == 1)
				{
					b = new Bomb;
					*b = *(invader.b);	
				}
				else if (invader.num_bomb > 1)
				{
					b = new Bomb [invader.num_bomb];
					for (int k=0; k<invader.num_bomb; k++)
						b[k] = invader.b[k];
				}
				num_bomb = invader.num_bomb;
			}
		}
	}
	
	virtual ~Enemy ()
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
