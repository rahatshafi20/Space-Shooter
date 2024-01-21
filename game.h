#include <SFML/Graphics.hpp>
#include <time.h>
#include "player.h"
//other included classes...
#include "dragon.h"
#include "invaders.h"
#include "monster.h"
#include "enemy.h"
#include "alpha.h"
#include "beta.h"
#include "gamma.h"
#include "add_on.h"
#include "danger.h"
#include "lives.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
	Sprite background; //Game background sprite
	Texture bg_texture;
	Player* p; //player 
	// add other game attributes
	Sprite pauseButton_s;
	Texture pauseButton_t;
	Enemy* enemy;
	Add_on* add;
	int num_of_invaders;
	int level;
	int config_invaders;	//This will store about the configuration of the invaders...
	int lives;	//To store the lives of the player...
	bool game_finished;
	int score;
	Game()	//Constructor..;
	{
		p=new Player("img/player_ship.png");
		bg_texture.loadFromFile("img/background.jpg");
		background.setTexture(bg_texture);
		background.setScale(2.25, 1.35);
		//Initializing other game attributes...
		pauseButton_t.loadFromFile("img/pauseButton.jpg");
		pauseButton_s.setTexture(pauseButton_t);
		pauseButton_s.setScale(0.25,0.25);
		pauseButton_s.setPosition(720, 60);
		enemy = nullptr;
		add = nullptr;
		level = 1;
		config_invaders = 1;
		lives = 3;
		game_finished = false;
		score = 0;
	}
	void start_game()	//Starts the game and runs it...
	{
		srand(time(0));
		RenderWindow window(VideoMode(780, 780), title);
		Clock clock;
		float timer=0;
		//Other attributes...
		bool show_invaders = true;
		bool show_dragon = false;
		bool show_monster = false;
		bool m_move_l = true;	//To make monster moove left;
		bool m_move_r = false;	//To make monster moove right...
		bool monster_dodged = true;	//To see if the monster was able to destroy the ship or not../
		bool danger_sign = false;	//To show the danger sign...
		bool dogged_danger = true;
		bool up_lives = true;	//Power up of lives...
		float bullet_timer=0;
		float invaders_bomb_interval = 0;
		float dragon_interval = 0;
		float time_for_dragon = rand()%170;
		float wait_for_dragon = 0;
		float dragon_bomb_interval = 0;
		float time_for_danger = rand()%70;
		float wait_for_danger = 0;
		float time_laser_monster = 0;
		float time_count = 0;
		float time_for_lives = rand()%100;
		float wait_for_lives = 0;
		bool invaders_deleted = false;	//When dragon/monster should come, invaders should delete...
		Font font;
		font.loadFromFile("font/arial.ttf");	//Loading the font that I have added in this folder (arial)...
		Text text;
		while (window.isOpen())
		{
			
			float time = clock.getElapsedTime().asSeconds(); 
			clock.restart();
			timer += time;   
			bullet_timer += time;	//To store time to see after hhow much time bullet shoud fire...
			invaders_bomb_interval += time;	//To see the time of droping of bombs by invaders...
			wait_for_dragon+= time;
			dragon_bomb_interval += time;
			if (show_monster)
				time_laser_monster += time;
			if (wait_for_dragon >= time_for_dragon && show_monster == false)
		    	{	
				show_dragon = true;
				show_invaders = false;
				wait_for_dragon = 0;
				time_for_dragon = rand()%200;	//again choosing a random time for the appearance of dragon...
		    	}
		    	wait_for_danger += time;
		    	if (wait_for_danger >= time_for_danger && add == nullptr)
			{
				danger_sign = true;
				time_for_danger = rand()%60;
				wait_for_danger = 0;
			}
			if (show_dragon)
			{
				if (dragon_interval < 15)	//To calculate time of apperance of dragon which is 15 seconds...
				{
					if (dragon_bomb_interval >=5)
					{
						enemy->delete_bomb(0);
						enemy->drop_bomb();
						dragon_bomb_interval = 0;
					}
					dragon_interval += time;
					enemy->move_bombs();	//To move the bomb
				}
				else
				{
					show_dragon = false;
					show_invaders = true;
					dragon_interval = 0;
					invaders_deleted = false;
					delete enemy;	//deleting dragon;
					enemy = nullptr;
				}
			}
			wait_for_lives += time;
			if (wait_for_lives >= time_for_lives && add == nullptr)
			{
				up_lives = true;
				time_for_lives = rand()%60;
				wait_for_lives = 0;
			}
	 		Event e;
		    	while (window.pollEvent(e))
		   	{  
		        if (e.type == Event::Closed) // If cross/close is clicked/pressed
		            window.close(); //close the game                        	    
		    	}
		      
			if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
			{
				p->reset_rotation();	//If any rotation has taken place, this function will reset that...
				p->move("l");    // Player will move to left
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
			{
				p->reset_rotation();	//If any rotation has taken place, this function will reset that...
				p->move("r");  //player will move to right
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
			{
				p->reset_rotation();	//If any rotation has taken place, this function will reset that...
				p->move("u");    //player will move upwards
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
			{
				p->reset_rotation();	//If any rotation has taken place, this function will reset that...
				p->move("d");  //player will move downwards
			}
			  
			if (Keyboard::isKeyPressed(Keyboard::A)) // If A key is pressed...
			{
				    p->move("u");  
				    p->move("r"); 
				    //player will move diagonally towards North-East...
				    p->rotate_45_right();
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) // If D key is pressed...
			{
				    p->move("d");  
				    p->move("l"); 
				    //player will move diagonally towards South-West...
				     p->rotate_45_right();
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) // If C key is pressed...
			{
				    p->move("u");  
				    p->move("l"); 
				    //player will move diagonally towards North-West...
				     p->rotate_45_left();
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) // If D key is pressed
			{
				    p->move("d");  
				    p->move("r"); 
				    //player will move diagonally towards South-East...   
				    p->rotate_45_left();
			}
			if (Keyboard::isKeyPressed(Keyboard::Space) && bullet_timer > 0.25)	
			//Bullet should fire from interval of 0.25s so that there is a bit pause in between firing oof bullets...
			{
				p->fire(1);
				bullet_timer = 0;	//To reset the bullet timer...
			}
			////////////////////////////////////////////////	
			/////  Call your functions here            ////
			//
			p->fire(0);
			if (show_dragon && invaders_deleted == false)	//To delete the invaders when dragon come, and to create dragon...
			{
				if (num_of_invaders)	//If invaders are already present there...
				{
					if (num_of_invaders == 1)
						delete enemy;
					else
						delete[] enemy;
					num_of_invaders = 0;	//As invaders have been destroyed when the dragon jumps into...
					enemy = new Dragon; 	//creating dragon...
				}
				else
				{
					enemy = new Dragon;	//creating new dragon...
				}
				invaders_deleted = true;
			}
			if (show_invaders)	
			{
				if (config_invaders == 1)
					set_alpha_invaders();
				else if (config_invaders == 2) 
					set_beta_invaders();
				else if (config_invaders == 3)
					set_gamma_invaders();
			}
			if (show_invaders)	//To detect the collisons between space ship and player...
			{
				
				if (num_of_invaders == 1)
				{
					//first checking if there is any collision between invaders and bullets from space ship...
					if (p-> detect_collision(enemy->sprite.getPosition().x, enemy->sprite.getPosition().y))
					{
						if (enemy != nullptr)
						{
							delete enemy;
							enemy = nullptr;
							num_of_invaders--;
							score += config_invaders * 10 * level;	//The formula used to claculate score when an invader is destroyed...
							config_invaders ++; //To check if entire invaders of one type were detsroyed so that next phase could start...
						}
					}
					
				}
				else if (num_of_invaders > 1)
				{
					//first checking if there is any collision between invaders and bullets from space ship..
					for  (int k=0; k<num_of_invaders; k++)
					{
						if (p -> detect_collision(enemy[k].sprite.getPosition().x, enemy[k].sprite.getPosition().y))
						{
							delete_invader(k);	//To delete that particular invader which is shot up...
							score += config_invaders * 10 * level;	//The formula used to claculate score when an invader is destroyed...
							break;	//As only 1 invader to be deleted per unit time...
						}	
						
					}
				}
				//Now checking if any invader has attached the ship and detroyed one life...
				if (show_invaders)
				{
					if (num_of_invaders == 1)
					{
						if (enemy -> num_bomb == 1)
						{
							if (p->check_attacked(enemy->b->bomb_spr.getPosition().x, enemy->b->bomb_spr.getPosition().y))
							{
								enemy->delete_bomb(0);	//Deleting that particular bomb that striked the enemy...
								lives --;
							}
						}
						else if (enemy -> num_bomb > 1)
						{
							for (int i = 0; i<enemy->num_bomb; i++)
								if (p->check_attacked(enemy->b[i].bomb_spr.getPosition().x, enemy->b[i].bomb_spr.getPosition().y))
								{
									lives --;
									enemy->delete_bomb(i);	//Deleting that particular bomb that striked the enemy...
									break;
								}
						}
					}
					else if (num_of_invaders > 1)
					{
						for  (int k=0; k<num_of_invaders; k++)
						{
							if (enemy[k].num_bomb == 1)
							{
								if (p->check_attacked(enemy[k].b->bomb_spr.getPosition().x, enemy[k].b->bomb_spr.getPosition().y))
								{
									lives --;
									enemy[k].delete_bomb(0);	//Deleting that particular bomb that striked the enemy...
									break;
								}
							}
							else if (enemy -> num_bomb > 1)
							{
								bool exit = false;
								for (int i = 0; i<enemy->num_bomb; i++)
									if (p->check_attacked(enemy[k].b[i].bomb_spr.getPosition().x, enemy[k].b[i].bomb_spr.getPosition().y))
									{
										lives --;
										enemy[k].delete_bomb(i);	//Deleting that particular bomb that striked the enemy...
										exit = true;
										break;
									}
								if (exit)
									break;
							}	
						}
					}
				}
				//Now checking to drop any bomb...
				float due_interval_bomb = 0;
				if (config_invaders == 1)
					due_interval_bomb = 5;
				else if (config_invaders == 2) 
					due_interval_bomb = 3;
				else if (config_invaders == 3)
					due_interval_bomb = 2;
				//Now dropping bomb...
				if (invaders_bomb_interval >= due_interval_bomb)
				{
					if (num_of_invaders > 1)
					{
						for (int k=0; k<num_of_invaders; k++)
							enemy[k].drop_bomb();
					}
					else if (num_of_invaders == 1)
						enemy->drop_bomb();
					invaders_bomb_interval = 0;	//resetting the timer...
				}
				//Now checking to delete bombs...
				if (num_of_invaders > 1)
				{
					for (int k=0; k<num_of_invaders; k++)
					{
						if (enemy[k].b != nullptr)
						{
							if (enemy[k].num_bomb == 1)
							{
								if (enemy[k].b->check_finish())
									enemy[k].delete_bomb(k);
							}
							else if (enemy[k].num_bomb > 1)
							{
								for (int i=0; i<enemy[k].num_bomb; i++)
								{
									if (enemy[k].b[i].check_finish())
										enemy[k].delete_bomb(i);
								}
							}
						}
					}
				}
				else if (num_of_invaders == 1)
				{
					if (enemy->b != nullptr)
					{
						if (enemy->num_bomb == 1)
						{
							if (enemy->b->check_finish())
									enemy->delete_bomb(0);
						}
						else if (enemy->num_bomb > 1)
						{
							for (int i=0; i<enemy->num_bomb; i++)
							{
								if (enemy->b[i].check_finish())
									enemy->delete_bomb(i);
							}
						}
					}
				}
				//Now moving bombs
				if (num_of_invaders > 1)
				{
					for (int k=0; k<num_of_invaders; k++)
					{
						if (enemy[k].b != nullptr)
							enemy[k].move_bombs();
					}
				}
				else if (num_of_invaders == 1)
				{
					if (enemy->b != nullptr)
							enemy->move_bombs();
				}
			}
			if (config_invaders > 3)
			{
				config_invaders = 1;	//Resetting the invaders
				//Writing code to get into next phase...
				level++;
				//Changing the background when level changes...
				if (level == 2)
				{
					bg_texture.loadFromFile("img/background1.jpg");
					background.setTexture(bg_texture);
					background.setScale(1, 1.4);
				}
				else if (level == 3)
				{
					bg_texture.loadFromFile("img/background.png");
					background.setTexture(bg_texture);
					background.setScale(2.25, 1.5);
				}
				if (level > 3)
					level = 3;	//As level can't go above 3..
				//Now bringing monster when level changes
				show_monster = true;
				show_invaders = false;
				if (num_of_invaders > 1)
					delete[] enemy;
				else if (num_of_invaders == 1)
					delete enemy;
				num_of_invaders = 0;
				if (show_dragon)
				{
					show_dragon = false;
					delete enemy;
				}
				enemy = new Monster;
				m_move_l = true;
				monster_dodged = true;	//To see if in this try monster was able to destroy ship or not...
			}
			if (lives <= 0)
			{
				//Write code to end game...
				game_finished = true;
				window.close();	//To close this window so that the other window should begin...
			}
			//Functionality for pasuing the game...
			if (e.type == Event::MouseButtonPressed)	//If the mouse button is pressed
			{
				if (e.mouseButton.button == Mouse::Left)	//If its a left click...
				{
					if (e.mouseButton.x>=720 && e.mouseButton.x<=760 && e.mouseButton.y>=60 && e.mouseButton.y<=100 )	
						pauseGame(window);
				}
			}
			if (show_monster)
			{
				if (m_move_l)
				{
					enemy->set_position(-0.25, 0);
					if (enemy -> x <= 0)	//If it has reached the left end...
					{
						m_move_l = false;
						m_move_r = true;	//Now it will start moving right...
					}
				}
				else if (m_move_r)
				{
					enemy->set_position(0.25, 0);
					if (enemy -> x >= 760)	//If it has reached the right end...
					{
						m_move_r = false;
						m_move_l = true;	//so that next time monster starts m,oving towards left
						//Finishing the monster...
						delete enemy;
						enemy = nullptr;
						show_monster = false;
						show_invaders = true;
						if (monster_dodged)
							score += 40;	//The score to dodge the monster is 40
					}
				}
			}
			//Creation of danger sign
			if (danger_sign)
			{
				if (add == nullptr)
					add = new Danger();
				else
					add -> move (0, 0.1);
				//Now check if danger sign has reached at the end...
				if (add -> over())
				{
					delete add;
					add = nullptr;
					danger_sign = false;
					if (dogged_danger)
						score += 5;	//To dodge danger sign, 5 score will be awarded..
				}
			}
			//Checking for collision between danger sign and player...
			if (danger_sign)
			{
				if (add -> check_collision (p->x, p->y))
				{
					delete add;
					add = nullptr;
					danger_sign = false;
					lives--;	//if theres a collison, lives will decrease...
				}
			}
			//Creation of level power up...
			if (up_lives)
			{
				if (add == nullptr)
					add = new Lives;
				else
					add -> move (0, 0.1);
				//Now check if lives power up has reached at the end...
				if (add -> over())
				{
					delete add;
					add = nullptr;
					up_lives = false;
				}
			}
			//Checking for collision between lives power up and player...
			if (up_lives)
			{
				if (add -> check_collision (p->x, p->y))
				{
					delete add;
					add = nullptr;
					up_lives = false;
					lives++;	//if theres a collison, lives will increase...
				}
			}
			//////////////////////////////////////////////
			window.clear(Color::Black); //clears the screen
			window.draw(background);  // setting background
			window.draw(p->sprite);   // setting player on screen
			//
			string to_show;	//The text to show the level and the score to the user on screen 
			to_show = "Level: ";
			to_show += to_string (level);
			to_show += "\tScore: ";
			to_show += to_string (score);
			to_show += "\tRemaining Lives: ";
			to_show += to_string (lives);
			text.setFont(font); 
			text.setString(to_show);
			text.setCharacterSize(30);
			text.setFillColor(Color::White);
			text.setStyle(Text::Bold);
			text.setPosition(0,0);
			window.draw(text);
			
			if (show_dragon)
				window.draw(enemy->sprite);   // setting dragon on screen...
			p -> show_bullet(window);	// setting the bullet on screen...
			
			if (show_monster && time_laser_monster >= 2)
			{
				if (enemy -> b == nullptr)	//If there is no laser created before...
					enemy -> drop_bomb();
				else
					enemy -> move_bombs();
				time_count += time;
				if (time_count >= 2)
				{
					time_count = 0;
					time_laser_monster = 0;	//The dragon will stop throwing laser...
					enemy -> delete_bomb(0);	//Delete the bomb as there is a gap to 2s...
				}
				else	//Check for collison between bomb of monster and the player
				{
					if (enemy -> b != nullptr)	//If the monster has a laser on...
					{
						if (p->laser_monster_collison (enemy->b->bomb_spr.getPosition().x, enemy->b->bomb_spr.getPosition().y))
						{
							enemy -> delete_bomb(0);
							time_laser_monster = 0;
							time_count = 0;
							lives--;	//Then spaceship is destroyed so life is decreased...
							monster_dodged = false;	//The spaceship was destroyed by monster
						}
					}
				}
				
			}
			
			if (show_dragon)
			{
				//To check for collision between bomb of dragon and the player
				if (enemy -> b != nullptr)	//If the dragon has a laser on...
				{
					if (p->laser_monster_collison (enemy->b->bomb_spr.getPosition().x, enemy->b->bomb_spr.getPosition().y))
					{
						enemy -> delete_bomb(0);
						lives--;	//Then spaceship is destroyed so life is decreased...
					}
				}
			
			}
			
			
			if (show_monster || show_dragon)
				enemy -> display_bombs(window);	//Display the laser of monster and bombs of  dragons on screen ...
				
		
				
			if (show_invaders)	//To show the bombs of the invaderss..
			{
				if (num_of_invaders == 1)
					enemy -> display_bombs(window);
				else if (num_of_invaders > 1)
				{
					for (int i=0; i<num_of_invaders; i++)
						enemy[i].display_bombs(window);
				}
			}
			//Setting the invaders on screen ...
			if (show_invaders)
			{
				for  (int k=0; k<num_of_invaders; k++)
					window.draw(enemy[k].sprite);
			}	
			//If there is a danger sign...
			if (danger_sign)
			{
				window.draw (add->sprite);
			}
			//If there is a lives power up...
			if (up_lives)
			{
				window.draw (add->sprite);
			}
			//If there is monster, show it..
			if (show_monster)
				window.draw(enemy -> sprite);
			//Show the pauseButton
			window.draw(pauseButton_s);
			//Displying all the sprites
			window.display();  
		}
	}
	
	//Function that will create Alpha invaders in their required configuration
	void set_alpha_invaders()
	{
		int shape;
		if (level == 1 || level == 2)
			shape = level;
		else
			shape = rand() % 2 + 1;	//If level is 3 then the shape will be chosen form any of these shapes...
		if (enemy == nullptr)
		{
			if (shape == 1)
			{
				//TO show the rectangle configuration of alpha invaders...
				num_of_invaders = 10;
				enemy = new Alpha[num_of_invaders];	//creating invaders as per 
				//Setting the invaders at their positions...
				enemy[0].set_position(0, 100);
				enemy[1].set_position(0, -100);
				enemy[2].set_position(100, -100);
				enemy[3].set_position(100, 100);
				enemy[4].set_position(200, -100);
				enemy[5].set_position(200, 0);
				enemy[6].set_position(200, 100);
				enemy[7].set_position(-100, -100);
				enemy[8].set_position(-100, 0);
				enemy[9].set_position(-100, 100);
			}
			else if (shape == 2)
			{
				//TO show the circle configuration of alpha invaders...
				num_of_invaders = 8;
				enemy = new Alpha[num_of_invaders];	//creating invaders as per 
				//Setting the invaders at their positions...
				enemy[0].set_position(0, 150);
				enemy[1].set_position(150, 0);
				enemy[2].set_position(0, -150);
				enemy[3].set_position(-150, 0);
				enemy[4].set_position(-100, -100);
				enemy[5].set_position(100, -100);
				enemy[6].set_position(-100, 100);
				enemy[7].set_position(100, 100);
			}
		}	
	}
	//Function that will create Beta invaders in their required configuration
	void set_beta_invaders()
	{
		int shape;
		if (level == 1 || level == 2)
			shape = level;
		else
			shape = rand() % 2 + 1;	//If level is 3 then the shape will be chosen form any of these shapes...
		if (enemy == nullptr)
		{
			if (shape == 1)
			{
				//TO show the triangle configuration of beta invaders...
				num_of_invaders = 9;
				enemy = new Beta[num_of_invaders];	//creating invaders as per 
				//Setting the invaders at their positions...
				enemy[0].set_position(0, 0);
				enemy[1].set_position(-50, 50);
				enemy[2].set_position(50, 50);
				enemy[3].set_position(-100, 100);
				enemy[4].set_position(100, 100);
				enemy[5].set_position(-150, 150);
				enemy[6].set_position(150, 150);
				enemy[7].set_position(-50, 150);
				enemy[8].set_position(50, 150);		
			}
			else if (shape == 2)
			{
				//TO show the diamond configuration of beta invaders...
				num_of_invaders = 10;
				enemy = new Beta[num_of_invaders];	//creating invaders as per 
				//Setting the invaders at their positions...
				enemy[0].set_position(0, 150);
				enemy[1].set_position(-150, -100);
				enemy[2].set_position(150, -100);
				enemy[3].set_position(-100, -50);
				enemy[4].set_position(100, -50);
				enemy[5].set_position(100, -150);
				enemy[6].set_position(-100, -150);
				enemy[7].set_position(65, 30);
				enemy[8].set_position(-65, 30);
				enemy[9].set_position(0, -200);	
			}
		}
	}
	//Function that will create Gamma invaders in their required configuration
	void set_gamma_invaders()
	{
		int shape;
		if (level == 1 || level == 2)
			shape = level;
		else
			shape = rand() % 2 + 1;	//If level is 3 then the shape will be chosen form any of these shapes...
		if (enemy == nullptr)
		{
			if (shape == 1)
			{
				//TO show the cross configuration of gamma invaders...
				num_of_invaders = 9;
				enemy = new Gamma[num_of_invaders];	//creating invaders as per 
				//Setting the invaders at their positions...
				enemy[0].set_position(0, 0);
				enemy[1].set_position(-50, -50);
				enemy[2].set_position(50, -50);
				enemy[3].set_position(-50, 50);
				enemy[4].set_position(50, 50);
				enemy[5].set_position(-100, -100);
				enemy[6].set_position(100, -100);
				enemy[7].set_position(-100, 100);
				enemy[8].set_position(100, 100);
			}
			else if (shape == 2)
			{
				//TO show the Heart configuration of gamma invaders...
				num_of_invaders = 8;
				enemy = new Gamma[num_of_invaders];	//creating invaders as per 
				//Setting the invaders at their positions...
				enemy[0].set_position(0, 200);
				enemy[1].set_position(0, -100);
				enemy[2].set_position(-50, 100);
				enemy[3].set_position(50, 100);
				enemy[4].set_position(100, 0);
				enemy[5].set_position(-100,0);
				enemy[6].set_position(150, -150);
				enemy[7].set_position(-150, -150);
			}
		
		}
	}
	void delete_invader(int position)	//To delete any one invader from the array....
	{
		Enemy* temp;
		
		if (num_of_invaders - 1 > 1)
		{
			//deleting the current bullets of the enemy to be distroyed...
			if (enemy[position].b != nullptr)
			{
				if (enemy[position].num_bomb == 1)
					delete enemy[position].b;
				else if (enemy[position].num_bomb > 1)
					delete[] enemy[position].b;
				enemy[position].b = nullptr;
			}
			if (config_invaders == 1)	//if alpha invaders are showing on screen...
				temp = new Alpha[num_of_invaders-1];
			else if (config_invaders == 2)	//if beta invaders are showing on screen...
				temp = new Beta[num_of_invaders-1];
			else if (config_invaders == 3)	//if gamma invaders are showing on screen...
				temp = new Gamma[num_of_invaders-1];
			int counter = 0;
			for (int k=0; k<num_of_invaders; k++)
			{
				if (k != position)
				{
					temp[counter] = enemy[k];
					counter++;
				}
			}
			delete[] enemy;
			num_of_invaders--;
			if (config_invaders == 1)	//if alpha invaders are showing on screen...
				enemy = new Alpha [num_of_invaders];
			else if (config_invaders == 2)	//if beta invaders are showing on screen...
				enemy = new Beta [num_of_invaders];
			else if (config_invaders == 3)	//if gamma invaders are showing on screen...
				enemy = new Gamma [num_of_invaders];
			for (int k=0; k<num_of_invaders; k++)
				enemy[k] = temp[k];
			delete[] temp;
			
		}
		else if (num_of_invaders - 1 == 1)
		{
			//deleting the current bullets of the enemy to be distroyed...
			if (enemy[position].b != nullptr)
			{
				if (enemy[position].num_bomb == 1)
					delete enemy[position].b;
				else if (enemy[position].num_bomb > 1)
					delete[] enemy[position].b;
				enemy[position].b = nullptr;
			}
			if (config_invaders == 1)	//if alpha invaders are showing on screen...
				temp = new Alpha;
			else if (config_invaders == 2)	//if beta invaders are showing on screen...
				temp = new Beta;
			else if (config_invaders == 3)	//if gamma invaders are showing on screen...
				temp = new Gamma;
			if (position == 1)
			{
				*temp = enemy[0];
				delete[] enemy;
				if (config_invaders == 1)	//if alpha invaders are showing on screen...
					enemy = new Alpha;
				else if (config_invaders == 2)	//if beta invaders are showing on screen...
					enemy = new Beta;
				else if (config_invaders == 3)	//if gamma invaders are showing on screen...
					enemy = new Gamma;
				*enemy = *temp;
				delete temp;
			}
			else if (position == 0)
			{
				*temp = enemy[1];
				delete[] enemy;
				if (config_invaders == 1)	//if alpha invaders are showing on screen...
					enemy = new Alpha;
				else if (config_invaders == 2)	//if beta invaders are showing on screen...
					enemy = new Beta;
				else if (config_invaders == 3)	//if gamma invaders are showing on screen...
					enemy = new Gamma;
				*enemy = *temp;
				delete temp;
			}
			num_of_invaders--;
		}
	}
	void pauseGame(RenderWindow& window)
	{
		Font font;
		font.loadFromFile("font/arial.ttf");	//Loading the font that I have added in this folder (arial)...
		Text text, text1, text2, text3;
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{  
				if (event.type == Event::MouseButtonPressed)	//If the mouse button is pressed
				{
					if (event.mouseButton.button == Mouse::Left)	//If its a left click...
					{
						if (event.mouseButton.x>=200 && event.mouseButton.x<=455 && event.mouseButton.y>=200 && event.mouseButton.y<=250 )	
							return;
						else if (event.mouseButton.x>=200 && event.mouseButton.x<=455 && event.mouseButton.y>=300 && event.mouseButton.y<=350 )	
						{
							game_finished = true;
							window.close();	//This will close the window and game will end...
						}
						else if (event.mouseButton.x>=200 && event.mouseButton.x<=550 && event.mouseButton.y>=400 && event.mouseButton.y<=450 )	
							window.close();	//This will only close the window and game will be saved in the menu class..
					}
				}
			}
			text.setFont(font); 
			text.setString("Game is Paused");
			text.setCharacterSize(40);
			text.setFillColor(Color::White);
			text.setStyle(Text::Bold | Text::Underlined);
			text.setPosition(200,0);
			text1.setFont(font); 
			text1.setString("-> Resume Game");
			text1.setCharacterSize(30);
			text1.setFillColor(Color::Red);
			text1.setStyle(Text::Bold);
			text1.setPosition(200,200);
			text2.setFont(font); 
			text2.setString("-> Finish Game");
			text2.setCharacterSize(30);
			text2.setFillColor(Color::Red);
			text2.setStyle(Text::Bold);
			text2.setPosition(200,300);
			text3.setFont(font); 
			text3.setString("-> Save State & Close");
			text3.setCharacterSize(30);
			text3.setFillColor(Color::Red);
			text3.setStyle(Text::Bold);
			text3.setPosition(200,400);
			window.clear(Color::Black); //clears the screen
			window.clear(Color::Black); //clears the screen
			window.draw(background);  // setting background
			window.draw(text);
			window.draw(text1);
			window.draw(text2);
			window.draw(text3);
			window.display();	
		}
	}
	
};


