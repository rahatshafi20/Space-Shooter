#include <SFML/Graphics.hpp>
#include<string.h>
#include "bullet.h"
using namespace sf;
class Player{
public:
Texture tex, tex1;
Sprite sprite, sprite1;
Bullet* ship_bullet;
int num_bullet;	//To keep record of the current bullets...
float speed = 0.25;
float x,y;
int bx, by;	//The x and y coordinates that of the bullets to be added...
bool rotated_left = false, rotated_right = false;	//To see if the space ship is rotated or not...
Player(std::string png_path)
{
	tex.loadFromFile(png_path);
	sprite.setTexture(tex);
	x=340;y=500;
	sprite.setPosition(x,y);
	sprite.setScale(0.75,0.75);
	ship_bullet = nullptr;
	num_bullet = 0;
	rotated_left = false;
	rotated_right = false;
	bx=x; by=y;
}
void fire(bool again)
{
	if (again)
		addBullet();
	//IF this function is called with a value of 1 then a bullet is added,
	//Otherwise bullet is moved above, and if gets out of range, its deleted... 
	else 
	{
		//To move bullets upwards...
		if (num_bullet == 1)
			ship_bullet->move();
		else if (num_bullet > 1)
		{
			for (int k=0; k<num_bullet; k++)
				ship_bullet[k].move();
		}
		//Now check to finish bullets if they get out of range....
		if (num_bullet > 1)	//If there are more then 1 bullets...
		{
			for (int k=0; k<num_bullet; k++)
			{
				if (ship_bullet[k].check_finish())	//Individually checking if any of the bullet has gone out of range...
				{
					deleteBullet(k);	//Deleting that bullet at index k...
					break;	//So that one bullett is deleted at one call, which is how the game should work...						
				}
			}
		}
		else if (num_bullet == 1)	//If there is only 1 bullet...
		{
			if (ship_bullet -> check_finish())
				deleteBullet(0);
		}		
	}
}

//This below function is used to delete a bullet from the aray after it has been out of range...
void deleteBullet(int k = 0)	
//Here k is the location of the bullet int the array, if not mentioned, its taken 0,
{
	if (num_bullet  > 2)
	{
		Bullet* temp = new Bullet [num_bullet - 1];
		int inner_counter = 0;
		for (int l=0; l<num_bullet; l++)
			if (l != k)
			{
				temp[inner_counter] = ship_bullet[l];
				inner_counter++;
			}
		delete[] ship_bullet;
		num_bullet --;
		ship_bullet = new Bullet [num_bullet];
		for (int l=0; l<num_bullet; l++)
			ship_bullet[l] = temp[l];
		delete[] temp;
	}
	else if (num_bullet == 2)
	{
		Bullet* temp = new Bullet;
		if (k == 0)
			*temp = ship_bullet[1];
		else
			*temp = ship_bullet[0];
		delete[] ship_bullet;
		ship_bullet = new Bullet;
		*ship_bullet = *temp;
		delete temp;
		num_bullet --;
	}
	else if (num_bullet == 1 && k==0)	//If there is only 1 bullet...
	{
		delete ship_bullet;
		ship_bullet = nullptr;
		num_bullet --;
	}
}
//This below function is used to add a new bullet into the array of bullets...
void addBullet()	
{
	if (ship_bullet != nullptr)
	{
		Bullet* temp;
		if (num_bullet == 1)
		{
			temp = new Bullet;
			*temp = *ship_bullet;
			delete ship_bullet;
		}
		else
		{
			temp = new Bullet [num_bullet];
			for (int k=0; k<num_bullet; k++)
				temp[k] = ship_bullet [k];
			delete[] ship_bullet;
		}
		ship_bullet = new Bullet [num_bullet+1];
		if (num_bullet == 1)
		{
			ship_bullet[0] = *temp;
			ship_bullet[1].setLocation(bx, by);	//To reset the position of the added bullet...
			delete temp;
		}
		else
		{
			for (int k=0; k<num_bullet; k++)
				ship_bullet [k] = temp[k];
			ship_bullet[num_bullet].setLocation(bx, by);	//To reset the position of the added bullet...
			delete[] temp;
		}
		num_bullet++;
	}
	else 
	{
		ship_bullet = new Bullet (bx,by);
		num_bullet++;
	}
}
//To show the bullet of the screen ...
void show_bullet (RenderWindow& window)
{
	if (num_bullet == 1)
	{
		window.draw(ship_bullet -> b1);
		window.draw(ship_bullet -> b2);
		window.draw(ship_bullet -> b3);
		
	}
	else if (num_bullet > 1)
	{
		for (int k=0; k<num_bullet; k++)
		{
			window.draw(ship_bullet[k].b1);
			window.draw(ship_bullet[k].b2);
			window.draw(ship_bullet[k].b3);
		}
	}
}
//To move the player on the screen...
void move(std::string s){
	float delta_x=0,delta_y=0;
	if( s == "l")			//move the player left
		delta_x = -1;
	else if(s == "r")		//move the player right
		delta_x = 1;
	else if(s == "u")		//move the player up
		delta_y = -1;
	else if(s == "d")		//move the player down
		delta_y = 1;

	delta_x *= speed;
	delta_y *= speed;
	
	//Making changes in the original coordinates of the player as well because it will be used later in the game...
	x = x + delta_x;
	y = y + delta_y;
	
	//cout<<"x: "<<x<<" y: "<<y<<endl;
	//cout<<"delta x: "<<delta_x<<"delta y: "<<delta_y<<endl;
	//sprite.move(delta_x, delta_y);	
	//sprite.setPosition (x, y);
	//Now trying to make the galaxy wrap around...
	if (x <= 0 && y>0)
	{
		x = 770;
		sprite.setPosition (x, y);
	}
	else if (x >= 780 && y>0)
	{
		x = 10;
		sprite.setPosition (x, y);
	}
	else if (x >0 && y <= 0)
	{
		y = 770;
		sprite.setPosition (x, y);
	}
	else if (x >0 && y >= 780)
	{
		y = 10;
		sprite.setPosition (x, y);
	}
	bx = x;	//The x-coordinate of the bullet will change when it is spaceship is moved...
	by = y;
	sprite.setPosition (x, y);
}
void rotate_45_right()
{
	if (rotated_right == false)
	{
		tex.loadFromFile("img/Ship_45_Right.png");
		sprite.setTexture(tex);
		sprite.setScale(0.75,0.75);
		rotated_right = true;
		rotated_left = false;
	}
	bx = x + 40;	//The x-coordinate of the bullet will change when it is rotated....
	by = y;
}
void rotate_45_left()
{
	if (rotated_left == false)
	{
		tex.loadFromFile("img/Ship_45_Left.png");
		sprite.setTexture(tex);
		sprite.setScale(0.75,0.75);
		rotated_left = true;
		rotated_right = false;
	}
	bx = x - 40;	//The x-coordinate of the bullet will change when it is rotated....
	by = y;
}
void reset_rotation()
{
	if (rotated_left == true || rotated_right == true)
	{
		tex.loadFromFile("img/player_ship.png");
		sprite.setTexture(tex);
		rotated_left = false;
		rotated_right = false;
		//When the axis are not rotated, so these should be the points of bullets...
		bx = x;
		by = y;
	}
}
//If the bullet of player has hit the invader
bool detect_collision(int invader_x, int invader_y)
{
	if (num_bullet == 1)
	{
	
		if ((ship_bullet->xb1 >= (invader_x) && ship_bullet->xb1 <= (invader_x+50) && ship_bullet->yb1 >= (invader_y) && ship_bullet->yb1 <=(invader_y+50))
			||(ship_bullet->xb2 >= (invader_x) && ship_bullet->xb2 <=(invader_x+50) && ship_bullet->yb2 >= (invader_y) && ship_bullet->yb2 <= (invader_y+50)) 
			||(ship_bullet->xb3 >= (invader_x) && ship_bullet->xb3 < (invader_x+50) && ship_bullet->yb3 >= (invader_y) && ship_bullet->yb3 <= (invader_y+50)))
		{
			deleteBullet(0);
			return true;
		}
	}
	else if (num_bullet > 1)
	{
		for (int k=0; k<num_bullet; k++)
		{
			if ((ship_bullet[k].xb1 >= (invader_x) && ship_bullet[k].xb1 <= (invader_x+50) && ship_bullet[k].yb1 >= (invader_y) && ship_bullet[k].yb1 < (invader_y+50))
			 || (ship_bullet[k].xb2 >= (invader_x) && ship_bullet[k].xb2 <= (invader_x+50) && ship_bullet[k].yb2 >= (invader_y) && ship_bullet[k].yb2 < (invader_y+50)) 
			 || (ship_bullet[k].xb3 >= (invader_x) && ship_bullet[k].xb3 <= (invader_x+50) && ship_bullet[k].yb3 >= (invader_y) && ship_bullet[k].yb3 < (invader_y+50)))
			 {
			 	deleteBullet(k);
				return true;
			}
		}
	}
	return false;
}
//To check if the space ship has been attacked or not...
bool check_attacked (int bomb_x, int bomb_y)
{
	if (bomb_x >= x && bomb_x < x+40 && bomb_y >= y && bomb_y < y+40)
		return true;
	return false;	
}
//To check if laser of monster destroys the ship
bool laser_monster_collison (int laser_x, int laser_y)
{
	if (x >= laser_x-10 && x < laser_x+70 && y >= laser_y && y < 760)
		return true;
	return false;	
}

};
