#include "functions.h"

#include "functions.h"

extern SDL_Surface* optimalize(const char *titles);
extern void show_button_text(const char *text, int x, int y);
 
extern SDL_Rect clips1;
extern SDL_Rect clips2;
extern SDL_Event event0;
bool full_screen=false;
extern bool change;
extern bool sound;
extern int speed;
extern int default_ball_R;
extern int Ai;

void setting_menu()
{
	SDL_FillRect(screen,NULL,0);

	TTF_Font *f1=nullptr;
	TTF_Font *f2=nullptr;
	TTF_Font *f3=nullptr;
	TTF_Font *f4=nullptr;
	TTF_Font *f5=nullptr;
	SDL_Rect offset;
	bool quit=false;
	char adat1[5];
	char adat2[5];
	char adat3[5];
	SDL_Color white={255,255,255};
	SDL_Surface *title11=nullptr;
	SDL_Surface *Ai_w=nullptr;
	SDL_Surface *bat=nullptr;
	SDL_Surface *ball=nullptr;
	SDL_Surface *bat_speed=nullptr;
	SDL_Surface *ball_speed=nullptr;
	SDL_Surface *b0=nullptr;
	SDL_Surface *b1=nullptr;
	SDL_Surface *b2=nullptr;
	SDL_Surface *b3=nullptr;
	SDL_Surface *b4=nullptr;
	SDL_Surface *b5=nullptr;
	SDL_Rect clr1;
	SDL_Rect clr2;
	SDL_Rect clr3;
	
	clr1.x=290;
	clr1.y=440;
	clr1.w=30;
	clr1.h=30;
	
	clr2.x=500;
	clr2.y=440;
	clr2.w=30;
	clr2.h=30;
	
	clr3.x=680;
	clr3.y=440;
	clr3.w=30;
	clr3.h=30;

	f1=TTF_OpenFont("data/ttf/Airacobra_Italic.ttf",40);
	f2=TTF_OpenFont("data/ttf/Alexis_Expanded.ttf",30);
	f5=TTF_OpenFont("data/ttf/Alexis_Expanded.ttf",25);
	f4=TTF_OpenFont("data/ttf/Quikhand.otf",25);
	f3=TTF_OpenFont("data/ttf/Anothers.ttf",25);
	SDL_Surface* optimizedImage = optimalize("data/images/backg.png");
	b0 = optimalize("data/images/off.png");
	b1 = optimalize("data/images/on.png");
    b3 = optimalize("data/images/up.ico");
    b2 = optimalize("data/images/down.ico");
    b4 = optimalize("data/images/Button1.png");
    b5 = optimalize("data/images/Button2.png");
	

	 Uint32 colorkey0 = SDL_MapRGB( b0->format, 0, 0, 0 );
	 Uint32 colorkey1 = SDL_MapRGB( b1->format, 0, 0, 0 );
	 Uint32 colorkey2 = SDL_MapRGB( b2->format, 0, 0, 0 );
	 Uint32 colorkey3 = SDL_MapRGB( b3->format, 0, 0, 0 );
	 Uint32 colorkey4 = SDL_MapRGB( b4->format, 0, 0, 0 );
	 Uint32 colorkey5 = SDL_MapRGB( b5->format, 0, 0, 0 );
	 SDL_SetColorKey( b0, SDL_SRCCOLORKEY, colorkey0 );
	 SDL_SetColorKey( b1, SDL_SRCCOLORKEY, colorkey1 );
	 SDL_SetColorKey( b2, SDL_SRCCOLORKEY, colorkey2 );
	 SDL_SetColorKey( b3, SDL_SRCCOLORKEY, colorkey3 );
	 SDL_SetColorKey( b4, SDL_SRCCOLORKEY, colorkey4 );
	 SDL_SetColorKey( b5, SDL_SRCCOLORKEY, colorkey5 );
	 
	 
	  bat=TTF_RenderText_Solid(f4,"Bat speed:",white);
	  ball=TTF_RenderText_Solid(f4,"Ball speed:",white);
	 //Alap kinézet
	 title11=TTF_RenderText_Solid(f1,"SETTINGS",white);
	 offset.x=280;
	 offset.y=0;
	 SDL_BlitSurface(optimizedImage,NULL,screen,NULL);
	 SDL_BlitSurface(title11,NULL,screen,&offset);
	 offset.x=510;
	 offset.y=560;
     char nevem[23];
	 sprintf(nevem,"Made by: Kert%csz  %cd%cm",233,193,193);
	 title11=TTF_RenderText_Solid(f3,nevem,white);
	 SDL_BlitSurface(title11,NULL,screen,&offset);
     SDL_Flip(screen);
	 
	 //Feliratok
	 offset.x=50;
	 offset.y=450;
	 title11=TTF_RenderText_Solid(f2,"Speed",white);
	 SDL_BlitSurface(title11,NULL,screen,&offset); 
	 
	 offset.x=50;
	 offset.y=150;
	 title11=TTF_RenderText_Solid(f2,"Full Screen",white);
	 SDL_BlitSurface(title11,NULL,screen,&offset); 
	 
	 offset.x=50;
	 offset.y=300;
	 title11=TTF_RenderText_Solid(f2,"Sound",white);
	 SDL_BlitSurface(title11,NULL,screen,&offset);
	 
	 
	//Gombok
	Button back_Button(20, 500, 264, 83 );
	Button full_Button(500,140,30,30);
	Button sound_Button(500,290,30,30);
	Button r_down_Button(260,440,30,30);
	Button r_up_Button(320,440,30,30);	
	Button b_down_Button(470,440,30,30);
	Button b_up_Button(530,440,30,30);
	Button ai_up_Button(710,440,30,30);
	Button ai_down_Button(650,440,30,30);
	
	 
	 
	 SDL_Flip(screen);
	 
	 offset.x=260;
	 offset.y=400;
	 SDL_BlitSurface(bat,NULL,screen,&offset); 
	 //Ütő sebesége
	 sprintf(adat1,"%d",speed);
	 bat_speed=TTF_RenderText_Solid(f4,adat1,white);
	 SDL_FillRect(screen,&clr1,0);
	 offset.x=300;
	 offset.y=440;
	 SDL_BlitSurface(bat_speed,NULL,screen,&offset); 
	 
	 offset.x=470;
	 offset.y=400;
	 SDL_BlitSurface(ball,NULL,screen,&offset); 
	 //Labda sebessége
	 sprintf(adat2,"%d",default_ball_R);
	 ball_speed=TTF_RenderText_Solid(f4,adat2,white);
	 SDL_FillRect(screen,&clr2,0);
	 offset.x=510;
	 offset.y=440;
	 SDL_BlitSurface(ball_speed,NULL,screen,&offset);
	 
	 //Ai
	 Ai_w=TTF_RenderText_Solid(f4,"Ai",white);
	 offset.x=687;
	 offset.y=400;
	 SDL_BlitSurface(Ai_w,NULL,screen,&offset); 
	 sprintf(adat3,"%d",Ai);
	 Ai_w=TTF_RenderText_Solid(f4,adat3,white);
	 SDL_FillRect(screen,&clr3,0);
	 offset.x=690;
	 offset.y=440;
	 SDL_BlitSurface(Ai_w,NULL,screen,&offset);
	 
	 title11=TTF_RenderText_Solid(f2,"Back",white);
	 while(quit==false)
	 {
		 while(SDL_WaitEvent(&event0))
		 {
			 if(event0.type==SDL_QUIT)
			 {
				buttonSheet1=b4;
				buttonSheet2=b5;
				SDL_FreeSurface(optimizedImage);
				SDL_FreeSurface(b1);
				SDL_FreeSurface(b0);
				SDL_FreeSurface(b2);
				SDL_FreeSurface(b3);
				SDL_FreeSurface(ball);
				SDL_FreeSurface(ball_speed);
				SDL_FreeSurface(bat);
				SDL_FreeSurface(bat_speed);
				TTF_CloseFont(f1);
				TTF_CloseFont(f2);
				TTF_CloseFont(f3);
				TTF_CloseFont(f4);
				TTF_CloseFont(f5);
				TTF_Quit();
				SDL_Quit();
				exit(0);
			 }
			 
			back_Button.handle_events();
			buttonSheet1=b4;
			buttonSheet2=b5;
			back_Button.show();
			
			r_down_Button.handle_events();
			buttonSheet2=buttonSheet1=b2;
			r_down_Button.show();
			
			r_up_Button.handle_events();
			buttonSheet2=buttonSheet1=b3;
			r_up_Button.show();
			
			b_down_Button.handle_events();
			buttonSheet2=buttonSheet1=b2;
			b_down_Button.show();
			
			b_up_Button.handle_events();
			buttonSheet2=buttonSheet1=b3;
			b_up_Button.show();
			
			ai_up_Button.handle_events();
			buttonSheet2=buttonSheet1=b3;
			ai_up_Button.show();
			
			ai_down_Button.handle_events();
			buttonSheet2=buttonSheet1=b2;
			ai_down_Button.show();
			
			offset.x=90;
			offset.y=531;
			SDL_BlitSurface(title11,NULL,screen,&offset);
			
			if(ai_down_Button.get_push()==true)
			{
				ai_down_Button.set_push();
				if(Ai>1)
				{
					Ai--;
					sprintf(adat3,"%d",Ai);
					Ai_w=TTF_RenderText_Solid(f4,adat3,white);
					SDL_FillRect(screen,&clr3,0);
					offset.x=690;
					offset.y=440;
					SDL_BlitSurface(Ai_w,NULL,screen,&offset);
				}
			}
			
			if(ai_up_Button.get_push()==true)
			{
				ai_up_Button.set_push();
				if(Ai<9)
				{
					Ai++;
					sprintf(adat3,"%d",Ai);
					Ai_w=TTF_RenderText_Solid(f4,adat3,white);
					SDL_FillRect(screen,&clr3,0);
					offset.x=690;
					offset.y=440;
					SDL_BlitSurface(Ai_w,NULL,screen,&offset);
				}
			}
			
			if(b_down_Button.get_push()==true)
			{
				b_down_Button.set_push();
				if(default_ball_R>1)
				{
					default_ball_R--;
					//Labda sebessége
					sprintf(adat2,"%d",default_ball_R);
					ball_speed=TTF_RenderText_Solid(f4,adat2,white);
					SDL_FillRect(screen,&clr2,0);
					offset.x=510;
					offset.y=440;
					SDL_BlitSurface(ball_speed,NULL,screen,&offset);
				}
			}
			
			if(b_up_Button.get_push()==true)
			{
				b_up_Button.set_push();
				if(default_ball_R < 99)
				{
					default_ball_R++;
					//Labda sebessége
					sprintf(adat2,"%d",default_ball_R);
					ball_speed=TTF_RenderText_Solid(f4,adat2,white);
					SDL_FillRect(screen,&clr2,0);
					offset.x=510;
					offset.y=440;
					SDL_BlitSurface(ball_speed,NULL,screen,&offset);
				}
			}
			
			if(full_screen==false)
			{
				buttonSheet2=buttonSheet1=b0;
			}
			else
			{
				buttonSheet2=buttonSheet1=b1;
			}
			full_Button.handle_events();
			full_Button.show();
			
			if(r_down_Button.get_push()==true)
			{
				r_down_Button.set_push();
				if(speed>1)
				{
					speed--;
					//Ütő sebesége
					sprintf(adat1,"%d",speed);
					bat_speed=TTF_RenderText_Solid(f4,adat1,white);
					SDL_FillRect(screen,&clr1,0);
					offset.x=300;
					offset.y=440;
					SDL_BlitSurface(bat_speed,NULL,screen,&offset);
				}
			}
			
			if(r_up_Button.get_push()==true)
			{
				r_up_Button.set_push();
				if(speed<99)
				{
					speed++;
					//Ütő sebesége
					sprintf(adat1,"%d",speed);
					bat_speed=TTF_RenderText_Solid(f4,adat1,white);
					SDL_FillRect(screen,&clr1,0);
					offset.x=300;
					offset.y=440;
					SDL_BlitSurface(bat_speed,NULL,screen,&offset);
				}
			}
			
			if(full_Button.get_push()==true)
			{
				full_Button.set_push();
				
				if(full_screen==false)
				{
					full_screen=true;
					change=true;
					screen=SDL_SetVideoMode(800,600,32,SDL_FULLSCREEN);
					quit=true;
					break;
				}
				else if(full_screen==true)
				{
					full_screen=false;
					change=true;
					screen=SDL_SetVideoMode(800,600,32,SDL_HWSURFACE);
					quit=true;
					break;
				}
			}
			
			if(sound_Button.get_push())
			{
				sound_Button.set_push();
				if(sound==true)
					sound=false;
				else if(sound==false)
					sound=true;
			}
			
			if(sound==true)
			{
				buttonSheet2=buttonSheet1=b1;
			}
			else
			{
				buttonSheet2=buttonSheet1=b0;
			}
			sound_Button.handle_events();
			sound_Button.show();
			
			SDL_Flip(screen);
			if(back_Button.get_push()==true)
			{
				quit=true;
				break;
			} 
		 }
	 }
	buttonSheet1=b4;
	buttonSheet2=b5;
	SDL_FreeSurface(optimizedImage);
	SDL_FreeSurface(b0);
	SDL_FreeSurface(b1);
	SDL_FreeSurface(b2);
	SDL_FreeSurface(b3);
	SDL_FreeSurface(ball);
	SDL_FreeSurface(Ai_w);
	SDL_FreeSurface(ball_speed);
    SDL_FreeSurface(bat);
	SDL_FreeSurface(bat_speed);
	TTF_CloseFont(f1);
	TTF_CloseFont(f2);
	TTF_CloseFont(f3);
	TTF_CloseFont(f4);
	TTF_CloseFont(f5);
	return;
}
