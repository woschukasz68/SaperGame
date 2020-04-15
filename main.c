#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"
#include "gra.h"
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int main()
{

    int x, y;
    int poziom;
    int plansza_poziomX;
    int plansza_poziomY;
    int bomby_poziom;
    int szerokosc;
    int dlugosc;
    int bomby;

    struct Pole** plansza = NULL;

    printf("Graczu wybierz poziom trudnosci: \n");
    printf("[1] Latwy\n");
    printf("[2] Sredni\n");
    printf("[3] Trudny\n");
    printf("[4] Poziom niestandardowy\n");
    scanf("%d", &poziom);

    system(CLEAR);  // odswiezanie konsoli

switch(poziom){

    case 1:

        plansza_poziomX = plansza_latwy_x;
        plansza_poziomY = plansza_latwy_y;
        bomby_poziom = bomby_latwy;
        break;

    case 2:

        plansza_poziomX = plansza_sredni_x;
        plansza_poziomY = plansza_sredni_y;
        bomby_poziom = bomby_sredni;
        break;

    case 3:

        plansza_poziomX = plansza_trudny_x;
        plansza_poziomY = plansza_trudny_y;
        bomby_poziom = bomby_trudny;
        break;

    case 4:

        printf("Podaj szerokosc planszy: ");
        scanf("%d", &szerokosc);
        printf("Podaj dlugosc planszy: ");
        scanf("%d", &dlugosc);
        printf("Podaj ilosc bomb: ");
        scanf("%d", &bomby);
        plansza_poziomX = szerokosc;
        plansza_poziomY = dlugosc;
        bomby_poziom = bomby;
        break;

    default:

        printf("Wybierz liczbe z zakresu 1-4");
        break;
}


        plansza = tworz_plansza(plansza_poziomX, plansza_poziomY);

        generuj_bomby(plansza, plansza_poziomX, plansza_poziomY, bomby_poziom);

        do{

            generuj_plansza(plansza, plansza_poziomX, plansza_poziomY);
            printf("Podaj X(dodanie '-' wywoluje flage): ");
            scanf("%d", &x);
            printf("Podaj Y(dodanie '-' wywoluje flage): ");
            scanf("%d", &y);

            system(CLEAR);
            if(x<0 && y<0){
                ustaw_flage(plansza, x+1, y+1, plansza_poziomX, plansza_poziomY);
                continue;
            }

        }while(odkrywanie_pola(plansza, x-1, y-1, plansza_poziomX, plansza_poziomY) != 1);

    zniszcz_plansze(plansza);
}
