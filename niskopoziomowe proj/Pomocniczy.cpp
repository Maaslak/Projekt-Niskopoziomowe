#include "Pomocniczy.h"
#include <cstdio>
#include <allegro.h>
#include<cmath>
//Za nie bicie tracisz zycie nie lubie!!!!!


void GenStanPocz(){
tab[0]=Bialy;
for(int i=1; i<34; i++)
    tab[i]=Nic;
for(int i=1; i<5; i++){
 tab[i]=tab[i+4]=tab[i+8]=Czarny;
 tab[i+20]=tab[i+24]=tab[i+28]=Bialy;
}
}
void GenXY(){
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
}

int WykonajRuch(int k, int i){
    bool CzyZbite=false;
    ZaNieBicie=false;
    if(zbij[i]!=0){
    tab[zbij[i]]=Nic;
    CzyZbite=true;
    if(tab[0]!=Bialy)bialeZbite++;
    else czarneZbite++;
    }
    if(CzyZbite==false) {
    CzyZaNieBicie();
    CzyKon=true;
    }
    else SaKolRuch=true;
    tab[i]=tab[k];
    tab[k]=Nic;
    if(ZaNieBicie==true){frame=0;}
    if(tab[0]==Czarny && ((i-1)/4)==7){tab[i]=CzarnyD;CzyZmian=true;}
    if(tab[0]==Bialy && ((i-1)/4==0)){tab[i]=BialyD;CzyZmian=true;}
    WyczRuchy();
    return i;
}

void WyczRuchy(){
 for(int i=0; i<34; i++){
  ruchy[i]=false;
 }
}

void ZbadajRuchy(int k){
    bool czy=false;
    for(int i=0; i<33; i++)
        zbij[i]=0;
    Kto temp;
    if(tab[0]==Bialy)temp=Czarny;
    else temp=Bialy;
    for(int i=0; i<34; i++){
        ruchy[i]=false;
    }
    if(CzyKon==false){
    if(((k-1)/4)%2==0){
        if(k+3<33 && tab[k+3]==Nic && SaKolRuch==0 && tab[0]==Czarny && k%4!=1)
            ruchy[k+3]=true;
        else
        if(k+7<33 && tab[k+7]==Nic && (tab[k+3]==temp || tab[k+3]==temp+2) && k%4!=1)
                {ruchy[k+7]=true;zbij[k+7]=k+3;zbij[0]++;}
        if(k+4<33 && tab[k+4]==Nic && SaKolRuch==0 && tab[0]==Czarny)
            ruchy[k+4]=true;
        else
        if(k+9<33 && tab[k+9]==Nic && (tab[k+4]==temp || tab[k+4]==temp+2) && k%4!=0)
                {ruchy[k+9]=true;zbij[k+9]=k+4;zbij[0]++;}
        if(k-4>0 && tab[k-4]==Nic && SaKolRuch==0 && tab[0]==Bialy)
            ruchy[k-4]=true;
        else
            if(k-7>0 && (tab[k-4]==temp || tab[k-4]==temp+2) && tab[k-7]==Nic  && k%4!=0)
                {ruchy[k-7]=true;zbij[k-7]=k-4;zbij[0]++;}
        if(k-5>0 && tab[k-5]==Nic && k%4!=1 && SaKolRuch==0 && tab[0]==Bialy && k%4!=1)
        ruchy[k-5]=true;
        else
            if(k-9>0 && (tab[k-5]==temp || tab[k-5]==temp+2) && tab[k-9]==Nic  && k%4!=1)
                {ruchy[k-9]=true;zbij[k-9]=k-5;zbij[0]++;}
        }
    else{
        if(k+4<33 && tab[k+4]==Nic && SaKolRuch==0 && tab[0]==Czarny)
            ruchy[k+4]=true;
        else
        if(k+7<33 && tab[k+7]==Nic && (tab[k+4]==temp || tab[k+4]==temp+2)&& k%4!=1)
                {ruchy[k+7]=true;zbij[k+7]=k+4;zbij[0]++;}
        if(k+5<33 && tab[k+5]==Nic && SaKolRuch==0 && tab[0]==Czarny && k%4!=0)
            ruchy[k+5]=true;
        else
        if(k+9<33 && tab[k+9]==Nic && (tab[k+5]==temp || tab[k+5]==temp+2) && k%4!=0)
                {ruchy[k+9]=true;zbij[k+9]=k+5;zbij[0]++;}
        if(k-3>0 && tab[k-3]==Nic && k%4!=0 && SaKolRuch==0 && tab[0]==Bialy && k%4!=0)
        ruchy[k-3]=true;
        else
            if(k-7>0 && (tab[k-3]==temp || tab[k-3]==temp+2)&& tab[k-7]==Nic && k%4!=0)
                {ruchy[k-7]=true;zbij[k-7]=k-3;zbij[0]++;}
        if(k-4>0 && tab[k-4]==Nic && SaKolRuch==0 && tab[0]==Bialy)
        ruchy[k-4]=true;
        else
        if(k-9>0 && (tab[k-4]==temp || tab[k-4]==temp+2) && tab[k-9]==Nic && k%4!=1)
                {ruchy[k-9]=true;zbij[k-9]=k-4;zbij[0]++;}
    }
    }
    for(int i=1; i<34; i++)
        if(ruchy[i]==true){
         czy=true;
         break;
        }
        if(czy==false){  //Nie ma ju¿ ruchów!!!
         CzyZmian=true;
         //CzyKon=true;
        }

}


