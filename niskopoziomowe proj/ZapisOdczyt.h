#ifndef ZAPISODCZYT_H_INCLUDED
#define ZAPISODCZYT_H_INCLUDED
#include <fstream>
#include <iostream>
#include <allegro.h>
#include <string>
#include "Multiplayer.h"

void Zapisz(int tab[], int biale, int czarne, int ktory);

void DialogMulti();
void DialogSingle();
int *Wczytaj(int ktory);
int *Wczytaj2();
int *Wczytaj1S();
int *Wczytaj2S();

#endif // ZAPISODCZYT_H_INCLUDED
