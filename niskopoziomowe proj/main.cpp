#include "Allegro.h"
#include "Multiplayer.h"
#include <allegro.h>
#include<cmath>
#include <cstdlib>
#include <string>
#include <iostream>


inline void init();
void init2();
inline void deinit();
int mx = 0, my = 0, mb = 0;
BITMAP* SP=NULL,* MP=NULL,* LSP=NULL, * LMP=NULL, * Ex=NULL, * Tytan=NULL;

int main(int argc, char *argv[])
{
	init();
    init2();
    myszka();
    while (mb!=1 || mx>550 || mx<240 || my>550 || my<500)
	{
        myszka();
        if(mb==1 && mx<550 && mx>240 && my<150 && my>100){
            SinglePlayer(0);
            init2();
        }
        if(mb==1 && mx<550 && mx>240 && my<250 && my>200){
                Multiplayer(0);
                init2();
        }
        if(mb==1 && mx<550 && mx>240 && my<350 && my>300){
            DialogSingle();
            init2();
        }
        if(mb==1 && mx<550 && mx>240 && my<450 && my>400){
                DialogMulti();
                init2();
        }

	}
	deinit();
    return 0;
}
END_OF_MAIN()



inline void init()
{
	allegro_init();
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    set_palette( default_palette );
	install_keyboard();
	install_mouse();
	install_timer();
    SP = load_bmp ("bitmapy/SinglePlayer.bmp", default_palette);
    if( !SP )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ Single!" );
    allegro_exit();
    }
    MP = load_bmp ("bitmapy/MultiPlayer.bmp", default_palette);
    if( !SP )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ Multi!" );
    allegro_exit();
    }
    LSP = load_bmp ("bitmapy/LoadSinglePlayer.bmp", default_palette);
    if( !SP )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ LoadSingle!" );
    allegro_exit();
    }
    LMP = load_bmp ("bitmapy/LoadMultiPlayer.bmp", default_palette);
    if( !LMP )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ LoadMulti!" );
    allegro_exit();
    }
    Ex = load_bmp ("bitmapy/Exit.bmp", default_palette);
    if( !LMP )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ Exit!" );
    allegro_exit();
    }
    Tytan = load_bmp ("bitmapy/TYTAN!.bmp", default_palette);
    if( !Tytan )
    {
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ Tytan!" );
    allegro_exit();
    }
}
void init2(){
clear_to_color( screen, makecol( 0, 128, 0 ) );
show_mouse(screen);
    blit( Tytan, screen, 0, 0, 100, 0, Tytan->w, Tytan->h );
    blit( SP, screen, 0, 0, 240, 100, SP->w, SP->h );
    blit( MP, screen, 0, 0, 240, 200, MP->w, MP->h );
    blit( LSP, screen, 0, 0, 240, 300, LSP->w, LSP->h );
    blit( LMP, screen, 0, 0, 240, 400, LMP->w, LMP->h );
    blit( Ex, screen, 0, 0, 240, 500, Ex->w, Ex->h );
}

inline void deinit()
{
    destroy_bitmap(Tytan);
    destroy_bitmap(SP);
    destroy_bitmap(MP);
    destroy_bitmap(LSP);
    destroy_bitmap(LMP);
    destroy_bitmap(Ex);
	clear_keybuf();
	allegro_exit();
}

