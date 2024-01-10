/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct stablo* Position;
typedef struct stablo
{
    int number;
    Position left;
    Position right;
}stablo;

Position insert(Position root, int value);
int replace(Position root);
void ispis(Position root);
int main()
{
    Position root = NULL;
    int casechose = 0;
    int NewNumber = 0;
    srand(time(NULL));
    while (1)
    {
        printf("Unesi koju radnju iduću želiš izvršiti?\n");
        printf("1 - Unesi novi element\n2 - Replace (sumiranje djece)\n3-ispis\n4-spremi to txt file");

        scanf("%d", &casechose);

        switch (casechose)
        {
        case 1:
            puts("broj automatski generiram...?");
            NewNumber = rand() % (90 - 10 + 1) + 10;
            root = insert(root, NewNumber); // Ažuriraj korijen nakon dodavanja novog elementa
            break;

        case 2:
            replace(root);
            break;

        case 3: ispis(root); break;
        case 4:
            SaveToTxtFile(root);
            printf("Stablo uspješno spremljeno u datoteku 'datoteka.txt'.\n");
            break;

        default:
            break;
        }
    }
}
Position CreateNewNode(int value)
{
    Position NewElement = (Position)malloc(sizeof(stablo));
    if (NewElement == NULL)
    {
        puts("Greška pri alokaciji memorije.");
        return NULL;
    }
    else
    {
        NewElement->left = NULL;
        NewElement->right = NULL;
        NewElement->number = value;
    }
    return NewElement;
}
Position insert(Position root, int value)
{
    if (root == NULL)
    {
        return CreateNewNode(value);
    }

    if (root->number < value)
    {
        root->right = insert(root->right, value);
    }
    else if (root->number > value)
    {
        root->left = insert(root->left, value);
    }

    return root;
}
int replace(Position root)
{
    int leftsum = 0;
    int rightSum = 0;
    int subtreeSum = 0;
    int currentValue = 0;

    if (root == NULL) {
        return 0; // Ako je čvor prazan, vraćamo 0.
    }

    // Rekurzivno pozivamo funkciju za lijevo i desno podstablo
    leftsum = replace(root->left);
     rightSum = replace(root->right);
     
    // Računamo sumu potomaka prije zamjene vrijednosti u tim potomcima
     subtreeSum = leftsum + rightSum;
    
    // Spremamo trenutnu vrijednost čvora
    currentValue = root->number;

    // Zamjenjujemo vrijednost čvora sa sumom potomaka
    root->number = subtreeSum;

    // Vraćamo sumu potomaka i trenutnu vrijednost čvora
  
    return subtreeSum + currentValue;
}
void ispis(Position root)
{
    //ispisat cu kao prereder
    if (root) {
        printf(" %d  ", root->number);
        ispis(root->left);
        ispis(root->right);
    }
  
}
int SaveToTxtFile(Position root) {
    FILE* filePointer = fopen("datoteka.txt", "w");
    if (filePointer == NULL) {
        printf("Greška pri otvaranju datoteke.\n");
        return 0;
    }

    // Inorder način upisa: lijevo, root, desno
    SaveToTxtFile(root->left, filePointer);
    fprintf(filePointer, "%d ", root->number);
    SaveToTxtFile(root->right, filePointer);

    fclose(filePointer);

    return 0; // Uspješno zapisano u datoteku
}
