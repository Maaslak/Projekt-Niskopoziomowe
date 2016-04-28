#include "Rozgrywka.h"
Kto* GenStanPocz()
{
Kto* tab;
tab=new Kto[33];
tab[0]=Bialy;
for(int i=1; i<5; i++){
 tab[i]=tab[i+8]=Czarny;
 tab[i+20]=tab[i+24]=tab[i+28]=Bialy;
 tab[18]=tab[19]=Czarny;
}
return tab;
}



/*
std::vector <int> ZbadajRuchy(){

    std::vector <int> ruchy;
    if(((k-1)/4)%2==0){
        if(k-4>0 && k-4<33 && tab[k-4]==Nic){
        ruchy.push_back(k-4);
        allegro_message( "Ok" );
        }
        if(k-5>0 && k-5<33 && tab[k-5]==Nic && k%4!=1){
        ruchy.push_back(k-5);
         allegro_message( "Ok" );
        }
        }
    else{
        if(k-3>0 && k-3<33 && tab[k-3]==Nic && k%4!=0){
        ruchy.push_back(k-3);
         allegro_message( "Ok" );
        }
        if(k-4>0 && k-4<33 && tab[k-4]==Nic){
        ruchy.push_back(k-4);
         allegro_message( "Ok" );
        }
}
return ruchy;
}

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
