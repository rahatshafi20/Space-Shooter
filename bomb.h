#include <SFML/Graphics.hpp>
using namespace sf;
#ifndef bomb_H
#define bomb_H
class Bomb
{
public:
	Texture bomb_tex;
	Sprite bomb_spr;
	int bx, by;
	Bomb(int x=0, int y=0, string image = "img/explosion.png")	
	{
		bomb_tex.loadFromFile(image);
		bomb_spr.setTexture(bomb_tex);
		bomb_spr.setScale(0.1,0.1);
		if (image == "img/explosion.png")
			bomb_spr.setTextureRect(IntRect (0,0, 150, 330));//Picture of explosions have 4 types, so I am chosing one type of explosive...
		bx = x + 28;
		by = y + 48;
		bomb_spr.setPosition(bx, by);
	}
	//To check when the bomb is out of range etc....
	bool check_finish()
	{
		if (by >= 780)	//If the bomb have reached the bottom..
			return true;	//Then the bomb should finish...
		return false;
	}
	void move_bomb()
	{
		bomb_spr.move (0, 0.1);
		by += 0.1;
	}
	void setLocation (int x, int y)
	{
		bx = x + 28;
		by = y + 48;
		bomb_spr.setPosition(bx,by);
	}
	void setScale (float x, float y)
	{
		bomb_spr.setScale(x, y);
	}
	void operator = (Bomb& equate)
	{
		bomb_tex.loadFromFile("img/explosion.png");
		bomb_spr.setTexture(bomb_tex);
		bomb_spr.setScale(0.1,0.1);
		bomb_spr.setTextureRect(IntRect (0,0, 150, 330));	//Picture of explosions have 4 types, so I am chosing one type of explosive...
		bx = equate.bx;
		by = equate.by;
		bomb_spr.setPosition(bx, by);
	}
	~Bomb (){}
};

#endif
