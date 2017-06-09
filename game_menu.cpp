#include "functions.h"

extern SDL_Surface* optimalize(const char *titles);
extern void show_button_text(const char *text, int x, int y);
 
extern SDL_Rect clips1;
extern SDL_Rect clips2;
extern SDL_Event event0;

int game_menu()
{
	SDL_FillRect(screen,NULL,0);
	
	TTF_Font *font=nullptr;
	TTF_Font *font4=nullptr;
	SDL_Color white={255,255,255};
	SDL_Surface *title=nullptr;
	SDL_Rect offset;
	bool quit=false;
	
	offset.x=300;
	offset.y=0;
	font4=TTF_OpenFont("data/ttf/Anothers.ttf",25);
	font=TTF_OpenFont("data/ttf/Airacobra_Italic.ttf",40);
	title=TTF_RenderText_Solid(font,"G  A  M  E",white);
	
	char title1[]="data/images/backg.png";
	char title2[]="data/images/Button1.png";
	char title3[]="data/images/Button2.png";
	
	SDL_Surface* optimizedImage = optimalize(title1);
    buttonSheet1 = optimalize(title2);
    buttonSheet2 = optimalize(title3);
    
     Uint32 colorkey1 = SDL_MapRGB( buttonSheet1->format, 0, 0, 0 );
	 Uint32 colorkey2 = SDL_MapRGB( buttonSheet2->format, 0, 0, 0 );
	 SDL_SetColorKey( buttonSheet1, SDL_SRCCOLORKEY, colorkey1 );
	 SDL_SetColorKey( buttonSheet2, SDL_SRCCOLORKEY, colorkey2 );
	
	 //Képernyőre rajzolás
	 SDL_BlitSurface( optimizedImage,NULL,screen,NULL);
	 SDL_BlitSurface(title,NULL,screen,&offset);
	 offset.x=510;
	 offset.y=560;
     char nevem[23];
	 sprintf(nevem,"Made by: Kert%csz  %cd%cm",233,193,193);
	 title=TTF_RenderText_Solid(font4,nevem,white);
	 SDL_BlitSurface(title,NULL,screen,&offset);
     SDL_Flip(screen);
     
	 Button Player1_Button(268, 120, 264, 83 );
     Button Player2_Button(268, 250, 264, 83 );
     Button BackButton(268, 380, 264, 83 );

	 while(quit==false)
     {
		while(SDL_WaitEvent(&event0))
		{
			if(event0.type==SDL_QUIT)
			{
				exit(0);
			}
			Player1_Button.handle_events();
			Player1_Button.show();
			Player2_Button.handle_events();
			Player2_Button.show();
			BackButton.handle_events();
			BackButton.show();
			show_button_text("1 Player",290,150);
			show_button_text("2 Player",274,280);
			show_button_text("Back",330,410);
			SDL_Flip(screen);
			if(BackButton.get_push()==true)
			{
				TTF_CloseFont(font);
				TTF_CloseFont(font4);
				SDL_FreeSurface(title);
				SDL_FreeSurface(optimizedImage);
				return 0;
			}
			if(Player1_Button.get_push()==true)
			{
				TTF_CloseFont(font);
				TTF_CloseFont(font4);
				SDL_FreeSurface(title);
				SDL_FreeSurface(optimizedImage);
				return 1;
			}
			if(Player2_Button.get_push()==true)
			{
				TTF_CloseFont(font);
				TTF_CloseFont(font4);
				SDL_FreeSurface(title);
				SDL_FreeSurface(optimizedImage);
				return 2;
			}
		}
	 }
	return 0;
}
