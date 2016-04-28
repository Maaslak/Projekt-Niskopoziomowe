#include <cstddef>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "JedenGracz.h"

using namespace std;

const int infinity=1000000;
const int minusinfinity=-1000000;
const int Max_Glebokosc=5;

wezel* korzen=NULL;

Kto* RuchKomputer(Kto tablica[]){
 cout<<"Mysle........\n";
 int wart;
 korzen=new wezel;
 korzen->ojciec=NULL;
 korzen->tab=CopyArrayKto(tablica);
 korzen->Max=true;
 wart=MinMax(korzen);
 for(vector <wezel*>::iterator i=korzen->potomkowie.begin(); i!=korzen->potomkowie.end(); ++i)
 if((*i)->WartHeur==wart){
  cout<<"Wybrana ostatecznie: "<<wart<<'\n';
  return (*i)->tab;
 }
 return korzen->tab;
}

void CzyscDrzewo(wezel* wez){
for(vector <wezel*>::iterator it=wez->potomkowie.begin(); it!=wez->potomkowie.end(); ++it)
    CzyscDrzewo(*it);
delete(wez);
}

bool CzyTerminalny(Kto tablica[]){
 bool biale=false, czarne=false;
 for(int i=0; i<33; i++){
        if(tablica[i]==Bialy)biale=true;
        if(tablica[i]==Czarny)czarne=true;
        if(biale==true && czarne==true)return 0;
 }
 return 1;
}

int Ewaluacja(wezel* wez){
int ocena=0;
Kto temp;
if(tab[0]==Bialy)temp=Czarny;
else temp=Bialy;
for(int i=1; i<33; i++){
 if(wez->tab[i]==Czarny){
        ocena+=5;
        switch((i-1)/4){
         case 2:ocena+=1;
                break;
         case 3:ocena+=1;
                break;
         case 4:ocena+=3;
                break;
         case 5:ocena+=3;
                break;
         case 6:ocena+=20;
                break;
        }
        if((i-1)/4%2==0 && (i-1)%4<3 && i>4){
                ocena+=1;
        }
        if((i-1)/4%2==1 && (i-1)%4>0 && i>4){
                ocena+=1;
        }
 }
 if(wez->tab[i]==Czarny+2)ocena+=50;
 if(wez->tab[i]==Bialy){
        ocena-=5;
         switch((i-1)/4){
         case 5:ocena-=1;
                break;
         case 4:ocena-=1;
                break;
         case 3:ocena-=3;
                break;
         case 2:ocena-=3;
                break;
         case 1:ocena-=20;
                break;
        }
        if((i-1)/4%2==0 && (i-1)%4<3 && i<29){
                ocena-=1;
        }
        if((i-1)/4%2==1 && (i-1)%4>0 && i<29){
                ocena-=1;
        }
 }
 if(wez->tab[i]==Bialy+2)ocena-=50;
}
return ocena;
}
/*
int IleBic(Kto* tablica){
Kto* temp=CopyArrayKto(tablica);
int MaksymalnaIloscBic=0;
short int* zbij;
for(int i=1; i<33; i++)
    if(tab[i]==tab[0]){zbij=ZbadajRuchy(i, temp, 0)
        while(zbij[0]){
         for(int j=1; j<
        }
    }
}*/

bool CzyGlebokoscOk(wezel* wez){
 wezel* cur=wez;
 int ile=0;
 while(cur!=NULL){
  cur=cur->ojciec;
  ile++;
 }
 if(ile>Max_Glebokosc)return 0;
 return 1;
}

