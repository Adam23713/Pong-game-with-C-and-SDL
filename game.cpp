#include "functions.h"

extern SDL_Surface* optimalize(const char *titles);

const int WIDTH = 800;
const int HEIGHT = 600;
const int BBP = 32;
const int textsize=28;
const int data_size=40;
extern int game_countinue;
extern int default_ball_R;
extern int Ai;
int Xvel,Yvel,LastX,LastY;
int player_points,ai_points;
SDL_Surface* screen=nullptr;
SDL_Surface* field=nullptr;
SDL_Surface* soccer=nullptr;
SDL_Surface* bat_p=nullptr;
SDL_Surface* message1=nullptr;
SDL_Surface* message2=nullptr;
SDL_Surface* pause_message=nullptr;
SDL_Color textcolor={23,202,187};
SDL_Event event;
SDL_Rect Playerpaddle;
SDL_Rect Aipaddle;
SDL_Rect Ball;
SDL_Rect cut;
TTF_Font *font=nullptr;
TTF_Font *font2=nullptr;
Mix_Chunk *pimples=nullptr;
Mix_Chunk *goal=nullptr;
Mix_Chunk *wall=nullptr;
Uint32 white;
Uint32 green;

void ResetBall()
{
	
	Ball.x=(WIDTH/2)-(Ball.w/2);
	Ball.y=(HEIGHT/2)-(Ball.h/2);

	int point=rand() % 4 ;

	if(point==0) //Ball felső sarok felé indul
	{
		Xvel=-default_ball_R;
		Yvel=-default_ball_R;
	}
	if(point==1) //Ball alsó sarok felé indul
	{
		Xvel=-default_ball_R;
		Yvel=default_ball_R;
	}
	if(point==2) //Jobb felső sarok felé indul
	{
		Xvel=default_ball_R;
		Yvel=-default_ball_R;
	}
	if(point==3) //Jobb alsó sarok felé indul
	{
		Xvel=default_ball_R;
		Yvel=default_ball_R;
	}

	
}

