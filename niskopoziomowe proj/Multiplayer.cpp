#include "Multiplayer.h"
#include <time.h>
#include<cstdlib>


int frame = -1000, tabZapis[33];;
const int epsilon=18;
int xtab[33], ytab[33], bialeZbite=0, czarneZbite=0;
sem_t sem_rest;
BITMAP * plansza = NULL,*planszamini=NULL, * bufor = NULL,* Gracz=NULL, * White=NULL, * Black=NULL;

volatile int ticks = 0;
const int updates_per_second = 60;
extern int mx, my, mb;
int wybr=0;
Kto tab[33],PoprzedniStanPlanszy[33];
bool CzyPierw=true, CzyKol=false, CzyZmian=false, CzyWybr=false,SaKolRuch=false, CzyKon, ruchy[33], ruchyConst[33], ZaNieBicie=false, Czykomputer=false, CzySingle=false, wcisniete=false;
extern short int zbij[33], zbijConst[33];
const int xp=700, xk=790, y1p=200, y1k=250, y2p=300, y2k=350;
extern wezel* korzen;


int Multiplayer(int pocz)
{
    initM();
    if(pocz==0)initBez();
	if(pocz>0)initZ(pocz);
	//textout_ex(bufor, font, "Hello World!", 0, 0, makecol(255, 255, 255), 0);
	while (!key[KEY_ESC])
	{
	    sem_wait(&sem_rest);
	    myszka();
        while(ticks > 0)
		{
		    if(CzyPierw==true && CzyWybr==false){
             for(int i=0; i<33; i++)
             switch (tab[i]){
                 case Nic:tabZapis[i]=0;
                        break;
                 case Bialy:tabZapis[i]=1;
                        break;
                 case Czarny:tabZapis[i]=2;
                        break;
                 case BialyD:tabZapis[i]=3;
                        break;
                 case CzarnyD:tabZapis[i]=4;
                        break;
             }
            }
            if(mx>xp && mx<xk && my>y1p && my<y1k && mb==1)Zapisz(tabZapis, bialeZbite, czarneZbite, 1);
		    if(mx>xp && mx<xk && my>y2p && my<y2k && mb==1)Zapisz(tabZapis, bialeZbite, czarneZbite, 2);
		    if(mb==2 && CzyPierw==1)Anuluj();
		    if(CzyWybr==0)WybranyPion();
		    if(CzyKol==1)KolejnyRuch();
		    if(CzyPierw==1 && CzyWybr==1)PierwszyRuch();
		    if(frame>100)ZakonczAnim();
		    if(CzyZmian==1)ZmienZaw();
		    Wyswietl();
			int old_ticks = ticks;
			ticks--;
			if(old_ticks <= ticks)
				break;
            if(frame>-1)frame++;
		}
		if(bialeZbite==12 || czarneZbite==12)break;
	}
	clear_to_color( screen, makecol( 51, 128, 0 ) );
	if(czarneZbite==12){
	textout_ex(screen, font, "Bialy Wygrywa!", 0, 0, makecol(255, 255, 255), 0);
	_sleep(5000);
	}
	if(bialeZbite==12){
	textout_ex(screen, font, "Czarny Wygrywa!", 0, 0, makecol(255, 255, 255), 0);
    _sleep(5000);
	}
	deinitM();
	return 0;
}

void PrzepiszTab(Kto* tablica){
 for(int i=0; i<33; i++){
        tab[i]=tablica[i];
 }
}

void KopiujDoPoprzedni(){
for(int i=0; i<33; i++)
    PoprzedniStanPlanszy[i]=tab[i];
}

int SinglePlayer(int pocz)
{
    initM();
    if(pocz==0)initBezS();
    if(pocz>0)initZ(pocz);
	while (!key[KEY_ESC])
	{
	    sem_wait(&sem_rest);
	    myszka();
        while(ticks > 0)
		{
		    if(Czykomputer==false){
		    if(CzyPierw==true && CzyWybr==false){
             for(int i=0; i<33; i++)
             switch (tab[i]){
                 case Nic:tabZapis[i]=0;
                        break;
                 case Bialy:tabZapis[i]=1;
                        break;
                 case Czarny:tabZapis[i]=2;
                        break;
                 case BialyD:tabZapis[i]=3;
                        break;
                 case CzarnyD:tabZapis[i]=4;
                        break;
             }
            }
            if(mx>xp && mx<xk && my>y1p && my<y1k && mb==1)Zapisz(tabZapis, bialeZbite, czarneZbite, 10);
		    if(mx>xp && mx<xk && my>y2p && my<y2k && mb==1)Zapisz(tabZapis, bialeZbite, czarneZbite, 11);
		    if(mb==2 && CzyPierw==1)Anuluj();
		    if(CzyWybr==0)WybranyPion();
		    if(CzyKol==1)KolejnyRuch();
		    if(CzyPierw==1 && CzyWybr==1)PierwszyRuch();
		    if(frame>100)ZakonczAnim();
		    if(CzyZmian==1){ZmienZawS();if(tab[0]==Bialy)tab[0]=Czarny;
            else tab[0]=Bialy;}
		    Wyswietl();
			int old_ticks = ticks;
			ticks--;
			if(old_ticks <= ticks)
				break;
            if(frame>-1)frame++;
		}
		else{
        Wyswietl();
        KopiujDoPoprzedni();
        PrzepiszTab(RuchKomputer(tab));
        CzyscDrzewo(korzen);
        LiczZbite();
        ZmienZawS();
        wcisniete=true;

		}
		}
		if(bialeZbite==12 || czarneZbite==12)break;
	}
	clear_to_color( screen, makecol( 51, 128, 0 ) );
	if(czarneZbite==12){
	textout_ex(screen, font, "You win!", 0, 0, makecol(255, 255, 255), 0);
	_sleep(5000);
	}
	if(bialeZbite==12){
	textout_ex(screen, font, "You lose!", 0, 0, makecol(255, 255, 255), 0);
    _sleep(5000);
	}
	deinitM();
	return 0;
}

