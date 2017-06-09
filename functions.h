#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdlib.h>
#include <string.h>
#include <ctime>


void init();
void Ai_Logic(int speed);
void setting_menu();
void clean();
void Logic(int);
void ResetBall();
void DrawnScreen();
bool menu();
int game_menu();


extern bool sound;
extern SDL_Event event0;
extern SDL_Rect clips1;
extern SDL_Rect clips2;
extern SDL_Surface* buttonSheet1;
extern SDL_Surface* buttonSheet2;
extern SDL_Surface* screen;
extern void apply_surface( int x,int y,SDL_Surface*,SDL_Surface*,SDL_Rect*);


//Button Class
extern Mix_Chunk *button_song;

class Button
{
    private:
    //The attributes of the button
    SDL_Rect box;
    
    bool over;
    bool push;
    bool gone=false;

    //The part of the button sprite sheet that will be shown
    SDL_Rect clip;

    public:
    //Handles events and set the button's sprite region
    
    bool get_push()
    {
		return push;
	}
	
	void set_push()
	{
		push=false;
	}
    
	void handle_events()
	{
		
		//The mouse offsets
		int x = 0, y = 0;

		//If the mouse moved
		if( event0.type == SDL_MOUSEMOTION )
		{
			//Get the mouse offsets
			x = event0.motion.x;
			y = event0.motion.y;

			//If the mouse is over the button
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
			{
				//Set the button sprite
				//printf("x = %d\ny = %d\n",x,y);
				clip = clips1;
				over=true;
				if(gone==true)
				{
					if(sound==true)
						Mix_PlayChannel(-1,button_song,0);
					gone=false;
				}
			}
			//If not
			else
			{
				//Set the button sprite
				clip = clips2;
				over=false;
				gone=true;
			}
		}
		
		 //If a mouse button was pressed
		if( event0.type == SDL_MOUSEBUTTONDOWN )
		{
			//If the left mouse button was pressed
			if( event0.button.button == SDL_BUTTON_LEFT )
			{
				//Get the mouse offsets
				x = event0.button.x;
				y = event0.button.y;

				//If the mouse is over the button
				if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
				{
					//Set the button sprite
					push=true;
				}
			}
		}
  
	}

    //Shows the button on the screen
    void show()
	{
		//Show the button
		if(over==false)
			apply_surface( box.x, box.y, buttonSheet1, screen, &clip );
		else if(over==true)
			apply_surface( box.x, box.y, buttonSheet2, screen, &clip );
	}
    
    Button( int x, int y, int w, int h)
	{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    push=false;
    gone=true;
    //Set the default sprite
    clip = clips1;
	}
    
};


 #endif
