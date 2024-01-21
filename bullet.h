#include<iostream>
using namespace std;
class Bullet
{

public:
	Texture bullet;
	Sprite b1, b2, b3;
	int num_of_bullets;
	int xb1, xb2, xb3;
	int yb1, yb2, yb3;
	Bullet(int x=0, int y=0)
	{
		bullet.loadFromFile("img/PNG/Lasers/laserGreen03.png");
		b1.setTexture(bullet);
		xb1 = x + 36;
		yb1 = y - 10;
		b1.setPosition(xb1, yb1);
		b1.setScale(0.7,0.3);
		b2.setTexture(bullet);
		xb2 = x + 34;
		yb2 = y - 10;
		b2.setPosition(xb2, yb2);
		b2.setScale(0.7,0.3);
		b3.setTexture(bullet);
		xb3 = x + 38;
		yb3 = y - 10;
		b3.setPosition(xb3,yb3);
		b3.setScale(0.7,0.3);
	}
	void move()
	{
		b1.move(0, -0.5);
		yb1 -= 0.5;
		b2.move(0.25, -0.5);
		xb2 += 0.25;
		yb2 -= 0.5;
		b3.move(-0.25, -0.5);
		xb3 -= 0.25;
		yb3 -= 0.5;
	}
	bool check_finish()
	{
		if (yb2 <= 0 || yb3 <= 0 || yb1<= 0)	//If the bullets have reached the top...
			return true;	//Then the bullet should finish...
		return false;
	}
	void setLocation (int x, int y)
	{
		xb1 = x + 36;
		yb1 = y - 10;
		b1.setPosition(xb1,yb1);
		xb2 = x + 34;
		yb2 = y - 10;
		b2.setPosition(xb2,yb2);
		xb3 = x + 38;
		yb3 = y - 10;
		b3.setPosition(xb3,yb3);
	}
	void operator=(Bullet& b)
	{
		bullet.loadFromFile("img/PNG/Lasers/laserGreen03.png");
		b1.setTexture(bullet);
		xb1 = b.xb1;
		yb1 = b.yb1;
		b1.setPosition(xb1, yb1);
		b1.setScale(0.7,0.3);
		b2.setTexture(bullet);
		xb2 = b.xb2;
		yb2 = b.yb2;
		b2.setPosition(xb2, yb2);
		b2.setScale(0.7,0.3);
		b3.setTexture(bullet);
		xb3 = b.xb3;
		yb3 = b.yb3;
		b3.setPosition(xb3,yb3);
		b3.setScale(0.7,0.3);
	
	}
	
	
};