void LiczZbite(){
 bialeZbite=0;
 czarneZbite=0;
 for(int i=1; i<33; i++)
        if(tab[i]==Bialy || tab[i]==BialyD)bialeZbite++;
        else if(tab[i]==Czarny || tab[i]==CzarnyD)czarneZbite++;
 bialeZbite=12-bialeZbite;
 czarneZbite=12-czarneZbite;
}

inline void initM()
{
    clear_to_color( screen, makecol( 128, 128, 128 ) );
	install_timer();
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));
	CreateBit();
	show_mouse( bufor );
	GenXY();
}

void initBez()
{
 CzySingle=false;
 GenStanPocz();
 KopiujDoPoprzedni();
 bialeZbite=0;
 czarneZbite=0;
}

void initBezS()
{
 CzySingle=true;
 Czykomputer=false;
 GenStanPocz();
 KopiujDoPoprzedni();
 bialeZbite=0;
 czarneZbite=0;
}

void initZ(int Z)
{
int* tablica=new int [35];
tablica=Wczytaj(Z);
for(int i=0; i<33; i++)
switch (tablica[i]){
 case 0: tab[i]=Nic;
        break;
 case 1: tab[i]=Bialy;
        break;
 case 2: tab[i]=Czarny;
        break;
 case 3: tab[i]=BialyD;
        break;
 case 4: tab[i]=CzarnyD;
        break;
}
bialeZbite=tablica[33];
czarneZbite=tablica[34];
delete(tablica);
}

inline void deinitM()
{

    DelPom();
	show_mouse(screen);
    destroy_bitmap( bufor );
    destroy_bitmap( plansza );
    destroy_bitmap(planszamini);
    destroy_bitmap(Gracz);
}

int CreateBit(){
plansza = load_bmp ("bitmapy/board.bmp", default_palette);
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

planszamini=load_bmp ("bitmapy/boardmini.bmp", default_palette);
if( !planszamini )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ obrazka ZaNie!" );
    allegro_exit();
    return 0;
}

Gracz=load_bmp ("bitmapy/Gracz.bmp", default_palette);
if( !Gracz )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ obrazka Gracz!" );
    allegro_exit();
    return 0;
}


return 1;
}
void ticker()
{
	sem_post(&sem_rest);//unlock the semaphore, and allow the game loop to continue
	ticks++;
}
END_OF_FUNCTION(ticker)
END_OF_FUNCTION(ticker)