int MinMax(wezel* wez){
 if(wez->Max==true)wez->WartHeur=minusinfinity;
 else wez->WartHeur=infinity;
 if(CzyTerminalny(wez->tab)==1 || !CzyGlebokoscOk(wez))
    return wez->WartHeur=Ewaluacja(wez);
 GenPotomkow(wez, 0);
 for(unsigned int i=0; i<wez->potomkowie.size(); i++){
     if(wez->Max==true){
     wez->WartHeur=max(wez->WartHeur, MinMax(wez->potomkowie[i]));if(wez==korzen)cout<<wez->WartHeur<<' ';}
     else{
     wez->WartHeur=min(wez->WartHeur, MinMax(wez->potomkowie[i]));}
    }
 return wez->WartHeur;
 }

 Kto* CopyArrayKto(Kto tablica[]){
    Kto* nowa=new Kto [33];
     for(int i=0; i<33; i++)
        nowa[i]=tablica[i];
     return nowa;
 }

void WyswietlTabliceKto(Kto* tablica){
cout<<"Kto\n"<<tab[0];
 for(int i=1; i<33; i++){
    if(i%4==1)cout<<'\n';
    if(((i-1)/4)%2==1) cout<<' ';
    cout<<tablica[i];
    if(((i-1)/4)%2==0)cout<<' ';
    }
cout<<'\n';
}

void WyswietlTabliceInt(short int* tablica){
cout<<"Int\n";
 for(int i=0; i<33; i++)
    cout<<tablica[i]<<' ';
cout<<'\n';
}

void GenPotomkow(wezel* wez, short wybrany){
 short int* zbij;
 if(wybrany==0){
 for(int i=1; i<33; i++){
    if(wez->tab[i]==wez->tab[0] || wez->tab[i]==wez->tab[0]+2){
    if(wez->tab[i]==wez->tab[0])zbij=ZbadajRuchy(i, wez->tab, 0);
    else if(wez->tab[i]==wez->tab[0]+2)zbij=ZbadajRuchyDam(i, wez->tab, 0);
    for(int j=1; j<33; j++){
        if(zbij[j]==-1){
            wezel* nowy=new wezel;
            nowy->tab=CopyArrayKto(wez->tab);
            for(int l=1; l<33; l++){
            if(nowy->tab[l]==nowy->tab[0])if(CzyZaNiePion(l, nowy->tab))break;
            if(nowy->tab[l]==nowy->tab[0]+2)if(CzyZaNieDam(l, nowy->tab))break;
            }
            WykonajRuchBezBicia(i, j, nowy->tab);
            if(nowy->tab[0]==Bialy)nowy->tab[0]=Czarny;
            else nowy->tab[0]=Bialy;
            nowy->ojciec=wez;
            if(wez->Max==true)nowy->Max=false;
            else nowy->Max=true;
            wez->potomkowie.push_back(nowy);
        }
        if(zbij[0]!=0 && zbij[j]!=-1 && zbij[j]!=0){
            wezel* nowy=new wezel;
            nowy->tab=CopyArrayKto(wez->tab);
            nowy->ojciec=wez;
            int tempWybr=WykonajRuchBicie(i, j, zbij[j], nowy->tab);
            GenPotomkow(nowy, tempWybr);
        }
    }
 }
 }
 }
 else{
 zbij=ZbadajRuchy(wybrany, wez->tab, 1);
 if(zbij[0]!=0){
 for(int i=1; i<33; i++){
  if(zbij[i]!=0){
    wezel* nowy=new wezel;
    nowy->tab=CopyArrayKto(wez->tab);
    nowy->ojciec=wez->ojciec;
    int tempWybr=WykonajRuchBicie(wybrany, i, zbij[i], nowy->tab);
    GenPotomkow(nowy, tempWybr);
  }
 }
 }
  else{
    if(wez->ojciec->Max==true)wez->Max=false;
    else wez->Max=true;
    if(wez->tab[0]==Bialy)wez->tab[0]=Czarny;
    else wez->tab[0]=Bialy;
    wez->ojciec->potomkowie.push_back(wez);
 }
 }
delete(zbij);
}

 int WykonajRuchBicie(int k, int i, int bicie, Kto* tablica){
    tablica[bicie]=Nic;
    tablica[i]=tablica[k];
    tablica[k]=Nic;
    if(tablica[0]==Czarny && ((i-1)/4)==7 && tablica[i]!=Nic){tablica[i]=CzarnyD; i=-1;}
    if(tablica[0]==Bialy && ((i-1)/4==0) && tablica[i]!=Nic){tablica[i]=BialyD; i=-1;}
    return i;
}



