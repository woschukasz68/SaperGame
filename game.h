#ifndef GRA_H
#define GRA_H
#include <stdbool.h>
#include "plansza.h"

extern const int bomby_latwy;
extern const int plansza_latwy_x;
extern const int plansza_latwy_y;
extern const int bomby_sredni;
extern const int plansza_sredni_x;
extern const int plansza_sredni_y;
extern const int bomby_trudny;
extern const int plansza_trudny_x;
extern const int plansza_trudny_y;

void generuj_bomby(struct Pole ** plansza, int x, int y, int liczba_bomb);
void generuj_pola_neutralne(struct Pole **plansza, int x, int y);
int odkrywanie_pola(struct Pole ** plansza, int x, int y, int planszaX, int planszaY);
int ustaw_flage(struct Pole ** plansza, int x, int y, int planszaX, int planszaY);
void generuj_plansza(struct Pole ** plansza, int planszaX, int planszaY);
struct Pole ** tworz_plansza(int maxX, int maxY);
void zniszcz_plansze(struct Pole **plansza);

#endif
