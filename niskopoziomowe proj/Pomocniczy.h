#ifndef POMOCNICZY_H_INCLUDED
#define POMOCNICZY_H_INCLUDED

enum Kto{Nic, Czarny, Bialy, CzarnyD, BialyD};
extern int xtab[33], ytab[33], bialeZbite, czarneZbite;
extern bool ruchy[33], SaKolRuch;//ruchy przechowuje dostêpne ruchy, SaKolRuch pamiêta czy nie zakonczyc ruchu
extern Kto tab[33];//stan planszy tab[0]-gracz
extern bool CzyZmian, CzyKon, ZaNieBicie, ZaNieBicie2, CzyWybr, CzyKol;
//CzyZmiana- nalezy zmienic zawodnika
extern int frame;
static short int zbij[33];//bada, nic nie znaczy
static short int zbijtemp;//Do ZaNie bicie tracisz życie

void GenStanPocz();//tab wypelnia sie
void GenXY();//tabx i taby wypelnia sie
void DelPom();//zwolnienie pamieci
void ZbadajRuchy(int k);//bada ruchy pion
void ZbadajRuchyDam(int k);//bada ruchy damek
int WykonajRuch(int k, int i);// wykonuje ruch
void WyczRuchy();//czysci ruchy
void CzyZaNieBicie();
void CzyZaNiePion(int k);
bool CzyZaNieDam(int k);

#endif // POMOCNICZY_H_INCLUDED
