#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

typedef enum {TRUE = 1, FALSE = 0} bool;

const int rozmiar_kostki = 100;


void rysuj_kostke(ALLEGRO_BITMAP  *obrazy_kostek[], int nr, bool zaznaczona = FALSE)
{
	const int wyswietlanie_kostki_x = 100;
	const int wyswietlanie_kostki_y = 100;

	if(zaznaczona)
		al_draw_bitmap(zaznaczenie_kostki, wyswietlanie_kostki_x - 10, wyswietlanie_kostki_y - 10, 0);

	al_draw_bitmap(obrazy_kostek[nr], wyswietlanie_kostki_x * (rozmiar_kostki + 25), wyswietlanie_kostki_y, 0);
}

void odswiez_ekran()
{
	al_flip_display();
}

void pobierz_klawisz(ALLEGRO_EVENT *ev, )
{
	do
	{
		al_wait_for_event(event_queue, *ev);
	}while(ev->type != ALLEGRO_EVENT_KEY_DOWN);
}

void wypisz_wiadomosc()
{

}


int rzut(int wynik[]){

    srand(time(NULL));
    int i;

    printf("\nOto twoj rzut: ");
    for (i=0;i<5;i++){
        wynik[i] = (rand()%6)+1;
        printf("%d ",wynik[i]);
    }
    return wynik;
}

int przerzut(int wynik[]){
    int ile;
    printf("\nIle kosci chcesz przerzucic? ");
    scanf("%d",&ile);
    while (ile<0 || ile>5){
        printf("Mozesz przerzucic od 0 do 5 kosci, podaj jeszcze raz: ");
        scanf("%d",&ile);
    }
    int i,a;
    if (ile != 0){
        int t_ile[5] = {0,0,0,0,0};
        if (ile != 5){
            printf("Kosci do przerzucenia:\n");
            for (i=0;i<ile;i++){
            scanf("%d",&a);
            t_ile[a-1]=1;
            }
        }
        if (ile == 5){
            for (i=0;i<ile;i++){
            t_ile[i]=1;
            }
        }
        puts("\n\n");
        for (i=0;i<5;i++){
        printf("%d",t_ile[i]);
        }
        puts("\n\nPo przerzuceniu:\n");

        for (i=0;i<5;i++){
            if (t_ile[i] == 1){
                wynik[i] = (rand()%5)+1;
            }
        }

        for (i=0;i<5;i++){
            printf("%d ",wynik[i]);
        }
    }
    return 0;
}

int punktacja(int wynik[],int punkty){
    int i,j;
    int co_wypadlo=0;
    bool para = FALSE;
    bool trojka = FALSE;

    int liczby[6] = {0,0,0,0,0,0};
    for (i=0;i<5;i++){

        if (wynik[i]==1)
            liczby[0]++;

        if (wynik[i]==2)
            liczby[1]++;

        if (wynik[i]==3)
            liczby[2]++;

        if (wynik[i]==4)
            liczby[3]++;

        if (wynik[i]==5)
            liczby[4]++;

        if (wynik[i]==6)
            liczby[5]++;
    }
    puts("\n");
   // for (i=0;i<6;i++)
   //         printf("%d,",liczby[i]);
    /*
        nic = 0
        para = 2
        trojka = 3
        kareta = 4
        general = 5
        dwie pary = 22
        maly strit = 15
        duzy strit = 26
        full = 32

    */
    int l_par=0;

    //para lub dwie pary
    for (i=0;i<6;i++){
        if (liczby[i] == 2){
            para = TRUE;
            l_par++;
        }
    }
    if (l_par == 1)
        co_wypadlo = 2;
    if (l_par == 2)
        co_wypadlo = 22;

    //trojka
    for (i=0;i<6;i++){
    if (liczby[i] == 3)
        trojka = TRUE;
    }
    if (trojka == TRUE)
        co_wypadlo = 3;
    //full
    if (trojka == TRUE && para == TRUE)
        co_wypadlo = 32;
    //kareta
    for (i=0;i<6;i++){
    if (liczby[i] == 4)
        co_wypadlo = 4;
    }
    //general
    for (i=0;i<6;i++){
    if (liczby[i] == 5)
        co_wypadlo = 5;
    }

    //strity
    j = 0;
    int maly_strit = 0, duzy_strit = 0;
    for (i=0;i<5;i++){
        if (liczby[i] == 1)
            maly_strit++;
    }
    if (maly_strit == 5)
        co_wypadlo = 15;

    for (i=1;i<6;i++){
        if (liczby[i] == 1)
            duzy_strit++;
    }
    if (duzy_strit == 5)
        co_wypadlo = 26;

    switch(co_wypadlo){

        case 0:
        printf("\nPrzykro mi.\n");
        punkty = 0;
        break;

        case 2:
        printf("\nMasz jedna pare\n");
        punkty = 10;
        break;

        case 3:
        printf("\nMasz trojke\n");
        punkty = 20;
        break;

        case 32:
        printf("\nMasz fulla\n");
        punkty = 40;
        break;

        case 4:
        printf("\nMasz karete\n");
        punkty = 50;
        break;

        case 5:
        printf("\nMasz generala!\n");
        punkty = 80;
        break;

        case 15:
        printf("\nMasz malego (strita)\n");
        punkty = 30;
        break;

        case 22:
        printf("\nMasz dwie pary\n");
        punkty = 20;
        break;

        case 26:
        printf("\nMasz duzego strita\n");
        punkty = 40;
        break;

        default: printf("???");
        break;
    }
    if (punkty !=0)
    printf("\n\nTwoja punktacja: %d",punkty);
    else printf("\n\nTwoja punktacja to kompletne nic.");

    return punkty;
}

