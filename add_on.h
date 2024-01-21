#include <SFML/Graphics.hpp>
#ifndef add_on_H
#define add_on_H
class Add_on
{
public:
	int x, y;
	Texture texture;
	Sprite sprite;
	virtual void move(float x, float y) = 0;	//Pure virtual function...
	virtual bool over() = 0;	//Pure virtual function...
	virtual bool check_collision (float x, float y) = 0;	//Pure virtual function...
};
#endif
