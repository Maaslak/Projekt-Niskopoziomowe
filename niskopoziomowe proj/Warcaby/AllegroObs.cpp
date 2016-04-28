#include "AllegroObs.h"
#include "Rozgrywka.h"

void laduj_kursor()
{
    kursor = load_bitmap( "cursor.bmp", NULL );
    if( !kursor )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Nie moge zaladowac grafiki ( kursor )" );
        allegro_exit();
    }
};

void ticker()
{
	sem_post(&sem_rest);//unlock the semaphore, and allow the game loop to continue
	ticks++;
}
END_OF_FUNCTION(ticker)


inline void init()
{
	allegro_init();
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    set_palette( default_palette );
    clear_to_color( screen, makecol( 128, 128, 128 ) );
	install_timer();
	install_keyboard();
	install_mouse();
	//laduj_kursor();
	//set_mouse_sprite( kursor );
	//select_mouse_cursor(MOUSE_CURSOR_ALLEGRO );
	//unscare_mouse();
	install_timer();
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));
	int k=1;
	for(int j=168; j<472; j+=38){ //Interpretacja tab na planszy
        for(int i=267; i<571; i+=76){
                if(i==267 || i==305){
                        if((j/38)%2==1)i=305;
                        else i=267;

                }
                xtab[k]=i;
                ytab[k]=j;
                k++;
                }
        }
        CreateBit();
        tab=GenStanPocz();
        WyswietlStanGry(tab);
        show_mouse( bufor );
}


void myszka()
{
    if( mx != mouse_x || my != mouse_y || mb != mouse_b )
    {
        mx = mouse_x;
        my = mouse_y;
        mb = mouse_b;
    }
};

void WlaczGre(){
    init();
	while (mb!=2)
	{
	    sem_wait(&sem_rest);
        myszka();
        bool CzyPionek=Ruch();
        while(ticks > 0)
		{
			int old_ticks = ticks;
            WyswietlStanGry(tab);
			ticks--;
			if(old_ticks <= ticks)
				break;
		}

	}

	deinit();
}ticker

bool Ruch(){
 sem_wait(&sem_rest);
 Kto Ktory;
if(CzyPionek==false){
 int i;
 for(i=1; i<33; i++){
  if(tab[i]==Bialy && labs(mx-xtab[i])<epsilon && labs(my-ytab[i])<epsilon && mb==1){
   Ktory=Bialy;
   //tab[i]=Nic;
   CzyPionek=true;
   k=i;
   //WyswietlStanGry(tab);
  }
  if(CzyPionek==true)break;
 }
}
else{

}
}



void WyswietlStanGry(Kto tab[]){
    clear_to_color( bufor, makecol( 128, 128, 128 ) );
    blit( plansza, bufor, 0, 0, 248, 148, plansza->w, plansza->h );
    textout_ex(bufor, font, "Warcaby fchuuuuuuj!", 340, 50, makecol(0, 0, 255), 0);
    for(int i=1; i<34; i++)
        switch (tab[i]){
                case Czarny:circlefill( bufor, xtab[i], ytab[i], 10, makecol( 0, 0, 0 ) );
                     break;
                case Bialy: circlefill( bufor, xtab[i], ytab[i], 10, makecol( 255, 255, 255 ) );
                     break;
                            }
    if(CzyPionek==true){
        Wybor();
    }

    show_mouse( bufor );
    blit( bufor, screen, 0, 0, 0, 0, 800, 600 );
}

/*
if(((k-1)/4)%2==0){
        if(k-4>0 && k-4<33 && tab[k-4]==Nic)
       circlefill( bufor, xtab[k-4], ytab[k-4], 10, makecol( 0, 255, 0 ) );
        if(k-5>0 && k-5<33 && tab[k-5]==Nic && k%4!=1)
       circlefill( bufor, xtab[k-5], ytab[k-5], 10, makecol( 0, 255, 0 ) );
        }
    else{
        if(k-3>0 && k-3<33 && tab[k-3]==Nic && k%4!=0)
       circlefill( bufor, xtab[k-3], ytab[k-3], 10, makecol( 0, 255, 0 ) );
        if(k-4>0 && k-4<33 && tab[k-4]==Nic)
       circlefill( bufor, xtab[k-4], ytab[k-4], 10, makecol( 0, 255, 0 ) );
       */

void Wybor(){
     bool czy=false;
     ZbadajRuchy();
     for(int i=1; i<33; i++){
        if(ruchy[i]==true){
        circlefill( bufor, xtab[i], ytab[i], 10, makecol( 0, 255, 0 ) );
        czy=true;
        }
     if(ruchy[i]==true && labs(mx-xtab[i])<epsilon && labs(my-ytab[i])<epsilon && mb==1){
     tab[k]=Nic;
     tab[i]=tab[0];
     if(labs((k+1)/4-((i+1)/4))==2 && ((k+1)/4)%2==1){
        tab[((k+i)/2)+1]=Nic; //if(labs(k-i)==7 || labs(k-i)==9)
     }
     if(labs((k+1)/4-((i+1)/4))==2 && ((k+1)/4)%2==0){
        tab[(k+i)/2]=Nic; //if(labs(k-i)==7 || labs(k-i)==9)
     }
     CzyPionek=false;
     if(czy==false){
     if(tab[0]==Czarny)tab[0]=Bialy;
     else tab[0]=Czarny;
     }
     }
}
}

int CreateBit(){
plansza = load_bmp ("board.bmp", default_palette);
if( !plansza )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ obrazka 1 !" );
    allegro_exit();
    return 0;
}

bufor = create_bitmap( 800, 600 );
if( !bufor )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie mogę utworzyć bufora !" );
    allegro_exit();
    return 0;
}
return 1;
}

inline void deinit(){
    show_mouse(screen);
    destroy_bitmap( kursor );
    destroy_bitmap( bufor );
    destroy_bitmap( plansza );
	clear_keybuf();
	allegro_exit();
	delete(tab);
	delete(ruchy);
}

void ZbadajRuchy(){
    ruchy=new bool[33];
    for(int i=0; i<33; i++){
        ruchy[i]=false;
    }
    if(((k-1)/4)%2==0){
        if(k-4>0 && k-4<33 && tab[k-4]==Nic)
            ruchy[k-4]=true;
        else
            if(k-7>0 && k-7<33 && tab[k-4]==Czarny && tab[k-7]==Nic  && k%4!=0)
                ruchy[k-7]=true;
        if(k-5>0 && k-5<33 && tab[k-5]==Nic && k%4!=1)
        ruchy[k-5]=true;
        else
            if(k-9>0 && k-9<33 && tab[k-5]==Czarny && tab[k-9]==Nic  && k%4!=1)
                ruchy[k-9]=true;
        }
    else{
        if(k-3>0 && k-3<33 && tab[k-3]==Nic && k%4!=0)
        ruchy[k-3]=true;
        else
            if(k-7>0 && k-7<33 && tab[k-3]==Czarny && tab[k-7]==Nic  && k%4!=0)
                ruchy[k-7]=true;
        if(k-4>0 && k-4<33 && tab[k-4]==Nic)
        ruchy[k-4]=true;
        if(k-9>0 && k-9<33 && tab[k-4]==Czarny && tab[k-9]==Nic && k%4!=1)
                ruchy[k-9]=true;

}
}