void Ai_Logic(int speed)
{
	static int ball_speed=1;
	Uint8 *keystates=SDL_GetKeyState(NULL);
	
	if(keystates[SDLK_ESCAPE])
	{
		if(event.key.keysym.sym==SDLK_ESCAPE)
		{
			game_countinue=true;
			if(menu()==true)
				exit(0);
			ResetBall();
			printf("default_ball_R = %d\n",default_ball_R);
		}
	}
	//Pause
	if(keystates[SDLK_SPACE])
	{
		SDL_Rect offset;
		offset.y=HEIGHT/2;
		offset.x=(WIDTH/2)-5*12;
		pause_message = TTF_RenderText_Solid(font2,"Pause",textcolor);
		SDL_BlitSurface(pause_message,NULL,screen,&offset);
		SDL_Flip(screen);
		while(SDL_WaitEvent(&event))
		{
			if(event.type==SDL_KEYDOWN)
				if(event.key.keysym.sym==SDLK_SPACE)
					break;
		}
		SDL_Delay(200);
	}
	
	//Player 1 Move's
	if(keystates[SDLK_w]) Playerpaddle.y-=speed;
	if(keystates[SDLK_s]) Playerpaddle.y+=speed;
	if(Playerpaddle.y <= 0)	Playerpaddle.y=0;
	if(Playerpaddle.y + Playerpaddle.h >= HEIGHT) Playerpaddle.y = HEIGHT - 1 - Playerpaddle.h;
		
	//Ai Move's
	
	if(Aipaddle.y + 0.5 * Aipaddle.h > Ball.y + 0.5 *Ball.h)
	{
		Aipaddle.y-=speed + (-1)*(9 - Ai);
	}
	if(Aipaddle.y + 0.5 * Aipaddle.h < Ball.y + 0.5 *Ball.h)
	{
		Aipaddle.y+=speed + (-1)*(9 - Ai);
	}
	if(Aipaddle.y <= 0)	Aipaddle.y=0;
	if(Aipaddle.y + Aipaddle.h >= HEIGHT) Aipaddle.y = HEIGHT - 1 - Aipaddle.h;
	
	//The ball's function
	LastX = Xvel;
	LastY = Ball.y;
	
	Ball.x += Xvel;
	Ball.y += Yvel;
	
	//If the ball touches the wall
	if(Ball.y <= 0)
	{ 
		Ball.y = 0;
		if(sound==true)
			Mix_PlayChannel(-1,wall,0);
		Yvel=-Yvel;
	}
	if(Ball.y + Ball.h >= HEIGHT)
	{
		Ball.y = HEIGHT - 1 - Ball.h;
		if(sound==true)
			Mix_PlayChannel(-1,wall,0);
		Yvel=-Yvel;
	}
	
	
	//Player 1 bat========================================
	if(Playerpaddle.x + Playerpaddle.w - 1 >= Ball.x) //Ha egy vonalban van
	{	
		
		if(((Playerpaddle.y <= Ball.y || Playerpaddle.y <= Ball.y + Ball.h) && Playerpaddle.y + Playerpaddle.h -1 >=Ball.y))
		{
			if(Ball.x >= 1) Ball.x = Playerpaddle.x + Playerpaddle.w - 1;
			
			//Tapadás---------------------------------------------------
			if(keystates[SDLK_w])
			{
				if(Ball.y > LastY) //A labda lefele halad
				{
					Yvel-=ball_speed; //Lasítja
				}
				else if(Ball.y < LastY)
				{
					Yvel-=ball_speed; //Gyorsítja felfelé
				}
			}
			
			if(keystates[SDLK_s])
			{
				if(Ball.y > LastY)
				{
					Yvel+=ball_speed;
				}
				if(Ball.y < LastY)
				{
					Yvel+=ball_speed;	//Lassítja a felfele menő labdát
				}
			}
			if(Yvel==0) Yvel=1;
			//----------------------------------------------------------
			Xvel=-Xvel;
			if(sound==true)
				Mix_PlayChannel(-1,pimples,0);
		}
	}
	//=====================================================
	
		//Ai 2 bat=========================================
	if(Aipaddle.x <= Ball.x + Ball.w - 1) //Ha egy vonalban van
	{
		
		if((Aipaddle.y <= Ball.y || Aipaddle.y <= Ball.y + Ball.h - 1) && Aipaddle.y + Aipaddle.h -1 >=Ball.y)
		{
			if(Ball.x <= WIDTH-1) Ball.x = Aipaddle.x - Ball.w;
			Xvel=-Xvel;
			if(sound==true)
				Mix_PlayChannel(-1,pimples,0);
		}
	
	}
	if(Ball.x < 2)
	{
		if(sound==true)
			Mix_PlayChannel(-1,goal,0);
		SDL_Delay(100);
		ResetBall();
		ai_points++;
	}
	
	if(Ball.x + Ball.w > WIDTH-2)
	{
		if(sound==true)
			Mix_PlayChannel(-1,goal,0);
		SDL_Delay(100);
		ResetBall();
		player_points++;
	}
	
}


