#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/


#define NAMESIZE 50

typedef struct Person
{
	char [NAMESIZE];
	char surname[NAMESIZE];
	int age;
	struct Person* next;
} Person;

void Ispisliste(Person* head)
{
	while (head != NULL)
	{
		IspisClana(head);
		head = head->next;
	}
}

void IspisClana(Person* head)
{
	printf("%s %s %d\n", head->name, head->surname, head->age);
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
	Person* novaosoba = UnosElementa();

	if (head == NULL) {
		return novaosoba;
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

int main()
{
	int odabir = 0;
	Person* head = NULL;

	puts("unesi broj kojim zelis izvrsit radnju;\n1. ispisi listu\n2. dodaj element na pocetak liste\n3. dodaj element na kraj liste\n4. pretrazi listu po prezimen\n5. izbrisi cijelu listu");
	scanf("%d", &odabir);

	while (odabir >= 1 && odabir <= 5)
	{
		switch (odabir)
		{
		case 1: Ispisliste(head); break;
		case 2: head = DodajNaPocetak(head); break;
		case 3: head = DodajNaKraj(head); break;
		case 4: PronadiPoPrezimenu(head); break;
		case 5: head = IzbrisiListu(head); break;
		default:
			puts("opcija nije u izboru");
			break;
		}
		puts("Unesite novi broj za izvršenje određene radnje (ili bilo koji drugi broj za izlaz):\n");
		scanf("%d", &odabir);
	}
}