void WykonajRuchBezBicia(int k, int i, Kto* tablica){
    tablica[i]=tablica[k];
    tablica[k]=Nic;
    if(tablica[0]==Czarny && ((i-1)/4)==7 && tablica[i]!=Nic)tablica[i]=CzarnyD;
    if(tablica[0]==Bialy && ((i-1)/4==0) && tablica[i]!=Nic)tablica[i]=BialyD;
}

short int* ZbadajRuchy(int k, Kto* tablica, bool SaKolRuch){
    short int* zbij=new short int [33];
    for(int i=0; i<33; i++)
        zbij[i]=0;
    Kto temp;
    if(tablica[0]==Bialy)temp=Czarny;
    else temp=Bialy;

    if(((k-1)/4)%2==0){
        if(k+3<33 && tablica[k+3]==Nic && SaKolRuch==0 && tablica[0]==Czarny && k%4!=1)
            zbij[k+3]=-1;
        else
        if(k+7<33 && tablica[k+7]==Nic && (tablica[k+3]==temp || tablica[k+3]==temp+2) && k%4!=1)
                {zbij[k+7]=k+3;zbij[0]++;}
        if(k+4<33 && tablica[k+4]==Nic && SaKolRuch==0 && tablica[0]==Czarny)
            zbij[k+4]=-1;
        else
        if(k+9<33 && tablica[k+9]==Nic && (tablica[k+4]==temp || tablica[k+4]==temp+2) && k%4!=0)
                {zbij[k+9]=k+4;zbij[0]++;}
        if(k-4>0 && tablica[k-4]==Nic && SaKolRuch==0 && tablica[0]==Bialy)
            zbij[k-4]=-1;
        else
            if(k-7>0 && (tablica[k-4]==temp || tablica[k-4]==temp+2) && tablica[k-7]==Nic  && k%4!=0)
                {zbij[k-7]=k-4;zbij[0]++;}
        if(k-5>0 && tablica[k-5]==Nic && k%4!=1 && SaKolRuch==0 && tablica[0]==Bialy && k%4!=1)
        zbij[k-5]=-1;
        else
            if(k-9>0 && (tablica[k-5]==temp || tablica[k-5]==temp+2) && tablica[k-9]==Nic  && k%4!=1)
                {zbij[k-9]=k-5;zbij[0]++;}
        }
    else{
        if(k+4<33 && tablica[k+4]==Nic && SaKolRuch==0 && tablica[0]==Czarny)
            zbij[k+4]=-1;
        else
        if(k+7<33 && tablica[k+7]==Nic && (tablica[k+4]==temp || tablica[k+4]==temp+2)&& k%4!=1)
                {zbij[k+7]=k+4;zbij[0]++;}
        if(k+5<33 && tablica[k+5]==Nic && SaKolRuch==0 && tablica[0]==Czarny && k%4!=0)
            zbij[k+5]=-1;
        else
        if(k+9<33 && tablica[k+9]==Nic && (tablica[k+5]==temp || tablica[k+5]==temp+2) && k%4!=0)
                {zbij[k+9]=k+5;zbij[0]++;}
        if(k-3>0 && tablica[k-3]==Nic && k%4!=0 && SaKolRuch==0 && tablica[0]==Bialy && k%4!=0)
        zbij[k-3]=-1;
        else
            if(k-7>0 && (tablica[k-3]==temp || tablica[k-3]==temp+2)&& tablica[k-7]==Nic && k%4!=0)
                {zbij[k-7]=k-3;zbij[0]++;}
        if(k-4>0 && tablica[k-4]==Nic && SaKolRuch==0 && tablica[0]==Bialy)
        zbij[k-4]=-1;
        else
        if(k-9>0 && (tablica[k-4]==temp || tablica[k-4]==temp+2) && tablica[k-9]==Nic && k%4!=1)
                {zbij[k-9]=k-4;zbij[0]++;}
    }
    //WyswietlTabliceKto(tablica);
    //WyswietlTabliceInt(zbij);
    return zbij;
}

