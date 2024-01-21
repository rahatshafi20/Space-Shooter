#include <SFML/Graphics.hpp>
#include<string.h>
using namespace std;
#include<iostream>
using namespace sf;
#include "enemy.h"
#ifndef invaders_H
#define invaders_H
class Invaders : public Enemy
{
public:
	Invaders(){}	//Constructor
	//virtual void set_position () = 0;	//Pure virtual function, will use it to set tthe position of invaders...
	virtual void set_position (float x, float y) = 0;
	
	//To drop a bomb towards the spaceship...
	void drop_bomb()
	{
		if (b == nullptr)
		{
			b = new Bomb(x, y);
			num_bomb++;
		}
		else	//Adding one new bomb if there are already bombs
		{
			Bomb* temp;
			if (num_bomb == 1)
			{
				temp = new Bomb;
				*temp = *b;
				delete b;
				num_bomb++;
 				b = new Bomb [num_bomb];
 				b[0] = *temp;
 				b[1].setLocation(x,y);
 				delete temp;
			}
			else if (num_bomb > 1)
			{
				temp = new Bomb[num_bomb];
				for (int k=0; k<num_bomb; k++)
					temp[k] = b[k];
				delete[] b;	
				b = new Bomb[num_bomb + 1];
				for (int k=0; k<num_bomb; k++)
					b[k] = temp[k];
				b[num_bomb].setLocation(x,y);
				num_bomb ++;
			}
		}
	}
	//To delete a bomb after it gets out of range...
	void delete_bomb (int position)
	{
		if (b!=nullptr)
		{
			Bomb* temp;
			if (num_bomb - 1 > 1)
			{
				temp = new Bomb [num_bomb];
				for (int k=0; k<num_bomb; k++)
					temp[k] = b[k];
				delete[] b;
				b = new Bomb [num_bomb - 1];
				int counter = 0;
				for (int k=0; k<num_bomb; k++)
					if (k != position)
					{
						b[counter] = temp[k];
						counter++;
					}
				delete[] temp;
				num_bomb --;
			}
			else if (num_bomb - 1 == 1)
			{
				temp = new Bomb;
				if (position == 0)
				{
					*temp = b[1];
					delete[] b;
					b = new Bomb;
					*b = *temp;
					delete temp;
				}
				else if (position == 1)
				{
					*temp = b[0];
					delete[] b;
					b = new Bomb;
					*b = *temp;
					delete temp;
				}
				num_bomb--;
			}
			else if (num_bomb == 1 && position == 0)
			{
				num_bomb --;
				delete b;
				b = nullptr;
			}
		}
	}
		
	void move_bombs()
	{
		if (num_bomb == 1)
		{
			b->move_bomb();
		}
		else if (num_bomb > 1)
		{
			for (int i=0; i<num_bomb; i++)
				b[i].move_bomb();
		}
	}
	//To dispaly bullets on screen...
	 void display_bombs(RenderWindow& window) 
	 {
		 if (b != nullptr)
		 {
		 	if (num_bomb == 1)
			{
				window.draw(b->bomb_spr);
			}
			else if (num_bomb > 1)
			{
				for (int i=0; i<num_bomb; i++)
					window.draw(b[i].bomb_spr);
			}
		 }
	 }
	virtual ~Invaders()
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
