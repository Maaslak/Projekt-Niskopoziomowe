#ifndef JEDENGRACZ_H_INCLUDED
#define JEDENGRACZ_H_INCLUDED
#include "Pomocniczy.h"
#include <vector>

struct wezel{
Kto* tab;
int WartHeur;
wezel* ojciec;
bool Max;
std::vector <wezel*> potomkowie;
};
bool CzyGlebokoscOk(wezel* wez);
int MinMax(wezel* wez);
short int* ZbadajRuchy(int k, Kto tablica[], bool SaKolRuch);
short int* ZbadajRuchyDam(int k, Kto* tablica, bool SaKolRuch);
void GenPotomkow(wezel* point, short wybrany);
void WykonajRuchBezBicia(int k, int i, Kto* tablica);
bool CzyTerminalny(Kto tablica[]);
Kto* CopyArrayKto(Kto tablica[]);
int WykonajRuchBicie(int k, int i, int bicie, Kto* tablica);
int Ewaluacja(wezel* wez);
Kto* RuchKomputer(Kto tablica[]);
void CzyscDrzewo(wezel* wez);
bool CzyZaNiePion(int k, Kto* tablica);
bool CzyZaNieDam(int k, Kto* tablica);
int IleBic(Kto* tablica);


#endif // JEDENGRACZ_H_INCLUDED
