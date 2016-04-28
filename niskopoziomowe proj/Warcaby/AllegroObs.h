#ifndef ALLEGROOBS_H_INCLUDED
#define ALLEGROOBS_H_INCLUDED
#include<allegro.h>
#include<cmath>
#include <time.h>
#include <semaphore.h>
#include <vector>
static sem_t sem_rest;
static BITMAP * plansza = NULL, * bufor = NULL, *kursor;
static int xtab[33], ytab[33];
static volatile int ticks = 0;
static const int updates_per_second = 60;
static int mx = 0, my = 0, mb = 0;
static int k;
static bool CzyPionek=false, * ruchy=NULL;
static const int epsilon=18;

enum Kto{Nic, Czarny, Bialy, CzarnyD, BialyD};
static Kto* tab;
int CreateBit();

inline void init();
inline void deinit();

void WyswietlStanGry(Kto tab[]);
void WlaczGre();
int CreateBit();
void myszka();
bool Ruch();
void wait(int seconds);
void Wybor();
void ZbadajRuchy();

#endif // ALLEGROOBS_H_INCLUDED
