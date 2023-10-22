
#include <stdio.h>
#include <stdlib.h>
/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci.+
Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) +
i učitati iz datoteke sve zapise.
Na ekran ispisati ime, prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/



#define VELICINAIMENA 50
#define max_br_bodova 10
#define ERROR 1

typedef struct student {
    char name[VELICINAIMENA];
    char surname[VELICINAIMENA];
    int points;
} stud;

float relativanBrojBodova(int brojbodova) {
    return (float)(brojbodova / max_br_bodova) * 100;
}

void ispisElemenata(stud* lista, int NumberOfPerson) {
    // Ispis podataka s relativnim brojem bodova po zadanoj formuli
    for (int i = 0; i < NumberOfPerson; i++) {
        printf("%s %s %d, rel. broj bodova %.2f\n", lista[i].name, lista[i].surname, lista[i].points, relativanBrojBodova(lista[i].points));
    }
}

int main() {
    FILE* filePointer = fopen("popis.txt", "r");
    if (filePointer == NULL) {
        printf("Pogreška pri otvaranju datoteke.\n");
        return ERROR;
    }

    int NumberOfPerson = 0;
    char line[200];
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        NumberOfPerson++; // Kad dođete do kraja linije, povećate broj ljudi u listi
    }
    rewind(filePointer); // Vratite pokazivač datoteke na početak

    stud* lista;
    lista = (stud*)malloc(sizeof(stud) * NumberOfPerson); // Dinamički alocirana memorija za n ljudi s popisa
    if (lista == NULL) {
        printf("Pogreška pri alociranju memorije.\n");
        fclose(filePointer);
        return ERROR;
    }

    // Unos podataka o osobama s liste
    for (int i = 0; i < NumberOfPerson; i++) {
        if (fscanf(filePointer, "%s %s %d", lista[i].name, lista[i].surname, &lista[i].points) != 3) {
            printf("Pogreška prilikom čitanja iz datoteke.\n");
            fclose(filePointer);
            free(lista);
            return ERROR;
        }
    }
    fclose(filePointer); // Zatvaranje datoteke, više nam nije potrebna

    // Ispis podataka s relativnim brojem bodova po zadanoj formuli
    ispisElemenata(lista, NumberOfPerson);

    // Dealociranje zauzete memorije
    free(lista);

    return 0;
}