short int* ZbadajRuchyDam(int k, Kto* tablica, bool SaKolRuch){
    int pion=0;
    Kto temp;
    short int* zbij=new short int [33];
    if(tablica[0]==Bialy)temp=Czarny;
    else temp=Bialy;
    bool czy=false;
    for(int i=0; i<34; i++)
        zbij[i]=0;

    if(((k-1)/4)%2==0){
     int i;
     if(k%4!=1){
     for(i=k-5;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
     pion=0;
     }
     for(i=k-4;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }
     pion=0;
     if(k%4!=1){
     for(i=k+3;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }
     }
    pion= 0;
     for(i=k+4;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }
     }

    else{
          int i;
     pion=0;
     for(i=k-4;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
        pion=0;
        if(k%4!=0){
     for(i=k-3;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }

        }
     pion=0;
     for(i=k+4;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }

     pion=0;
     if(k%4!=0){
     for(i=k+5;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){zbij[i]=-1;if(pion!=0){zbij[i]=pion;zbij[0]++;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }

     }
    }


return zbij;
}

bool CzyZaNiePion(int k, Kto* tablica){
Kto temp;
if(tablica[0]==Bialy)temp=Czarny;
else temp=Bialy;
if(((k-1)/4)%2==0)
    if((k+7<33 && tablica[k+7]==Nic && (tablica[k+3]==temp || tablica[k+3]==temp+2) && k%4!=1) || (k+9<33 && tablica[k+9]==Nic && (tablica[k+4]==temp || tablica[k+4]==temp+2) && k%4!=0) || (k-7>0 && (tablica[k-4]==temp || tablica[k-4]==temp+2) && tablica[k-7]==Nic  && k%4!=0) || (k-9>0 && (tablica[k-5]==temp || tablica[k-5]==temp+2) && tablica[k-9]==Nic  && k%4!=1)){tablica[k]=Nic;return 1;}
if(((k-1)/4)%2==1)
    if((k+7<33 && tablica[k+7]==Nic && (tablica[k+4]==temp || tablica[k+4]==temp+2)&& k%4!=1) || (k+9<33 && tablica[k+9]==Nic && (tablica[k+5]==temp || tablica[k+5]==temp+2) && k%4!=0) || (k-7>0 && (tablica[k-3]==temp || tablica[k-3]==temp+2)&& tablica[k-7]==Nic && k%4!=0) || (k-9>0 && (tablica[k-4]==temp || tablica[k-4]==temp+2) && tablica[k-9]==Nic && k%4!=1)){tablica[k]=Nic;return 1;}
return 0;
}

bool CzyZaNieDam(int k, Kto* tablica){
    Kto temp;
    if(tablica[0]==Bialy)temp=Czarny;
    else temp=Bialy;
    int pion=0;
    if(((k-1)/4)%2==0){
     int i;
     if(k%4!=1){
     for(i=k-5;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
     pion=0;
     }
     for(i=k-4;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }
     pion=0;
     if(k%4!=1){
     for(i=k+3;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }
     }
    pion= 0;
     for(i=k+4;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }
     }

    else{
          int i;
     pion=0;
     for(i=k-4;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
        pion=0;
        if(k%4!=0){
     for(i=k-3;(i>0) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }

        }
     pion=0;
     for(i=k+4;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }

     pion=0;
     if(k%4!=0){
     for(i=k+5;(i<33) && ((tablica[i]!=tablica[0] && tablica[i]!=tablica[0]+2 && pion==0) || (pion!=0 && tablica[i]==Nic));){
                if(tablica[i]==Nic){ruchy[i]=true;if(pion!=0){tablica[k]=Nic;return 1;}}
                else pion=i;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }

     }
    }
 return 0;
}

