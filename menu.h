//
#include <SFML/Graphics.hpp>
#include<fstream>
using namespace sf;
//
#include "game.h"
class Menu{
public:
//add menu attributes here
Menu()
{

//constructors body
}

void display_menu()
{
    Game g; 
//display menu screen here
	RenderWindow window(VideoMode(780, 780), "Menu");
	bool start_game = true;
	Font font, font1;
	font.loadFromFile("font/Birds of Paradise.ttf");	//Loading the font that I have added in this folder (BOP)...
	font1.loadFromFile("font/Garet-Book.ttf");	//Loading the font that I have added in this folder (GB)...
	Text text, text1, text2, text3, text4;
	Sprite background;
	Texture bg_texture;
	bg_texture.loadFromFile("img/background_1.png");
	background.setTexture(bg_texture);
	background.setScale(1.4, 1.1);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{  
			if (event.type == Event::MouseButtonPressed)	//If the mouse button is pressed
			{
				if (event.mouseButton.button == Mouse::Left)	//If its a left click...
				{
					if (event.mouseButton.x>=300 && event.mouseButton.x<=500 && event.mouseButton.y>=200 && event.mouseButton.y <= 250 )	
					//To close the menu and start the Game if the mouse is clicked at that option...
					{
						start_game = true;
						window.close();
					}
					else if(event.mouseButton.x>=300 && event.mouseButton.x<=500 && event.mouseButton.y>=300 && event.mouseButton.y<=350)	
					//To display the instructions window if the mouse is clicked at that option...
						display_instructions(window);
					else if (event.mouseButton.x>=300 && event.mouseButton.x<=500 && event.mouseButton.y>=400 && event.mouseButton.y<=450)	
					//Displaying the high scores if the mouse is clicked at that option...
						show_highScores(window);
					else if (event.mouseButton.x>=300 && event.mouseButton.x<=400 && event.mouseButton.y>=500 && event.mouseButton.y<=550)	
					//To close the menu screen and quit if the mouse is clicked at that option...
					{
						 start_game = false;	//Now the game will not start...
						 window.close(); 
					}
				}
			}
		}
		text.setFont(font1); 
		text.setString("Space Shooter Game");
		text.setCharacterSize(40);
		text.setFillColor(Color::White);
		text.setStyle(Text::Bold | Text::Underlined);
		text.setPosition(200,0);
		text1.setFont(font); 
		text1.setString("-> Start Game");
		text1.setCharacterSize(30);
		text1.setFillColor(Color::White);
		text1.setStyle(Text::Bold);
		text1.setPosition(300,200);
		text2.setFont(font); 
		text2.setString("-> Instructions");
		text2.setCharacterSize(30);
		text2.setFillColor(Color::White);
		text2.setStyle(Text::Bold);
		text2.setPosition(300,300);
		text3.setFont(font); 
		text3.setString("-> High Scores");
		text3.setCharacterSize(30);
		text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold);
		text3.setPosition(300,400);
		text4.setFont(font); 
		text4.setString("-> Exit");
		text4.setCharacterSize(30);
		text4.setFillColor(Color::White);
		text4.setStyle(Text::Bold);
		text4.setPosition(300,500);
		window.clear(Color::Black); //clears the screen
		window.draw(background);  // setting background
		window.draw(text);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);	
		window.display();	
	}