void ZbadajRuchyDam(int k){
    int pion=0;
    Kto temp;
    if(tab[0]==Bialy)temp=Czarny;
    else temp=Bialy;
    bool czy=false;
    for(int i=0; i<34; i++){
        ruchy[i]=false;
        zbij[i]=0;
    }
    if(CzyKon==false){
    if(((k-1)/4)%2==0){
     int i, ilemin=0;
     if(k%4!=1){
     for(i=k-5;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
     pion=0;
     }
     for(i=k-4;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }
     pion=0;
     if(k%4!=1){
     for(i=k+3;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }
     }
    pion= 0;
     for(i=k+4;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }
     }

    else{
          int i;
     pion=0;
     for(i=k-4;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
        pion=0;
        if(k%4!=0){
     for(i=k-3;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }

        }
     pion=0;
     for(i=k+4;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }

     pion=0;
     if(k%4!=0){
     for(i=k+5;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }

     }
    }
    }
 for(int i=1; i<34; i++)
        if(ruchy[i]==true){
         czy=true;
         SaKolRuch=true;
         break;
        }
        if(SaKolRuch==false){  //Nie ma ju¿ ruchów!!!
         CzyZmian=true;
        }

}

void CzyZaNieBicie(){
 for(int i=1; i<33; i++){
    zbijtemp=0;
    if(tab[i]==tab[0])CzyZaNiePion(i);
    if(tab[i]==tab[0]+2)CzyZaNieDam(i);
    if(zbijtemp==true){
            tab[i]=Nic;
            ZaNieBicie=true;
            if(tab[0]==Bialy)bialeZbite++;
            else czarneZbite++;
            break;
    }
 }
}

void CzyZaNiePion(int k){
Kto temp;
if(tab[0]==Bialy)temp=Czarny;
else temp=Bialy;
if(((k-1)/4)%2==0)
    if((k+7<33 && tab[k+7]==Nic && (tab[k+3]==temp || tab[k+3]==temp+2) && k%4!=1) || (k+9<33 && tab[k+9]==Nic && (tab[k+4]==temp || tab[k+4]==temp+2) && k%4!=0) || (k-7>0 && (tab[k-4]==temp || tab[k-4]==temp+2) && tab[k-7]==Nic  && k%4!=0) || (k-9>0 && (tab[k-5]==temp || tab[k-5]==temp+2) && tab[k-9]==Nic  && k%4!=1))zbijtemp=true;
if(((k-1)/4)%2==1)
    if((k+7<33 && tab[k+7]==Nic && (tab[k+4]==temp || tab[k+4]==temp+2)&& k%4!=1) || (k+9<33 && tab[k+9]==Nic && (tab[k+5]==temp || tab[k+5]==temp+2) && k%4!=0) || (k-7>0 && (tab[k-3]==temp || tab[k-3]==temp+2)&& tab[k-7]==Nic && k%4!=0) || (k-9>0 && (tab[k-4]==temp || tab[k-4]==temp+2) && tab[k-9]==Nic && k%4!=1))zbijtemp=true;
}
bool CzyZaNieDam(int k){
    Kto temp;
    if(tab[0]==Bialy)temp=Czarny;
    else temp=Bialy;
    int pion=0;
    if(((k-1)/4)%2==0){
     int i;
     if(k%4!=1){
     for(i=k-5;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
     pion=0;
     }
     for(i=k-4;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }
     pion=0;
     if(k%4!=1){
     for(i=k+3;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }
     }
    pion= 0;
     for(i=k+4;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }
     }

    else{
          int i;
     pion=0;
     for(i=k-4;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
        pion=0;
        if(k%4!=0){
     for(i=k-3;(i>0) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }

        }
     pion=0;
     for(i=k+4;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }

     pion=0;
     if(k%4!=0){
     for(i=k+5;(i<33) && ((tab[i]!=tab[0] && tab[i]!=tab[0]+2 && pion==0) || (pion!=0 && tab[i]==Nic));){
                if(tab[i]==Nic){ruchy[i]=true;if(pion!=0){zbijtemp=true;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }

     }
    }
 return 0;
}


void DelPom(){
 delete(xtab);
 delete(ytab);
 delete(ruchy);
// delete(tab);
}
