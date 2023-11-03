#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAMESIZE 50

/*3.
Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,+
B. dinamički dodaje novi element ispred određenog elementa,+
C. sortira listu po prezimenima osoba,-
D. upisuje listu u datoteku,+
E. čita listu iz datoteke.+
*/
typedef struct Person
{
	char name[NAMESIZE];
	char surname[NAMESIZE];
	int age;
	struct Person* next;
} Person;

void IspisClana(Person* head);
void Ispisliste(Person* head);
void UpisiUlistu(Person* head);
Person* UnosElementa();
Person* DodajNaPocetak(Person* head);
Person* DodajNaKraj(Person* head);
void PronadiPoPrezimenu(Person* head);
Person* IzbrisiListu(Person* head);
Person* DodajNakon(Person* head);
Person* DodajIspred(Person* head);
Person* UcitajizDatoteke(Person* head);
void PocetniMenu(int* odabir);
int main()
{
	Person = { " "," ",'0', NULL };//postavljanje vrijednosti na 0
	int odabir = 0;
	Person* head = NULL;
	PocetniMenu(&odabir);


	while (odabir >= 1 && odabir <= 9)
	{
		switch (odabir)
		{
		case 1: Ispisliste(head); break;
		case 2: head = DodajNaPocetak(head); break;
		case 3: head = DodajNaKraj(head); break;
		case 4: PronadiPoPrezimenu(head); break;
		case 5: head = IzbrisiListu(head); break;
		case 6: head = DodajNakon(head); break;
		case 7: head = DodajIspred(head); break;
		case 8: UpisiUlistu(head); break;
		case 9: head = UcitajizDatoteke(head); break;

		default:
			puts("opcija nije u izboru");
			break;
		}

		puts("Unesite novi broj za izvršenje određene radnje (ili bilo koji drugi broj za izlaz):\n");
		scanf("%d", &odabir);
	}
}

void IspisClana(Person* head)
{
	printf("%s %s %d\n", head->name, head->surname, head->age);
}

void Ispisliste(Person* head)
{
	while (head != NULL)
	{
		IspisClana(head);
		head = head->next;
	}
}

void UpisiUlistu(Person* head)
{
	FILE* FilePointer = fopen("popis.txt", "w");
	if (FilePointer == NULL)
	{
		puts("nemouce otvorit datoetku\n..");
		return;
	}

	while (head != NULL)
	{

		fprintf(FilePointer, "%s %s  %d\n", head->name, head->surname, head->age);//upis strukutre po strukutru sve dok Vezna Lista ne dode do kraja


		head = head->next;
	}

	fclose(FilePointer);
	puts("Upisi obavljen");
}

Person* UnosElementa()
{
	Person* novaosoba = (Person*)malloc(sizeof(Person));
	if (novaosoba == NULL)
		return NULL;

	printf("unes ime:");     scanf("%s", novaosoba->name);
	printf("unes prezime:"); scanf("%s", novaosoba->surname);
	printf("unes godine:");  scanf("%d", &novaosoba->age);
	novaosoba->next = NULL;
	return novaosoba;
}

Person* DodajNaPocetak(Person* head)
{
	Person* novaosoba = UnosElementa();
	novaosoba->next = head;
	head = novaosoba;

	return head;
}

Person* DodajNaKraj(Person* head) {
	
	Person* novaosoba = UnosElementa();//unosim podatke za novu osobu i postavljam njen next=NULL
	if (head == NULL)
	{
		return novaosoba;//ako je lista prazna vrati novu osobu na head
		
	}

	
	Person* current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = novaosoba;
	return head;
}

void PronadiPoPrezimenu(Person* head)
{
	char wantedSurname[NAMESIZE];
	puts("unesi prezime zeljenog clana\n");
	scanf("%s", wantedSurname);

	while (head != NULL)
	{
		if (strcmp(wantedSurname, head->surname) == 0)
		{
			IspisClana(head);
			return;
		}
		head = head->next;
	}
	puts("clan nije pronaden na listi");
}

Person* IzbrisiListu(Person* head)
{
	while (head != NULL)
	{
		Person* temp = head;
		head = head->next;
		free(temp);
	}

	return NULL;
}

