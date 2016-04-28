#include "Pom.h"
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
    Kto temp;
    if(tab[0]==Bialy)temp=Czarny;
    else temp=Bialy;
    ZaNieBicie=false;
    int j;
    if(tab[k]!=BialyD && tab[k]!=CzarnyD)
    {
    if(zbij[0]!=0){
    //if((k-1)/4-((i-1)/4)!=2 && (k-1)/4-((i-1)/4)!=-2)
                if((k-1)/4-((i-1)/4)==2 || (k-1)/4-((i-1)/4)==-2){
    if(((k-1)/4)%2==1){
        tab[((k+i)/2)+1]=Nic; //if(labs(k-i)==7 || labs(k-i)==9)
    }
     if(((k-1)/4)%2==0){
        tab[(k+i)/2]=Nic; //if(labs(k-i)==7 || labs(k-i)==9)
    }
    CzyZbite=true;
    }
    }

    if(CzyZbite==false){
     for(j=1; j<33; j++){
        if(tab[j]==tab[0])ZbadajRuchy(j);
        if(tab[j]==tab[0]+2)ZbadajRuchyDam(j);
        if(zbij[0]!=0){
        ZaNieBicie=true; break;
        }
     }
    }

    if(zbij[0]==0) {CzyKon=true;
    }

            //if((k-1)/4-((i-1)/4)!=2 && (k-1)/4-((i-1)/4)!=-2){
         /*for(j=1; j<33; j++){
            if(tab[j]==tab[0]==tab[0]+2){
                    if(((j-1)/4)%2==0)
                        if((j+7<33 && tab[j+7]==Nic && tab[j+3]==temp && j%4!=1) ||  (j+9<33 && tab[j+9]==Nic && tab[j+4]==temp && j%4!=0) ||  (j-7>0 && tab[j-4]==temp && tab[j-7]==Nic  && j%4!=0) ||  (j-9>0 && tab[j-5]==temp && tab[j-9]==Nic  && j%4!=1)){
                            ZaNieBicie=true;
                            break;
                        }
                    if(((j-1)/4)%2==1)
                        if( (j-9>0 && tab[j-4]==temp && tab[j-9]==Nic && j%4!=1) || (j-7>0 && tab[j-3]==temp && tab[j-7]==Nic && j%4!=0) || (j+9<33 && tab[j+9]==Nic && tab[j+5]==temp && j%4!=0) || (j+7<33 && tab[j+7]==Nic && tab[j+4]==temp && j%4!=1)){
                         ZaNieBicie=true;
                            break;
                        }

            }
         }*/

    tab[k]=Nic;
    tab[i]=tab[0];
    //if(j==k)tab[i]=Nic;
    }
    else{
     SaKolRuch=true;
     tab[i]=tab[k];
     tab[k]=Nic;
     if(tab[zbij[i]]==temp || tab[zbij[i]]==temp+2){
        tab[zbij[i]]=Nic;CzyZbite=true;}
     else{
     CzyKon=true;
     CzyZmian=true;
     SaKolRuch=false;
     }
    if(CzyZbite==false){
     for(j=1; j<33; j++){
        if(tab[j]==tab[0])ZbadajRuchy(j);
        if(tab[j]==tab[0]+2)ZbadajRuchyDam(j);
        if(zbij[0]!=0){
        ZaNieBicie=true; break;
        }
     }
    }
    }
    //if(ZaNieBicie==true){frame=0;}

    if(tab[0]==Czarny && ((i-1)/4)==7)tab[i]=CzarnyD;
    if(tab[0]==Bialy && ((i-1)/4==0))tab[i]=BialyD;

    if(ZaNieBicie==true)
         if(j!=k)tab[j]=Nic;
    WyczRuchy();
    return i;
}

void WyczRuchy(){
 for(int i=0; i<34; i++){
  ruchy[i]=false;
 }
}

void ZbadajRuchy(int k){
    for(int i=0; i<33; i++)
        zbij[i]=0;
    Kto temp;
    if(tab[0]==Bialy)temp=Czarny;
    else temp=Bialy;
    bool czy=false;
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
         SaKolRuch=true;
         break;
        }
        if(czy==false){  //Nie ma ju¿ ruchów!!!
         CzyZmian=true;
        }

}

