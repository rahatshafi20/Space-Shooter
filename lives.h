#include "add_on.h"
#ifndef lives_H
#define lives_H
class Lives : public Add_on
{
public:
	Lives()
	{
		texture.loadFromFile("img/PNG/Power-ups/pill_red.png");
		sprite.setTexture(texture);
		srand(time(0));
		x=rand()%740 + 10 ;
		y=0;
		sprite.setPosition(x,y);
		sprite.setScale(2,2);
	}
	void move(float m_x, float m_y)
	{
		sprite.move (m_x, m_y);
		x += m_x;
		y += m_y;
	}
	bool over()
	{
		if (y >= 780)
			return true;
		return false;
	}
	bool check_collision (float p_x, float p_y)
	{
		if (x >= p_x && x <= p_x+40 && y>=p_y && y<=p_y+40)
			return true;
		return false;
	}
};
#endif