// add functionality of all the menu options here
	if (start_game)
	{
		fstream file("Scores.txt", ios::app);
		RenderWindow window(VideoMode(780, 780), "User Input");
		string name = "";
		while (window.isOpen())
		{	
			Event event;
			while (window.pollEvent(event))
			{  
				
				if (event.type == Event::MouseButtonPressed)	//If the mouse button is pressed
				{
					if (event.mouseButton.button == Mouse::Left)	//If its a left click...
					{
						if (event.mouseButton.x>=200 && event.mouseButton.x<=600 && event.mouseButton.y>=500 && event.mouseButton.y<=550)	
						//To close the menu and start the Game if the mouse is clicked at that option...
						{
							name += ' ';	//To add a space between score and name in the file...
							file<<name;	//To store name in file...
		            		file.close();	//To close the text file ...
							window.close(); 
						}
					}
				}
				if (event.type == Event::TextEntered)	//To record the name that the user types on keyboard...
			  	{
			  		if (char(event.text.unicode) != ' ' )	//Ignoring the space character...
			  		//As enter key and space must not be saved, it will alter the file managment...
			  			name += char(event.text.unicode);	
			  	}
			  	if (event.type == Event::KeyPressed)
			  	{
			  		if (event.key.code == Keyboard::Return)
			  			//As enter key and space must not be saved, it will alter the file managment...
			  			{
			  				//Treating enter as name has finished...
			  				name += ' ';	//To add a space between score and name in the file...
							file<<name;	//To store name in file...
		            		file.close();	//To close the text file ...
							window.close(); 
			  			}
			  	}
			}
			text.setFont(font1); 
			text.setString("Enter Your Name: ");
			text.setCharacterSize(40);
			text.setFillColor(Color::White);
			text.setStyle(Text::Bold);
			text.setPosition(200,100);
			text1.setFont(font); 
			text1.setString(name);
			text1.setCharacterSize(40);
			text1.setFillColor(Color::White);
			text1.setStyle(Text::Bold | Text::Underlined);
			text1.setPosition(200,300);
			text2.setFont(font1); 
			text2.setString("Click Here To Start Game");
			text2.setCharacterSize(30);
			text2.setFillColor(Color::White);
			text2.setStyle(Text::Underlined);
			text2.setPosition(200,500);
			window.clear(Color::Black); //clears the screen
			window.draw(background);  // setting background
			window.draw(text);
			window.draw(text1);
			window.draw(text2);
			window.display();	
		}
	   	g.start_game();	//This will start the game...
	   	bool restart = false;
	   	if (g.game_finished)	//To check if the game is finished, when the lives of the player are over...
	   	{
			fstream file("Scores.txt", ios::app);
			RenderWindow window(VideoMode(780, 780), "Game Over");
			while (window.isOpen())
			{	
				Event event;
				while (window.pollEvent(event))
				{  
					if (event.type == Event::MouseButtonPressed)	//If the mouse button is pressed
					{
						if (event.mouseButton.button == Mouse::Left)	//If its a left click...
						{
							if (event.mouseButton.x>=200 && event.mouseButton.x<=600 && event.mouseButton.y>=500 && event.mouseButton.y<=550)	
							//To close the menu and start the Game if the mouse is clicked at that option...
							{
								file<<g.score<<endl;	//To store score in file...
				        		file.close();	//To close the text file ...
				        		restart = true;
								window.close();
							}
						}
					}

				}
				text.setFont(font1); 
				text.setString("Your Game Is Finished");
				text.setCharacterSize(40);
				text.setFillColor(Color::White);
				text.setStyle(Text::Bold | Text::Underlined);
				text.setPosition(200,100);
				text1.setFont(font1); 
				string display = "Your Score: ";
				display += to_string(g.score);
				text1.setString(display);
				text1.setCharacterSize(30);
				text1.setFillColor(Color::White);
				text1.setStyle(Text::Bold);
				text1.setPosition(200,300);
				text2.setFont(font1); 
				text2.setString("Return To Main Menu");
				text2.setCharacterSize(30);
				text2.setFillColor(Color::White);
				text2.setStyle(Text::Underlined);
				text2.setPosition(200,500);
				window.clear(Color::Black); //clears the screen
				window.draw(background);  // setting background
				window.draw(text);
				window.draw(text1);
				window.draw(text2);
				window.display();	
			}
		}
		else	//If the window was closed and game not to restart, means to save state of game
		{
			//Saving the state of game and then closing the file...
			ofstream outfile ("Save_State.txt");
		//	outfile<<g;
			outfile.close();
		}
		if (restart)
			display_menu();	//To return the player to main menu...
	}
}	
void display_instructions (RenderWindow& window)
{
	Font font1, font2;
	font1.loadFromFile("font/Garet-Book.ttf");	//Loading the font that I have added in this folder (Garet-Book)...
	font2.loadFromFile("font/arial.ttf");	//Loading the font that I have added in this folder (arial)...
	Text text, text1, text2, text3;
	Sprite background;
	Texture bg_texture;
	bg_texture.loadFromFile("img/background.jpg");
	background.setTexture(bg_texture);
	background.setScale(1.4, 1.1+0.5);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{  
			if (event.type == Event::MouseButtonPressed)	//If the mouse button is pressed
			{
				if (event.mouseButton.button == Mouse::Left)	//If its a left click...
				{
					if (event.mouseButton.x>=450 && event.mouseButton.x<=755 && event.mouseButton.y>=650 && event.mouseButton.y<=700 )	
						return;
				}
			}
		}
		text.setFont(font1); 
		text.setString("Instructions");
		text.setCharacterSize(40);
		text.setFillColor(Color::White);
		text.setStyle(Text::Bold | Text::Underlined);
		text.setPosition(200,0);
		text1.setFont(font2); 
		text1.setString("-> Rules For Scores");
		text1.setCharacterSize(30);
		text1.setFillColor(Color::White);
		text1.setStyle(Text::Bold);
		text1.setPosition(100,200);
		text2.setFont(font1); 
		text2.setString("1)Destroy invaders = level * invaders config * 10;\n(In level config ,alpha = 1, beta = 2, & gamma = 3)\n2)Dodging monster = 40\n3)Dodging Dragon = 50\n4)Dodging Danger Sign = 5\n");
		text2.setCharacterSize(25);
		text2.setFillColor(Color::White);
		text2.setStyle(Text::Bold);
		text2.setPosition(0,300);
		text3.setFont(font2); 
		text3.setString("Exit Instructions Page");
		text3.setCharacterSize(30);
		text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold | Text::Underlined);
		text3.setPosition(450,650);
		window.clear(Color::Black); //clears the screen
		window.draw(background);  // setting background
		window.draw(text);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.display();	

	}
}
void show_highScores (RenderWindow& window)
{
	Font font;
	font.loadFromFile("font/arial.ttf");	//Loading the font that I have added in this folder (arial)...
	Text text, text1, text2, text3, text4;
	Sprite background;
	Texture bg_texture;
	bg_texture.loadFromFile("img/background.jpg");
	background.setTexture(bg_texture);
	background.setScale(1.4, 1.1+0.5);
	//Calculating high scores..
	ifstream infile("Scores.txt");
	int counter=0;
	string name;
	string score;
	while(infile>>name>>score)
		counter++;	//Counting how mnay elemnets in the file
	string* names = nullptr;
	int* scores = nullptr;
	if (counter > 1)
	{
		names = new string [counter];
		scores = new int[counter];
	}
	else if (counter == 1)
	{
		names = new string;
		scores = new int;
	}
	infile.close();
	infile.open("Scores.txt");
	int new_counter = 0;
	if (counter>1)
	{
		while(infile>>names[new_counter]>>scores[new_counter])
			new_counter++;
	}
	else if (counter == 1)
	{
		while(infile>>(*names)>>(*scores))
			new_counter++;
	}
	int temp;	//to temporiarily store the score while swapping...
	string temp_s;	//to temporarily store the string while swapping...
    infile.close();	//Closing the opened file...
    //Below is the algorithm for binary search to sort the scores to get high scores
    if (counter > 1)
    {
		for (int i=0; i<counter; i++)
		{
			for(int j=0; j<counter-1; j++)
		    {
	 	 		if (scores[j] < scores[j+1])
		   		{
		   			temp = scores[j];
		       		temp_s = names[j];
		       		scores[j] = scores[j+1];
		       		names[j] = names[j+1];
		       		scores[j+1] = temp;
		       		names[j+1] = temp_s;
		       	}
		   	}
		}
	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{  
			if (event.type == Event::MouseButtonPressed)	//If the mouse button is pressed
			{
				if (event.mouseButton.button == Mouse::Left)	//If its a left click...
				{
					if (event.mouseButton.x>=450 && event.mouseButton.x<=755 && event.mouseButton.y>=600 && event.mouseButton.y<=650 )	
					{
						//First deleting the dynamically created arrays...
						if (counter>1)
						{
							delete[] scores;
							delete[] names;
						}
						else if (counter == 1)
						{
							delete scores;
							delete names;
						}
						scores = nullptr;
						names = nullptr;
						return;
					}
				}
			}
		}
		text.setFont(font); 
		text.setString("High Scores: ");
		text.setCharacterSize(40);
		text.setFillColor(Color::White);
		text.setStyle(Text::Bold | Text::Underlined);
		text.setPosition(200,0);
		text1.setFont(font); 
		string player1 = "-> Position 1: ";
		if (counter>=1)
		{
			player1 += names[0];
			player1 += "\tScore: ";
			player1 += to_string(scores[0]);
		}
		else
		{
			player1 += "This position is still vacant...";
		}
		text1.setString(player1);
		text1.setCharacterSize(30);
		text1.setFillColor(Color::White);
		text1.setStyle(Text::Bold);
		text1.setPosition(100,200);
		text2.setFont(font); 
		string player2 = "-> Position 2: ";
		if (counter>=2)
		{
			player2 += names[1];
			player2 += "\tScore: ";
			player2 += to_string(scores[1]);
		}
		else
		{
			player2 += "This position is still vacant...";
		}
		text2.setString(player2);
		text2.setCharacterSize(30);
		text2.setFillColor(Color::White);
		text2.setStyle(Text::Bold);
		text2.setPosition(100,300);
		text3.setFont(font); 
		string player3 = "-> Position 3: ";
		if (counter>=3)
		{
			player3 += names[2];
			player3 += "\tScore: ";
			player3 += to_string(scores[2]);
		}
		else
		{
			player3 += "This position is still vacant...";
		}
		text3.setString(player3);
		text3.setCharacterSize(30);
		text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold);
		text3.setPosition(100,400);
		text4.setFont(font); 
		text4.setString("Exit High Scores Page");
		text4.setCharacterSize(30);
		text4.setFillColor(Color::White);
		text4.setStyle(Text::Bold | Text::Underlined);
		text4.setPosition(450,600);
		window.clear(Color::Black); //clears the screen
		window.draw(background);  // setting background
		window.draw(text);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.display();	
	}
	if (counter>1)
	{
		delete[] scores;
		delete[] names;
	}
	else if (counter == 1)
	{
		delete scores;
		delete names;
	}
	scores = nullptr;
	names = nullptr;
}

};