void ZbadajRuchyDam(int k){
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
     for(i=k-5;(i>0) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
     if(i>0){
     if(tab[i]==Nic)ruchy[i]=true;
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==0 && i%4!=1 && tab[i-5]==Nic){ruchy[i-5]=true;zbij[i-5]=i;zbij[0]++;}
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==1  && tab[i-4]==Nic){ruchy[i-4]=true;zbij[i-4]=i;zbij[0]++;}
     }
     }
     for(i=k-4;(i>0) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }
     if(i>0){
     if(tab[i]==Nic)ruchy[i]=true;
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==1 && i%4!=0 && tab[i-3]==Nic){ruchy[i-3]=true;zbij[i-3]=i;zbij[0]++;}
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==0 && tab[i-4]==Nic){ruchy[i-4]=true;zbij[i-4]=i;zbij[0]++;}
     }
     if(k%4!=1){
     for(i=k+3;(i<33) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }
     }
     if(i<33){
     if(tab[i]==Nic)ruchy[i]==true;
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==0 && tab[i+3]==Nic){ruchy[i+3]=true;zbij[i+3]=i;zbij[0]++;}
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==1 && tab[i+4]==Nic){ruchy[i+4]=true;zbij[i+4]=i;zbij[0]++;}
     }

     for(i=k+4;(i<33) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }
     if(tab[i]==Nic)ruchy[i]==true;
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==0 && tab[i+4]==Nic){ruchy[i+4]=true;zbij[i+4]=i;zbij[0]++;}
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==1 &&i%4!=0 && tab[i+5]==Nic){ruchy[i+5]=true;zbij[i+5]=i;zbij[0]++;}
     }

    else{
          int i;

     for(i=k-4;(i>0) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==1)i-=4;
                else{if(i%4==1)break; i-=5;}
     }
     if(i>0){
     if(tab[i]==Nic)ruchy[i]=true;
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==0 && i%4!=1 && tab[i-5]==Nic){ruchy[i-5]=true;zbij[i-5]=i;zbij[0]++;}
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==1  && tab[i-4]==Nic){ruchy[i-4]=true;zbij[i-4]=i;zbij[0]++;}
      }
        if(k%4!=0){
     for(i=k-3;(i>0) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==0){i-=4;}
                else {if(i%4==0)break;i-=3;}
                }
     if(i>0){
     if(tab[i]==Nic)ruchy[i]=true;
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==1 && i%4!=0 && tab[i-3]==Nic){ruchy[i-3]=true;zbij[i-3]=i;zbij[0]++;}
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==0 && tab[i-4]==Nic){ruchy[i-4]=true;zbij[i-4]=i;zbij[0]++;}
     }
        }
     for(i=k+4;(i<33) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==0){if(i%4==1)break;i+=3;}
                else {i+=4;}
     }

     if(i<33){
     if(tab[i]==Nic)ruchy[i]==true;
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==0 && tab[i+3]==Nic){ruchy[i+3]=true;zbij[i+3]=i;zbij[0]++;}
     else
     if((tab[i]==temp || tab[i]==temp+2) && ((i-1)/4)%2==1 && tab[i+4]==Nic){ruchy[i+4]=true;zbij[i+4]=i;zbij[0]++;}
     }

     if(k%4!=0){
     for(i=k+5;(i<33) && (tab[i]==Nic);){
                ruchy[i]=true;
                if(((i-1)/4)%2==1){if(i%4==0)break;i+=5;}
                else {i+=4;}
     }
     if(i<33){
     if(tab[i]==Nic)ruchy[i]==true;
     else
     if(tab[i]==temp && ((i-1)/4)%2==0 && tab[i+4]==Nic){ruchy[i+4]=true;zbij[i+4]=i;zbij[0]++;}
     else
     if(tab[i]==temp && ((i-1)/4)%2==1 && i%4!=0 && tab[i+5]==Nic){ruchy[i+5]=true;zbij[i+5]=i;zbij[0]++;}
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


void DelPom(){
 delete(xtab);
 delete(ytab);
 delete(ruchy);
// delete(tab);
}
