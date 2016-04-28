#include <allegro.h>
int main()
{
    allegro_init();
    install_keyboard();
    set_color_depth( 32 );
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
    clear_to_color( screen, makecol( 128, 128, 128 ) );
    BITMAP * ludek = NULL;
    ludek = load_bmp( "Ok.bmp", default_palette );
if( !ludek )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "nie mogê za³adowaæ obrazka Ludek !" );
    allegro_exit();
    return 0;
}

    blit( ludek, screen, 0, 0, 100, 100, ludek->w, ludek->h );
readkey();
destroy_bitmap( ludek );
allegro_exit();
return 0;
}
END_OF_MAIN();
