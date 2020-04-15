#include "gra.h"     // wlaczenie biblioteki deklaracyjnej
#include <stdlib.h>     // biblioteka funkcji losowania
#include <time.h>
#include <stdbool.h>    // dodanie typu boole do jezyka

const int bomby_latwy = 15;
const int plansza_latwy_x = 10;
const int plansza_latwy_y = 10;
const int bomby_sredni = 80;
const int plansza_sredni_x = 15;
const int plansza_sredni_y = 15;
const int bomby_trudny = 150;
const int plansza_trudny_x = 20;
const int plansza_trudny_y = 20;

struct Pole ** tworz_plansza(int maxX, int maxY){   // funkcja zwracajaca dynamiczna tablice typu struct pole

struct Pole **plansza = malloc(sizeof *plansza * maxX); // alokacja pamieci ograniczona do szerokosci planszy
    if (plansza)
    {
        for (int i = 0; i < maxX; i++)
        {
            plansza[i] = malloc(sizeof *plansza[i] * maxY); // alokacja pamieci ograniczona do dlugosci planszy
        }
    }
    for(int i=0; i<maxX; i++)
    {
        for(int j=0; j<maxY; j++)
        {
            plansza[i][j].wartosc = 0;      // poczatkowa wartosc pola to 0, jest zakryte i nie ma flagi
            plansza[i][j].odkryte = false;
            plansza[i][j].flaga = false;
        }
    }
    return plansza;
}

void zniszcz_plansze(struct Pole **plansza){
    free(plansza);      // zwalnianie zaalokowanej pamieci
}

void generuj_plansza(struct Pole ** plansza, int planszaX, int planszaY){
for(int i=0; i<planszaX; i++)
        {
            for(int j=0; j<planszaY; j++)
            {
                if(plansza[i][j].odkryte)
                {
                    if(plansza[i][j].wartosc == 9)
                    {
                        printf("# ");
                    }
                    else
                    {
                        printf("%d ",plansza[i][j].wartosc);
                    }
                }
                else
                {
                    if(plansza[i][j].flaga){
                        printf("F ");
                    }
                    else
                        printf("@ ");
                }
            }
            printf("\n");
        }

}

void generuj_bomby(struct Pole ** plansza, int x, int y, int liczba_bomb) {
    srand(time(NULL));
    int bomby = 0;

        while(liczba_bomb != bomby){
        int pozycja_bomby_x=rand() % x;
        int pozycja_bomby_y=rand() % y;
        if(plansza[pozycja_bomby_x][pozycja_bomby_y].wartosc == 9){ // zabezpieczenie przed wygenerowanie bomby w tym samymym miejscu
            continue;
        }
        plansza[pozycja_bomby_x][pozycja_bomby_y].wartosc = 9;
        generuj_pola_neutralne(plansza, pozycja_bomby_x, pozycja_bomby_y);
        bomby++;
        }
}
void generuj_pola_neutralne(struct Pole** plansza, int x, int y){
 for(int i=-1; i<2; i++){
    for(int j=-1; j<2; j++){
        if((x+j) < 0 || (y+i) < 0 || (x+j) > 9 || (y+i)>9 ) continue;   // sprawdzanie wyjscia za tablice
        if(plansza[x+j][y+i].wartosc == 9 ) continue;    // sprawdzenie czy jest juz tam bomba
        plansza[x+j][y+i].wartosc +=1;  // zwiekszanie licznika gdy w sasiednich polach jest bomba

    }
 }
}

int odkrywanie_pola(struct Pole ** plansza, int x, int y, int planszaX, int planszaY){
    if(x<0 || x > planszaX || y < 0 || y > planszaY){   // zaebzpieczenie przed podaniem wspolrzednych spoza tablicy
        return -1;
    }

    if(plansza[x][y].wartosc == 9){
        printf("Trafiles na bombe!");
        plansza[x][y].odkryte = true;
        return 1;
    }

    if(plansza[x][y].odkryte){
        return plansza;
    }
    if(plansza[x][y].flaga){
        return 3;
    }
        plansza[x][y].odkryte = true;

    if(plansza[x][y].wartosc !=0){  // rozszerzanie pola neutralnego do pol sasiadujacych z bomba/bombami
        return 2;
    }

    odkrywanie_pola(plansza, x-1, y-1, planszaX, planszaY);
    odkrywanie_pola(plansza, x, y-1, planszaX, planszaY);
    odkrywanie_pola(plansza, x+1, y-1, planszaX, planszaY);
    odkrywanie_pola(plansza, x+1, y, planszaX, planszaY);
    odkrywanie_pola(plansza, x+1, y+1, planszaX, planszaY);
    odkrywanie_pola(plansza, x, y+1, planszaX, planszaY);
    odkrywanie_pola(plansza, x-1, y+1, planszaX, planszaY);
    odkrywanie_pola(plansza, x, y-1, planszaX, planszaY);
}

int ustaw_flage(struct Pole ** plansza, int x, int y, int planszaX, int planszaY){
    x = -x;
    y = -y;
    if(x<0 || x > planszaX || y < 0 || y > planszaY){
        return -1;
    }
    plansza[x][y].flaga = true;
}
