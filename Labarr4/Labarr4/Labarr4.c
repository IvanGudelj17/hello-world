/*Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Element;
typedef struct Element* Position;
typedef struct Element
{
	int coefficient;
	int exponent;
	Position next;
} Element;

int readFile(Position headPoly1, Position headPoly2, char *fileName);
int ParseStringInToList(Position headPoly, char buffer);
int InsertSorted(Position headPoly, Position newElement);
Position CreateElement(int koificijent, int exponent);
int MergeAfeter(Position CurrentElement, Position newElement);
int InsertAfter(Position CurrentElement, Position newElement);
int DeleteElement(Position CurrentElement);
int freeMemory(Position head);
int readFile(Position headPoly1, Position headPoly2, char* fileName);
int printPoly(char* polynomeName, Position first);


int addPoly(Position resultHead, Position firstElementPoly1, Position firstElementPoly2);
int multiplyPoly(Position resultHead, Position firstElementPoly1, Position firstElementPoly2);

int main()
{

	Element headPoly1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headPoly2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headPolyAdd = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headPolyMultiply = { .coefficient = 0, .exponent = 0, .next = NULL };
	char* fileName = "polynomes.txt";//ime datoteke iz koje citam podatke
	//tako sam je zada, da je mogu korsitit u daljnim funkcijama

	if (readFile(&headPoly1, &headPoly2, fileName) == 0) //ako se read file izvrsi do kraja, vraća 0..
	{

		printPoly("First polynome: ", headPoly1.next);
		printPoly("Second polynome: ", headPoly2.next);

		addPoly(&headPolyAdd, headPoly1.next, headPoly2.next);
		multiplyPoly(&headPolyMultiply, headPoly1.next, headPoly2.next);

		printPoly("Added polynome: ", headPolyAdd.next);
		printPoly("Multiplied polynome: ", headPolyMultiply.next);


		//oslobadanje memeorije
		freeMemory(&headPoly1);
		freeMemory(&headPoly2);
		freeMemory(&headPolyAdd);
		freeMemory(&headPolyMultiply);
	
	
	}

	//freeMemory(&headPoly1);
	//freeMemory(&headPoly2);
	return 0;
}

int printPoly(char* polynomeName, Position first) {
	printf(" %s", polynomeName);
	if (first != NULL) {
		if (first->exponent < 0) {
			if (first->coefficient == 1) {
				printf("x^(%d)", first->exponent);
			}
			else {
				printf("%dx^(%d)", first->coefficient, first->exponent);
			}
		}
		else {
			if (first->coefficient == 1) {
				printf("x^%d", first->exponent);
			}
			else {
				printf("%dx^%d", first->coefficient, first->exponent);
			}
		}

		first = first->next;
	}

	for (; first != NULL; first = first->next) {
		if (first->coefficient < 0) {
			if (first->exponent < 0) {
				printf(" - %dx^(%d)", first->coefficient, first->exponent);
			}
			else printf(" - %dx^%d", first->coefficient, first->exponent);
		}
		else {
			if (first->exponent < 0) {
				if (first->coefficient == 1) {
					printf(" + x^(%d)", first->exponent);
				}
				else {
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
				}
			}
			else {
				if (first->coefficient == 1) {
					printf(" + x^%d", first->exponent);
				}
				else {
					printf(" + %dx^%d", first->coefficient, first->exponent);
				}
			}
		}
	}

	printf("\n");
	return 1;
}


int addPoly(Position resultHead, Position firstElementPoly1, Position firstElementPoly2) {
	Position currentPoly1 = firstElementPoly1;
	Position currentPoly2 = firstElementPoly2;
	Position currentResult = resultHead;//lista umnozaka polinoma
	Position remainingPoly = NULL;

	while (currentPoly1 != NULL && currentPoly2 != NULL) {
		if (currentPoly1->exponent == currentPoly2->exponent) //ako su jednaki zbroji koif i stavi im exp zajednicki
		{
			createAndInsertAfter(currentPoly1->coefficient + currentPoly2->coefficient, currentPoly1->exponent, currentResult);
			currentPoly1 = currentPoly1->next;
			currentPoly2 = currentPoly2->next;
			currentResult = currentResult->next;//micemo se na iduci par poolinoma
		}
		else if (currentPoly1->exponent < currentPoly2->exponent) 
		{
			createAndInsertAfter(currentPoly1->coefficient, currentPoly1->exponent, currentResult);
			//ako je jedan clan manji od drugog, taj se moze autoamatski dodat na konacnu listu, jer nece bit onog koji ima exp ka oon
			currentPoly1 = currentPoly1->next;
			currentResult = currentResult->next;
		}

		else if (currentPoly1->exponent > currentPoly2->exponent) {
			//ako je jedan clan manji od drugog, taj se moze autoamatski dodat na konacnu listu, jer nece bit onog koji ima exp ka oon
			createAndInsertAfter(currentPoly2->coefficient, currentPoly2->exponent, currentResult);
			currentPoly2 = currentPoly2->next;
			currentResult = currentResult->next;
		}
	}
	//ako smo izaslii iz liste, mozda smo jer je jedna poly lista gotova pa;
	if (currentPoly2 == NULL) //poastavljam pokazivac trenunte liste za remaining pa cu snjim ic do kraja
	{
		remainingPoly = currentPoly1;
	}
	else  //poastavljam pokazivac trenunte liste za remaining pa cu snjim ic do kraja 
	{
		remainingPoly = currentPoly2;
	}

	while (remainingPoly != NULL)
	{//dodaji preostalne elemente na kraj liste
		createAndInsertAfter(remainingPoly->coefficient, remainingPoly->exponent, currentResult);
		remainingPoly = remainingPoly->next;
		currentResult->next;
	}

	return 1;
}
int multiplyPoly(Position resultHead, Position firstElementPoly1, Position firstElementPoly2) {

	if (firstElementPoly1 != NULL || firstElementPoly2 != NULL) {
	for (Position currentPoly1 = firstElementPoly1;    currentPoly1 != NULL;      currentPoly1 = currentPoly1->next) {
	for (Position currentPoly2 = firstElementPoly2;    currentPoly2 != NULL;     currentPoly2 = currentPoly2->next) {
	Position newElement = createElement(currentPoly1->coefficient * currentPoly2->coefficient, currentPoly1->exponent * currentPoly2->exponent);

				if (newElement == NULL) 
				{
					return EXIT_FAILURE;
				}

				InsertSorted(resultHead, newElement);//novi element prosljedi da se doda nakon
			}
		}
	}
	return 0;
}


int freeMemory(Position head) {

	Position current = head;

	while (current->next != NULL) {
		deleteAfter(current);
	}

	return 1;
}
int readFile(Position headPoly1, Position headPoly2, char *fileName)
{
	
	char buffer[100] = { 0 };
	FILE* filePointer = fopen(fileName, "r");

	int status = 0;
	if (filePointer == NULL)
	{
		puts("U have a problem with file opening...\n");
		return 1;
	}

	fgets(buffer, sizeof(buffer), filePointer);
	status = ParseStringInToList(headPoly1, buffer);
	if (status != 0)
	{
		puts("greska prilikom prelaska u parse");
		return 1;
	}
	fgets(buffer, sizeof(buffer), filePointer);
	status = ParseStringInToList(headPoly2, buffer);
	if (status != 0)
	{
		puts("greska prilikom prelaska u parse");
		return 1;

	}
	


	fclose(filePointer);
	return 0;

}
int ParseStringInToList(Position headPoly, char buffer)
{
	char* currentBuffer = buffer;
	int exponent = 0;
	int koificijent = 0;
	int status = 0;
	int NumberOfMouvedBytes = 0;

	Position newElement = NULL;
	


	while (strlen(currentBuffer) > 0) {
		//citanje podataka iz datoteke
		status = sscanf(" %dx^%d %n", &koificijent, &exponent, &NumberOfMouvedBytes);
		if (status != 2)
		{
			puts("error with reading from file");
			return 1;
		}

		newElement = CreateElement(koificijent, exponent);
		if (newElement == NULL) {
			return 1;
		}

	
		InsertSorted(headPoly, newElement);
		currentBuffer += NumberOfMouvedBytes;
	}
	return 0;

}
Position CreateElement(int koificijent, int exponent)
{
	Position newelement=NULL;
	newelement = (Position)malloc(sizeof(Element));
	if (newelement == NULL)
	{
		puts("u fucked dynamaic allocation of newwlwwmnr");

	}
	newelement->coefficient = koificijent;
	newelement->exponent = exponent;
	newelement->next = NULL;



	return newelement;
}
int InsertSorted(Position headPoly, Position newElement)
{
	Position CurrentElement = headPoly;

	//sve dok lista ili nije prazna ili je exponent iduceg clana veci od exp novovg elementa, idi dalje po listi
	while (CurrentElement->next != NULL && (CurrentElement->next->exponent > CurrentElement->exponent))
	{
		CurrentElement = CurrentElement->next;
	}
	 
	MergeAfeter(CurrentElement, newElement);//kad sam dosao na clan koji ima ex manji ili jednak novom, procjenjivam kakav je pa ga dodajem
	return 0;
}
int MergeAfeter(Position CurrentElement, Position newElement)
{
	if (CurrentElement->next == NULL || CurrentElement->next->exponent != CurrentElement->exponent)
	{
		InsertAfter(CurrentElement, newElement);
		//ako je novi el za na kraj liste, ili je razl od trenutnog
	}
	else
	{
		int sumofcoifficient = 0;
		sumofcoifficient = CurrentElement->next->exponent + CurrentElement->exponent;
		if (sumofcoifficient == 0)
		{
			DeleteElement(CurrentElement);//ako u zbroju dobijemo da se radi o suprotnim brojevima, cal se brise s liste(coif=0)
		}
		else {
			CurrentElement->next->exponent = sumofcoifficient;
			free(newElement);
			//ako se koif promjenio, ne trbea nam novi clan liste, nec samo promejnit koif postojeceg
		}
	}
	return 0;
}
int InsertAfter(Position CurrentElement, Position newElement)
{
	newElement->next = CurrentElement->next;
	CurrentElement->next = newElement;
	return 0;

}
int DeleteElement(Position CurrentElement)
{
	Position ToDelete = CurrentElement->next;
	CurrentElement->next = ToDelete->next;
	free(ToDelete);
	return 0;
}
int createAndInsertAfter(int coefficient, int exponent, Position current) {
	Position newElement = createElement(coefficient, exponent);

	if (newElement == NULL) {
		return EXIT_FAILURE;
	}

	insertAfter(current, newElement);

	return 0;
}