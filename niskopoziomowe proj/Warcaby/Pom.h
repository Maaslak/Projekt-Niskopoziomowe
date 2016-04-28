#ifndef POM_H_INCLUDED
#define POM_H_INCLUDED
#include<cmath>

enum Kto{Nic, Czarny, Bialy, CzarnyD, BialyD};
extern int xtab[33], ytab[33];
extern bool ruchy[33], SaKolRuch;
extern Kto tab[33];
extern bool CzyZmian, CzyKon, ZaNieBicie, ZaNieBicie2, CzyWybr;
extern int frame;
static short int zbij[33];

void GenStanPocz();
void GenXY();
void DelPom();
void ZbadajRuchy(int k);
void ZbadajRuchyDam(int k);
int WykonajRuch(int k, int i);
void WyczRuchy();


#endif // POM_H_INCLUDED
