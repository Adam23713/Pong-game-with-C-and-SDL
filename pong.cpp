#include "functions.h"

extern SDL_Event event;
int player_mode;
bool game_countinue=false;
bool sound=true;
int speed=5;
int Ai=9;

int default_ball_R=1;

int main(int argc, char* argv[])
{
	bool quit;
	
	init();
	quit = menu();
	if(quit==false)
	{
		ResetBall();
		while(quit==false)
		{
			SDL_PollEvent(&event);
		
			if(event.type==SDL_QUIT)
			{
				quit=true;
			}
			if(player_mode==2)
				Logic(speed);
			else if(player_mode==1)
				Ai_Logic(speed);
			DrawnScreen();
		}
	}
	clean();
	return EXIT_SUCCESS;
}