void Wyswietl(){
    clear_to_color( bufor, makecol( 0, 128, 0 ) );
    blit( plansza, bufor, 0, 0, 248, 148, plansza->w, plansza->h );
    if(CzySingle==true)blit( planszamini, bufor, 0, 0, 99, 59, planszamini->w, planszamini->h);
    blit( Gracz, bufor, 0, 0, 325, 0, Gracz->w, Gracz->h);
    if(tab[0]==Czarny)rectfill( bufor, 375, 50, 425, 100, makecol( 0, 0, 0 ) );
    else rectfill( bufor, 375, 50, 425, 100, makecol( 250, 250, 250 ) );
    for(int i=1; i<34; i++){
        switch (tab[i]){
                case Czarny:circlefill( bufor, xtab[i], ytab[i], 10, makecol( 0, 0, 0 ) );
                     break;
                case Bialy: circlefill( bufor, xtab[i], ytab[i], 10, makecol( 255, 255, 255 ) );
                     break;
                case BialyD: circlefill( bufor, xtab[i], ytab[i], 10, makecol( 255, 255, 255 ) );
                     circlefill( bufor, xtab[i], ytab[i], 5, makecol( 0, 0, 0 ) );
                     break;
                case CzarnyD: circlefill( bufor, xtab[i], ytab[i], 10, makecol( 0, 0, 0 ) );
                     circlefill( bufor, xtab[i], ytab[i], 5, makecol( 255, 255, 255 ) );
                            }
        if(CzySingle==true)switch (PoprzedniStanPlanszy[i]){
                case Czarny:circlefill( bufor, 2*xtab[i]/5, 2*ytab[i]/5, 4, makecol( 0, 0, 0 ) );
                     break;
                case Bialy: circlefill( bufor, 2*xtab[i]/5, 2*ytab[i]/5, 4, makecol( 255, 255, 255 ) );
                     break;
                case BialyD: circlefill( bufor, 2*xtab[i]/5, 2*ytab[i]/5, 4, makecol( 255, 255, 255 ) );
                     circlefill( bufor, 2*xtab[i]/5, 2*ytab[i]/5, 2, makecol( 0, 0, 0 ) );
                     break;
                case CzarnyD: circlefill( bufor, 2*xtab[i]/5, 2*ytab[i]/5, 4, makecol( 0, 0, 0 ) );
                     circlefill( bufor, 2*xtab[i]/5, 2*ytab[i]/5, 2, makecol( 255, 255, 255 ) );
                            }
        if(CzyWybr==true && ruchy[i]!=0)circlefill( bufor, xtab[i], ytab[i], 10, makecol( 0, 255, 0 ) );
    }
    for(int i=1; i<=bialeZbite; i++)
        circlefill( bufor, 234, 148+i*25, 10, makecol( 255, 255, 255 ) );
    for(int i=1; i<=czarneZbite; i++)
        circlefill( bufor, 566, 148+i*25, 10, makecol( 0, 0, 0 ) );
    rectfill( bufor, xp, y1p, xk, y1k, makecol( 128, 30, 30 ) );
    textout_ex(bufor, font, "Save 1", xp+10, y1k-50, makecol(254, 223, 131), 0);
    rectfill( bufor, xp, y2p, xk, y2k, makecol( 128, 30, 30 ) );
    textout_ex(bufor, font, "Save 2", xp+10, y2k-50, makecol(254, 223, 131), 0);
    if(wybr!=0)circlefill( bufor, xtab[wybr], ytab[wybr], 1, makecol( 255, 0, 0 ) );
    if(frame>0){
            textout_ex(bufor, font, "Za nie bicie tracisz zycie!", 340, 50, makecol(0, 0, 255), 0);

    }
    show_mouse( bufor );
    blit( bufor, screen, 0, 0, 0, 0, 800, 600 );
}
void myszka()
{
    if( mx != mouse_x || my != mouse_y || mb != mouse_b )
    {
        mx = mouse_x;
        my = mouse_y;
        mb = mouse_b;
    }
}

void WybranyPion(){
  SaKolRuch=false;
  if(wcisniete==false){
  for(int i=1; i<33; i++){
  if((tab[i]==tab[0] || tab[i]==tab[0]+2) && labs(mx-xtab[i])<epsilon && labs(my-ytab[i])<epsilon && mb==1){
   CzyKon=false;
   wybr=i;
   if(tab[wybr]!=BialyD && tab[wybr]!=CzarnyD)
   ZbadajRuchy(wybr);
   else
    ZbadajRuchyDam(wybr);
    bool CzySaRuchy=false;
    for(int i=1; i<33; i++)
        if(ruchy[i]==true){
        CzySaRuchy=true;
        break;
        }
    if(CzySaRuchy==true)
    CzyWybr=true;
    else{
    CzyZmian=false;
    }
   break;
  }
 }
}
else if(mb==0)wcisniete=false;

}

void PierwszyRuch(){
    for(int i=1; i<33; i++){
        if(ruchy[i]==true && labs(mx-xtab[i])<epsilon && labs(my-ytab[i])<epsilon && mb==1){
            wybr=WykonajRuch(wybr, i);
            ZbadajRuchy(wybr);
            CzyPierw=0;
            CzyKol=1;
        }
    }
}

void KolejnyRuch(){
for(int i=1; i<33; i++){
            if(ruchy[i]==true && labs(mx-xtab[i])<epsilon && labs(my-ytab[i])<epsilon && mb==1){
                wybr=WykonajRuch(wybr, i);
                ZbadajRuchy(wybr);
            }

        }
}

void ZmienZaw(){
 KopiujDoPoprzedni();
 CzyPierw=1;
 CzyWybr=0;
 wybr=0;
 CzyKol=0;
 CzyZmian=0;
 if(tab[0]==Bialy)tab[0]=Czarny;
 else tab[0]=Bialy;
}

void ZmienZawS(){
 CzyPierw=1;
 CzyWybr=0;
 wybr=0;
 CzyKol=0;
 CzyZmian=0;
 if(Czykomputer==true)Czykomputer=false;
 else Czykomputer=true;
}
void ZakonczAnim(){
  ZaNieBicie=false;
  frame=-1000;
}
void Anuluj(){
 CzyPierw=true;
 CzyWybr=0;
 wybr=0;
}

