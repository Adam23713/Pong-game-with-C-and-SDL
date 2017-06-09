#include "functions.h"

extern SDL_Surface* screen;
extern const int WIDTH=800;
extern const int HEIGHT=600;
extern int player_mode;
const int button_w=264;
const int button_h=83;
extern int game_countinue;
bool change;
Mix_Chunk *button_song=nullptr;
SDL_Surface* buttonSheet1=nullptr;
SDL_Surface* buttonSheet2=nullptr;
SDL_Surface* title = nullptr;
TTF_Font *font0=nullptr;
TTF_Font *font1=nullptr;
TTF_Font *font3=nullptr;
SDL_Color w = {255,255,255};
SDL_Color g = {25,130,52};
SDL_Event event0;

SDL_Rect clips1;
SDL_Rect clips2;


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

 SDL_Surface* optimalize(const char *titles)
{
	SDL_Surface* optimizedImage = nullptr;
    SDL_Surface* tempB = nullptr;
    
    tempB = IMG_Load(titles);
    //Load Pictures
    if( tempB != NULL )
    {
        optimizedImage = SDL_DisplayFormat(tempB);
        SDL_FreeSurface(tempB);
     }
     else
	{
		exit(1);
		puts("Nincs ilyen fájl!");
	}
		
	return optimizedImage;
    
}

void show_button_text(const char *text, int x, int y)
{
	 SDL_Rect offset;
	 offset.x=x;
     offset.y=y;  
     
     title=TTF_RenderText_Solid(font1,text,g);
     SDL_BlitSurface(title,NULL,screen,&offset);
}

bool menu()
{
	SDL_Rect offset;
	bool quit=false;
	char title1[]="data/images/backg.png";
	char title2[]="data/images/Button1.png";
	char title3[]="data/images/Button2.png";
	button_song=Mix_LoadWAV("data/sound/button.wav");

	SDL_Surface* optimizedImage = optimalize(title1);
    buttonSheet1 = optimalize(title2);
    buttonSheet2 = optimalize(title3);
	
	 Uint32 colorkey1 = SDL_MapRGB( buttonSheet1->format, 0, 0, 0 );
	 Uint32 colorkey2 = SDL_MapRGB( buttonSheet2->format, 0, 0, 0 );
	 SDL_SetColorKey( buttonSheet1, SDL_SRCCOLORKEY, colorkey1 );
	 SDL_SetColorKey( buttonSheet2, SDL_SRCCOLORKEY, colorkey2 );
	 
	 offset.x=280;
	 offset.y=0;
	 font0=TTF_OpenFont("data/ttf/Airacobra_Italic.ttf",40);
	 font1=TTF_OpenFont("data/ttf/Alexis_Expanded.ttf",35);
	 font3=TTF_OpenFont("data/ttf/Anothers.ttf",25);
	 title=TTF_RenderText_Solid(font0,"  P  O  N  G",w);
     SDL_BlitSurface(optimizedImage,NULL,screen,NULL);
     SDL_BlitSurface(title,NULL,screen,&offset);
     offset.x=510;
	 offset.y=560;
     char nevem[23];
	 sprintf(nevem,"Made by: Kert%csz  %cd%cm",233,193,193);
	 title=TTF_RenderText_Solid(font3,nevem,w);
	 SDL_BlitSurface(title,NULL,screen,&offset);
    
     SDL_Flip(screen);
 
	//Clip the sprite sheet
    clips1.x = 0;
    clips1.y = 0;
    clips1.w = 264;
    clips1.h = 83;

	//Kék
    clips2.x = 0;
    clips2.y = 0;
    clips2.w = 264;
    clips2.h = 83;
    
    Button GameButton( WIDTH/2-button_w/2, 120, button_w, button_h );
    Button SettingButton( WIDTH/2-button_w/2, 250, button_w, button_h );
    Button ExitButton( WIDTH/2-button_w/2, 380, button_w, button_h );
 
     while(quit==false)
     {
		while(SDL_WaitEvent(&event0))
		{
			if(event0.type==SDL_QUIT)
			{
				quit=true;
				break;
			}
			GameButton.handle_events();
			GameButton.show();
			SettingButton.handle_events();
			SettingButton.show();
			ExitButton.handle_events();
			ExitButton.show();
			if(game_countinue==true)
				show_button_text("Back",329,150);
			else
				show_button_text("Game",329,150);
			show_button_text("Setting",WIDTH/2-button_w+8*20,280);
			show_button_text("Exit",WIDTH/2-button_w+205,410);
			SDL_Flip(screen);
			if(SettingButton.get_push()==true)
			{
				SettingButton.set_push();
				change=false;
				setting_menu();
				if(change==true)
					setting_menu();
				SDL_FillRect(screen,NULL,0);
				offset.x=280;
				offset.y=0;
				SDL_BlitSurface(optimizedImage,NULL,screen,NULL);
				title=TTF_RenderText_Solid(font0,"  P  O  N  G",w);
				SDL_BlitSurface(title,NULL,screen,&offset);
				offset.x=510;
				offset.y=560;
				title=TTF_RenderText_Solid(font3,nevem,w);
				SDL_BlitSurface(title,NULL,screen,&offset);
				SDL_Flip(screen);
			}
			if(GameButton.get_push()==true)
			{
				
				if(game_countinue==true)
					return false;
				
				player_mode=game_menu();
				if(player_mode>0)
					return false;
				GameButton.set_push();
				SDL_FillRect(screen,NULL,0);
				offset.x=280;
				offset.y=0;
				SDL_BlitSurface(optimizedImage,NULL,screen,NULL);
				title=TTF_RenderText_Solid(font0,"  P  O  N  G",w);
				SDL_BlitSurface(title,NULL,screen,&offset);
				offset.x=510;
				offset.y=560;
				title=TTF_RenderText_Solid(font3,nevem,w);
				SDL_BlitSurface(title,NULL,screen,&offset);
				SDL_Flip(screen);
			}
			if(ExitButton.get_push()==true)
			{
				TTF_CloseFont(font0);
				TTF_CloseFont(font1);
				SDL_FreeSurface(optimizedImage);
				SDL_FreeSurface(buttonSheet1);
				SDL_FreeSurface(buttonSheet2);
				SDL_FreeSurface(title);
				return true;
			}
		}
	 }
     TTF_CloseFont(font0);
     TTF_CloseFont(font1);
     SDL_FreeSurface(optimizedImage);
     SDL_FreeSurface(buttonSheet1);
     SDL_FreeSurface(buttonSheet2);
     SDL_FreeSurface(title);
     Mix_FreeChunk(button_song);
     return quit;
}
