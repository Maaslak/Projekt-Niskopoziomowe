#include "ZapisOdczyt.h"
extern int mx, my, mb;
BITMAP* Franek=NULL;

using namespace std;

void Zapisz(int tab[], int biale, int czarne, int ktory){
fstream plik;
switch (ktory){
    case 1:plik.open("zapisy/Zapis1.txt", std::ios::out);
            break;
    case 2:plik.open("zapisy/Zapis2.txt", std::ios::out);
            break;
    case 10:plik.open("zapisy/Zapis1S.txt", std::ios::out);
            break;
    case 11:plik.open("zapisy/Zapis2S.txt", std::ios::out);
            break;
}
for(int i=0; i<33; i++)
    plik<<tab[i]<<" ";
plik<<biale<<" "<<czarne;
plik.close();
}

int *Wczytaj(int ktory)
{
int tab[35];
fstream plik;
switch (ktory){
    case 1:plik.open("zapisy/Zapis1.txt", std::ios::in);
            break;
    case 2:plik.open("zapisy/Zapis2.txt", std::ios::in);
            break;
    case 10:plik.open("zapisy/Zapis1S.txt", std::ios::in);
            break;
    case 11:plik.open("zapisy/Zapis2S.txt", std::ios::in);
            break;
}
for(int i=0; i<35; i++)
plik>>tab[i];
plik.close();
return tab;
}

int *Wczytaj2()
{
int tab[35];
fstream plik;
plik.open("zapisy/Zapis2.txt", std::ios::in);
for(int i=0; i<35; i++)
plik>>tab[i];
plik.close();
return tab;
}

int *Wczytaj1S(){
int tab[35];
fstream plik;
plik.open("zapisy/Zapis1S.txt", std::ios::in);
for(int i=0; i<35; i++)
plik>>tab[i];
plik.close();
return tab;
}

int *Wczytaj2S()
{
int tab[35];
fstream plik;
plik.open("zapisy/Zapis2S.txt", std::ios::in);
for(int i=0; i<35; i++)
plik>>tab[i];
plik.close();
return tab;
}

void DialogMulti()
{

    clear_to_color( screen, makecol( 128, 128, 128 ) );
    for(int i=1; i<3; i++)
        rectfill( screen, 30, i*100, 200, i*100+50, makecol( 128, 30, 30 ) );
    rectfill( screen, 30, 5*100, 200, 5*100+50, makecol( 128, 30, 30 ) );
    textout_ex(screen, font, "Load 1", 30, 114, makecol(254, 223, 131), 0);
    textout_ex(screen, font, "Load 2", 30, 214, makecol(254, 223, 131), 0);
    textout_ex(screen, font, "Exit", 30, 514, makecol(254, 223, 131), 0);
     Franek = load_bmp ("bitmapy/Franek.bmp", default_palette);
    if( !Franek )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ Franek!" );
    allegro_exit();
    }
    blit( Franek, screen, 0, 0, 100, 275, Franek->w, Franek->h );
    myszka();
while (mb!=1 || mx>300 || mx<30 || my>550 || my<500){
myszka();
if(mb==1 && mx<200 && mx>30 && my<150 && my>100){
 Multiplayer(1);
 break;
}
if(mb==1 && mx<200 && mx>30 && my<250 && my>200){
 Multiplayer(2);
 break;
}

}
delete(Franek);
}

void DialogSingle()
{
    clear_to_color( screen, makecol( 128, 128, 128 ) );
    for(int i=1; i<3; i++)
        rectfill( screen, 30, i*100, 200, i*100+50, makecol( 128, 30, 30 ) );
    rectfill( screen, 30, 5*100, 200, 5*100+50, makecol( 128, 30, 30 ) );
    textout_ex(screen, font, "Load 1", 30, 114, makecol(254, 223, 131), 0);
    textout_ex(screen, font, "Load 2", 30, 214, makecol(254, 223, 131), 0);
    textout_ex(screen, font, "Exit", 30, 514, makecol(254, 223, 131), 0);
    Franek = load_bmp ("bitmapy/Franek.bmp", default_palette);
    if( !Franek )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ Franek!" );
    allegro_exit();
    }
    blit( Franek, screen, 0, 0, 100, 275, Franek->w, Franek->h );
    myszka();
while (mb!=1 || mx>300 || mx<30 || my>550 || my<500){
myszka();
if(mb==1 && mx<200 && mx>30 && my<150 && my>100){
 SinglePlayer(10);
 break;
}
if(mb==1 && mx<200 && mx>30 && my<250 && my>200){
 SinglePlayer(11);
 break;
}

}
}