Person* DodajNakon(Person* head)
{
	Person* current = head;//trebam pomocni pokazivac za doci do listi do mjesta prije nego gdej trebam izvrsit dodavanje
	if (current == NULL)
	{
		puts("lista je prazna, dodaj prvi clan prvo");
		return head;
	}

	Person* novaOsoba = (Person*)malloc(sizeof(Person));
	if (novaOsoba == NULL) { puts("greska pri alokaciji nove osobe"); return head; }

	int clanprije;
	puts("nakon kojeg clana zelite dodati novi clan"); scanf("%d", &clanprije);
	puts("unesite podatke o novom clanu\n"); novaOsoba = UnosElementa();


	int i = 0;
	while (i < clanprije - 1)//Posto se dodaje clan nakon moram doci do clana prije.
	{
		current = current->next;
		if (current == NULL)
		{
			puts("izbarali ste mmjesto izvan ranga liste"); return head;

		}
		i++;

	}


	novaOsoba->next = current->next;//slazem pokazivace next tako da se povezu pravilno
	current->next = novaOsoba;

	return head;

}

Person* DodajIspred(Person* head)
{
	Person* current = head;
	if (current == NULL) {
		puts("Vaša lista je prazna, prvo dodajte neke članove");
		return head;
	}

	puts("Prije kojeg člana želite dodati novog člana?\n");
	int clan;
	scanf("%d", &clan);

	if (clan == 1) {
		// Ako treba dodati ispred prvog člana, pozovam samo DodajNaPocetak
		return DodajNaPocetak(head);
	}

	// Alocirajte memoriju za novog člana i unesite podatke
	Person* novaosoba = UnosElementa();
	if (novaosoba == NULL) {
		puts("Greška pri alociranju nove osobe");
		return head;
	}

	int i = 0;
	while (i < clan - 2) {
		if (current->next == NULL) {
			puts("Taj član ne postoji na listi, unesite nešto unutar raspona liste");
			free(novaosoba); // Oslobađa memoriju ako član ne postoji
			return head;
		}
		current = current->next;
		i++;
	}

	novaosoba->next = current->next;
	current->next = novaosoba;

	return head;
}

Person* UcitajizDatoteke(Person* head) {

	FILE* FilePointer = fopen("popis.txt", "r");
	if (FilePointer == NULL) {
		puts("Datoteka nije uspješno otvorena");
		return NULL;
	}

	char name[NAMESIZE];
	char surname[NAMESIZE];
	int age;

	Person* kraj = NULL;

	while (fscanf(FilePointer, "%s %s %d", name, surname, &age) != EOF)//FSCAF CE VRACAT 3 SVE DOK SE USPJESNO UCITAJE, INACE (-1) STO JE=EOF 
	{
		Person* NovaOsoba = (Person*)malloc(sizeof(Person));
		if (NovaOsoba == NULL) {
			puts("Nova osoba nije stvorena");
			fclose(FilePointer);
			free(NovaOsoba);
			return NULL;
		}

		strcpy(NovaOsoba->name, name);
		strcpy(NovaOsoba->surname, surname);
		NovaOsoba->age = age;
		NovaOsoba->next = NULL;

		if (head == NULL)
		{//ako je lista prazna i dodajemo tek prvi clan, oba pokazauju na njega.
			head = NovaOsoba;
			kraj = NovaOsoba;
		}
			else 
		{//svaki iduci, kraj postavljemo na njega da mozemo idalj dodavta na kraj.
			kraj->next = NovaOsoba;
			kraj = NovaOsoba;//pomicem pomocni pokazivac kraj na kraj liste, da bude spreman za novo dodvanje na kraj
		}
	}

	fclose(FilePointer);

	return head;
}


void PocetniMenu(int* odabir)
{


	puts("unesi broj kojim zelis izvrsit radnju;\n1. ispisi listu\n2. dodaj element na pocetak liste\n3. dodaj element na kraj liste\n4. pretrazi listu po prezimen\n5. izbrisi cijelu listu\n 6.dodaj clana nakon");
	puts("\n7. dodaj ispred clana\n8. upisi lstu u datoteku\n9. ucitaj listu iz datoteke");
	scanf("%d", odabir);


}