void Logic(int speed)
{
	static int ball_speed=1;
	Uint8 *keystates=SDL_GetKeyState(NULL);
	
	if(keystates[SDLK_ESCAPE])
	{
		if(event.key.keysym.sym==SDLK_ESCAPE)
		{
			game_countinue=true;
			if(menu()==true)
				exit(0);
			ResetBall();
			printf("default_ball_R = %d\n",default_ball_R);
		}
	}
	//Pause
	if(keystates[SDLK_SPACE])
	{
		SDL_Rect offset;
		offset.y=HEIGHT/2;
		offset.x=(WIDTH/2)-5*12;
		pause_message = TTF_RenderText_Solid(font2,"Pause",textcolor);
		SDL_BlitSurface(pause_message,NULL,screen,&offset);
		SDL_Flip(screen);
		while(SDL_WaitEvent(&event))
		{
			if(event.type==SDL_KEYDOWN)
				if(event.key.keysym.sym==SDLK_SPACE)
					break;
		}
		SDL_Delay(200);
	}
	
	//Player 1 Move's
	if(keystates[SDLK_w]) Playerpaddle.y-=speed;
	if(keystates[SDLK_s]) Playerpaddle.y+=speed;
	if(Playerpaddle.y <= 0)	Playerpaddle.y=0;
	if(Playerpaddle.y + Playerpaddle.h >= HEIGHT) Playerpaddle.y = HEIGHT - 1 - Playerpaddle.h;
		
	//Player 2 Move's
	if(keystates[SDLK_UP])   Aipaddle.y-=speed;
	if(keystates[SDLK_DOWN]) Aipaddle.y+=speed;
	if(Aipaddle.y <= 0)	Aipaddle.y=0;
	if(Aipaddle.y + Aipaddle.h >= HEIGHT) Aipaddle.y = HEIGHT - 1 - Aipaddle.h;
	
	//The ball's function
	LastX = Xvel;
	LastY = Ball.y;
	
	Ball.x += Xvel;
	Ball.y += Yvel;
	
	//If the ball touches the wall
	if(Ball.y <= 0)
	{
		Ball.y = 0;
		if(sound==true)
			Mix_PlayChannel(-1,wall,0);
		Yvel=-Yvel;
	}
	if(Ball.y + Ball.h >= HEIGHT)
	{
		Ball.y = HEIGHT - 1 - Ball.h;
		if(sound==true)
			Mix_PlayChannel(-1,wall,0);
		Yvel=-Yvel;
	}
	
	
	//Player 1 bat========================================
	if(Playerpaddle.x + Playerpaddle.w - 1 >= Ball.x) //Ha egy vonalban van
	{	
		
		if(((Playerpaddle.y <= Ball.y || Playerpaddle.y <= Ball.y + Ball.h) && Playerpaddle.y + Playerpaddle.h -1 >=Ball.y))
		{
			if(Ball.x >= 1) Ball.x = Playerpaddle.x + Playerpaddle.w - 1;
			
			//Tapadás---------------------------------------------------
			if(keystates[SDLK_w])
			{
				if(Ball.y > LastY) //A labda lefele halad
				{
					Yvel-=ball_speed; //Lasítja
				}
				else if(Ball.y < LastY)
				{
					Yvel-=ball_speed; //Gyorsítja felfelé
				}
			}
			
			if(keystates[SDLK_s])
			{
				if(Ball.y > LastY)
				{
					Yvel+=ball_speed;
				}
				if(Ball.y < LastY)
				{
					Yvel+=ball_speed;	//Lassítja a felfele menő labdát
				}
			}
			if(Yvel==0) Yvel=1;
			//----------------------------------------------------------
			Xvel=-Xvel;
			if(sound==true)
				Mix_PlayChannel(-1,pimples,0);
		}
	}
	//=====================================================
	
	//Player 2 bat=========================================
	if(Aipaddle.x <= Ball.x + Ball.w - 1) //Ha egy vonalban van
	{
		
		if((Aipaddle.y <= Ball.y || Aipaddle.y <= Ball.y + Ball.h - 1) && Aipaddle.y + Aipaddle.h -1 >=Ball.y)
		{
			if(Ball.x <= WIDTH-1) Ball.x = Aipaddle.x - Ball.w;
			
			//Tapadás---------------------------------------------------
			if(keystates[SDLK_UP])
			{
				if(Ball.y > LastY)
				{
					Yvel-=ball_speed;
				}
				else if(Ball.y < LastY)
				{
					Yvel-=ball_speed;
				}
			}
			
			if(keystates[SDLK_DOWN])
			{
				if(Ball.y > LastY)
				{
					Yvel+=ball_speed;
				}
				if(Ball.y < LastY)
				{
					Yvel+=ball_speed;	//Lassítja a felfele menő labdát
				}
			}
			if(Yvel==0) Yvel=1;
			//----------------------------------------------------------
			Xvel=-Xvel;
			if(sound==true)
				Mix_PlayChannel(-1,pimples,0);
		}
	}
	//======================================================
	
	if(Ball.x < 2)
	{
		if(sound==true)
			Mix_PlayChannel(-1,goal,0);
		SDL_Delay(100);
		ResetBall();
		ai_points++;
	}
	
	if(Ball.x + Ball.w > WIDTH-2)
	{
		if(sound==true)
			Mix_PlayChannel(-1,goal,0);
		SDL_Delay(100);
		ResetBall();
		player_points++;
	}
	
}