void wczytaj_kostki(ALLEGRO_BITMAP  *obrazy_kostek[])
{
	obrazy_kostek[0] = al_load_bitmap("obrazy/kostka1.png");
	obrazy_kostek[1] = al_load_bitmap("obrazy/kostka2.png");
	obrazy_kostek[2] = al_load_bitmap("obrazy/kostka3.png");
	obrazy_kostek[3] = al_load_bitmap("obrazy/kostka4.png");
	obrazy_kostek[4] = al_load_bitmap("obrazy/kostka5.png");
	obrazy_kostek[5] = al_load_bitmap("obrazy/kostka6.png");
}

void zwolnij_kostki(ALLEGRO_BITMAP  *obrazy_kostek[])
{
	for(int i = 0; i < 6; i++)
		al_destroy_bitmap(obrazy_kostek[i]);
}

int main(void)
{
	ALLEGRO_DISPLAY *display = al_create_display(800,600);
	ALLEGRO_BITMAP  *obrazy_kostek[6];


    int wynik[5],koniec,punkty;
    int tryb = 1,wyjscie;
    int gracz1 = 0,ilegraczy,i,n,r=1;
    int gracz[4];
    int runda;
    int rmax;
    int wygrana;
    do{
    	al_clear_to_color(al_map_rgb(0,0,0));
        runda = 0;
        gracz1 = 0;
        for (i=0;i<4;i++)
            gracz[i] = 0;
        wyjscie = 0;
        r = 1;
        i = 0;
        n = 0;
        printf("ZAJEBISTA GRA PYSI I STIXA - KOSCI");
        printf("\n1.Graj sam");
        printf("\n2.Graj z kolegami");
        printf("\n3.Wyjdz z gry");
        printf("\n\nWybierz tryb lub wyjdz z gry: ");
        scanf("%d",&tryb);
        switch(tryb){
            case 1:
                do{
                    al_clear_to_color(al_map_rgb(0,0,0));
                    if (gracz[0] != 0) printf("Uzbierane punkty: %d\n",gracz[0]);
                    printf("\n Runda %d",runda);
                    rzut(wynik);
                    przerzut(wynik);
                    gracz[0] = gracz[0] + punktacja(wynik,punkty);
                    runda++;
                    printf("\nCzy chcesz wrocic do menu glownego? (1) ");
                    scanf("%d",&wyjscie);
                }while (wyjscie != 1);
                if(wyjscie == 1){
                al_clear_to_color(al_map_rgb(0,0,0));
                break;
                }
            case 2:
                do{
                printf("Podaj liczbe graczy (2-4): ");
                scanf("%d",&ilegraczy);
                }while (ilegraczy <2 || ilegraczy >4);
                printf("Ile rund chcecie grac? ");
                scanf("%d",&rmax);
                while (rmax <1){
                    printf("Podaj liczbe rund rowna conajmniej 1: ");
                    scanf("%d",&rmax);
                }
                do{
                    al_clear_to_color(al_map_rgb(0,0,0));
                    for (n=0 ;n<ilegraczy;n++){
                        printf("Punkty gracza %d: %d\n",n+1,gracz[n]);
                    }
                    printf("\n Runda %d z %d",runda+1,rmax);
                    printf("\nTeraz rzuca gracz %d\n",i+1);
                    rzut(wynik);
                    przerzut(wynik);
                    gracz[i] = gracz[i] + punktacja(wynik,punkty);
                    if (r%ilegraczy == 0) runda++;
                    r++;
                    i++;
                    if (i>=ilegraczy) i=0;
                    if (runda == rmax){
                        scanf("%d",&i);
                        getchar();
                        al_clear_to_color(al_map_rgb(0,0,0));
                        puts("\nWyniki:\n");
                        for (i=0;i<ilegraczy;i++){
                            printf("Punkty gracza %d: %d\n",i+1,gracz[i]);
                        }
                        getchar();
                        break;
                    }
                    printf("\nCzy chcesz wrocic do menu glownego? (1) ");
                    scanf("%d",&wyjscie);
                }while (wyjscie != 1);
                if(wyjscie == 1){
                al_clear_to_color(al_map_rgb(0,0,0));
                break;
                }
                if (runda == rmax){
                    al_clear_to_color(al_map_rgb(0,0,0));
                    puts("\nWyniki:\n");
                        for (i=0;i<ilegraczy;i++){
                        printf("Punkty gracza %d: %d\n",i+1,gracz[i]);
                        }
                    getchar();
                    break;
                }

            case 3:
                al_clear_to_color(al_map_rgb(0,0,0));
                printf("Do zobaczenia!\n");
                getchar();
                break;
            default:
                al_clear_to_color(al_map_rgb(0,0,0));
                break;
        }

    }while (tryb != 3);
    return 0;
}

