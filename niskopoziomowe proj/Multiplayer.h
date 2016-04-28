#include "Pomocniczy.h"
#include "ZapisOdczyt.h"
#include "JedenGracz.h"
#include <allegro.h>
#include <semaphore.h>
#include<cmath>
#include <time.h>
#include <cstdlib>
#include <string>

//Za nie bicie anim
  // extern int xtab[33], ytab[33];

//using namespace std;

inline void initM();
void initBez();
void initBezS();
void initZ(int Z);
inline void deinitM();
void ticker();
int CreateBit();
void Wyswietl();
void myszka();
void PierwszyRuch();
void WybranyPion();
void wait(int seconds);
void KolejnyRuch();
void ZmienZaw();
void ZmienZawS();
void ZakonczAnim();
void Anuluj();
int Multiplayer(int pocz);
int SinglePlayer(int pocz);
void LiczZbite();