void DrawnScreen()
{
	SDL_Rect offset1;
	SDL_Rect offset2;
	
	char data1[data_size];
	char data2[data_size];
	offset2.y = 0;
	sprintf(data1,"Player 1 : %d",player_points);
	sprintf(data2,"Player 2 : %d",ai_points);
	offset2.x=WIDTH-strlen(data2)*12;
	message1 = TTF_RenderText_Solid(font,data1,textcolor);
	message2 = TTF_RenderText_Solid(font,data2,textcolor);
	
	SDL_BlitSurface(field,NULL,screen,0);
	offset1.x=Ball.x;
	offset1.y=Ball.y;
	SDL_BlitSurface(soccer,NULL,screen,&offset1);
		
	offset1.x=Playerpaddle.x;
	offset1.y=Playerpaddle.y;
	SDL_BlitSurface(bat_p,&cut,screen,&offset1);
	
	offset1.x=Aipaddle.x;
	offset1.y=Aipaddle.y;
	SDL_BlitSurface(bat_p,&cut,screen,&offset1);
	
	offset1.y = offset1.x = 0;
	//SDL_FillRect(screen,&Playerpaddle,white);
	//SDL_FillRect(screen,&Aipaddle,white);
	//SDL_FillRect(screen,&Ball,white);
	SDL_BlitSurface(message1,NULL,screen,&offset1);
	SDL_BlitSurface(message2,NULL,screen,&offset2);
	
	SDL_Flip(screen);
}

void init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		exit(1);
	if(TTF_Init() == -1)
		exit(1);
		
	screen=SDL_SetVideoMode(WIDTH,HEIGHT,BBP,SDL_HWSURFACE);
	if(screen==NULL)
		exit(1);
		
	field = optimalize("data/images/field.jpg");
	soccer= optimalize("data/images/soccer.png");
	bat_p= optimalize("data/images/bat.png");
	Uint32 colorkey1 = SDL_MapRGB( soccer->format, 0, 0, 0 );
	SDL_SetColorKey( soccer, SDL_SRCCOLORKEY, colorkey1 );
	
	cut.x=0;
	cut.y=0;
	cut.w=20;
	cut.h=100;
		
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	pimples=Mix_LoadWAV("data/sound/pimples.wav");
	goal=Mix_LoadWAV("data/sound/goal.wav");
	wall=Mix_LoadWAV("data/sound/wall.wav");
		
	ai_points = player_points = 0;
	SDL_WM_SetCaption("PONG",NULL);
	font=TTF_OpenFont("data/ttf/Quikhand.otf",28);
	font2=TTF_OpenFont("data/ttf/Quikhand.otf",48);
	
	Playerpaddle.x=20;
	Playerpaddle.h=100;
	Playerpaddle.w=20;
	Playerpaddle.y=250;
	
	Aipaddle.x=760;
	Aipaddle.h=100;
	Aipaddle.w=20;
	Aipaddle.y=250;
	
	Ball.h=20;
	Ball.w=20;
	Ball.x=(WIDTH/2)-(Ball.w/2);
	Ball.y=(HEIGHT/2)-(Ball.h/2);
		
	white=SDL_MapRGB(screen->format,255,255,255);
	green=SDL_MapRGB(screen->format,46,133,46);
	
	srand(time(NULL));
}

void clean()
{
	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	TTF_Quit();
	Mix_FreeChunk(pimples);
	Mix_FreeChunk(goal);
	Mix_FreeChunk(wall);
	Mix_CloseAudio();
	SDL_FreeSurface(message1);
	SDL_FreeSurface(message2);
	SDL_FreeSurface(field);
	SDL_FreeSurface(soccer);
	SDL_FreeSurface(bat_p);
	SDL_FreeSurface(pause_message);
	SDL_Quit();
}
