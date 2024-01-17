#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE (30)
struct City;
typedef struct City* CityPosition;
struct City
{
	char ime[NAME_SIZE];
	int population;
	CityPosition next;
	CityPosition left;
	CityPosition right;

}city;
struct Country;
typedef struct Country *CountryPosition;
struct Country
{
	char ime[NAME_SIZE];
	CountryPosition next;
	CountryPosition left;
	CountryPosition right;
	CityPosition TownRootTrees;
	CityPosition townListHead;

}country;
CountryPosition CreateCountry(char* Name);
CityPosition CreateNewTown(char* TownName, int PopulationInTown);
CityPosition InsertSortedNewTownToList(CityPosition townListHead, CityPosition NewTownList);
CityPosition insertTowenAter(CityPosition CurrentTown, CityPosition NewTownList);
CityPosition insertNewTownTree(CityPosition TownRootTrees, CityPosition NewTown);
CountryPosition insertsorededCountryInList(CountryPosition HeadofCountryList, CountryPosition NewCountryList);
CountryPosition CountryAfter(CountryPosition currentElement, CountryPosition NewCountryList);
CountryPosition insertNewCountryInTree(CountryPosition CountryRootTree, CountryPosition NewCountryTree);
int printTownList(CityPosition townListHead);
CountryPosition FindCertainCountry(CountryPosition HeadofCountryList);
CountryPosition ReadandMakeCountriesfromBuffer(CountryPosition HeadofCountryList, CountryPosition CountryRootTree);
int CreateNewCountryfromBuffer(char* countryName, char* FileLocationTxt, CountryPosition* countries);
int PrintCountrylist(CountryPosition HeadofCountryList);
int PrintTownTree(CityPosition TownRootTrees);
int printCountryTree(CountryRootTree);
int main()
{
	CountryPosition HeadofCountryList=NULL;
	CountryPosition CountryRootTree = NULL;
	CountryPosition SerchedCountry = NULL;

	CountryRootTree=ReadandMakeCountriesfromBuffer(HeadofCountryList, CountryRootTree);
	//dodaj print country tree
	printCountryTree(CountryRootTree); puts("\n\n\n\n\n");
	//dodaj print country list
	PrintCountrylist(HeadofCountryList);

	//odlucit cu se da ju trazim u listi
	SerchedCountry=FindCertainCountry(HeadofCountryList);
	if(SerchedCountry!=NULL)
	printf("trazena zemlja postoji - %s", SerchedCountry->ime);

	return 0;

}
CountryPosition ReadandMakeCountriesfromBuffer(CountryPosition HeadofCountryList, CountryPosition CountryRootTree)
{
	CountryPosition countries[] = { NULL, NULL };
	char countryName[NAME_SIZE] = { 0 };
	char FileLocationTxt[NAME_SIZE] = { 0 };
	CountryPosition NewCountryList = NULL;
	CountryPosition NewCountryTree = NULL;


	FILE* filecountrypointer = NULL;
	filecountrypointer = fopen("drzave.txt", "r");
	if (filecountrypointer == NULL)return NULL;

	while (!feof(filecountrypointer))
	{
		fscanf(filecountrypointer, " %s %s", countryName, FileLocationTxt);
		CreateNewCountryfromBuffer(countryName,FileLocationTxt, countries);//pdmah moram i stablo napravit
			 NewCountryTree = countries[1];//element koji je vracen iz gornje funkcije, i pokaziva na novi element za dodavanje u stablo
			 NewCountryList= countries[0];// -//- slicno, samo sluzi za dodavanje listu
		insertsorededCountryInList(HeadofCountryList, NewCountryList);
		CountryRootTree = insertNewCountryInTree(CountryRootTree, NewCountryTree);
	}
	fclose(filecountrypointer);
	return CountryRootTree;

}
int CreateNewCountryfromBuffer(char *countryName, char *FileLocationTxt, CountryPosition *countries)
{
	char Filename[NAME_SIZE] = { 0 };
	int PopulationInTown = 0;
	char TownName[NAME_SIZE] = { 0 };

	CityPosition NewTownList = NULL;
	CityPosition NewTown = NULL;

	CountryPosition NewCountryList = NULL;
	CountryPosition NewCountryTree = NULL;


	strcpy(	Filename,FileLocationTxt);
	FILE* towntxtpointer = NULL;
	towntxtpointer = fopen(Filename, "r");
	if ( towntxtpointer == NULL)return 0;


	NewCountryList = CreateCountry(countryName);//novi element za dodat u listu a
	NewCountryTree = CreateCountry(countryName);//novi element za dodatr u stablo gradova b


	while (!feof(Filename))
	{
		fscanf(Filename, "%s %d", TownName, &PopulationInTown);

		//stvaram element Grada za dodati u listu i u stablo te ga unosim sortirano u listu i u stablo
		NewTownList = CreateNewTown(TownName, PopulationInTown);
		NewTown = CreateNewTown(TownName, PopulationInTown);

		InsertSortedNewTownToList(NewCountryTree->townListHead, NewTownList);
		NewCountryList->TownRootTrees = insertNewTownTree(NewCountryList->TownRootTrees, NewTown);

	}
	countries[0] = NewCountryList;
	countries[1] = NewCountryTree;

	return 0;
}
CountryPosition CreateCountry(char *Name)
{
	CountryPosition	NewCountryElement = NULL;
	NewCountryElement = (CountryPosition)malloc(sizeof(country));
	if (NewCountryElement == NULL)return 0;

	strcpy(NewCountryElement->ime, Name);
	NewCountryElement->left =NULL;
	NewCountryElement->right = NULL;
	NewCountryElement->next =NULL;
	NewCountryElement->TownRootTrees =NULL;

	NewCountryElement->townListHead->population = 0;
	NewCountryElement->townListHead->left = NULL;
	NewCountryElement->townListHead->right = NULL;
	NewCountryElement->townListHead->next = NULL;
	return NewCountryElement;

}
CityPosition CreateNewTown(char* TownName,int PopulationInTown)
{
	CityPosition NewTownElement = NULL;
	NewTownElement = (CityPosition)malloc(sizeof(city));
	if (NewTownElement == NULL)return 0;

	strcpy(NewTownElement->ime, TownName);
	NewTownElement->population = PopulationInTown;
	NewTownElement->left = NULL;
	NewTownElement->next = NULL;
	NewTownElement->right = NULL;
	return NewTownElement;
}
CityPosition InsertSortedNewTownToList(CityPosition townListHead, CityPosition NewTownList)
{
	//sortirani unos u listu
	//sortiramo zavisno n abroj stanovnika, od najeveceg do najmanjeg
	if (townListHead == NULL)
	{
		//lista gradova je prazna, dodaj je na pocetka
		return NewTownList;
	}
	CityPosition CurrentTown = townListHead;

	while (CurrentTown->next != NULL && CurrentTown->next->population > NewTownList->population)
	{
		CurrentTown = CurrentTown->next;
	}
	insertTowenAter(CurrentTown, NewTownList);

	return NULL;

}
CityPosition insertTowenAter(CityPosition CurrentTown, CityPosition NewTownList)
{
	NewTownList->next = CurrentTown->next;
	CurrentTown->next = NewTownList;
	return 0;


}
CityPosition insertNewTownTree(CityPosition TownRootTrees, CityPosition NewTown)
{
	//sortirani unos u stablo
	if (TownRootTrees == NULL)
	{
		//lista je prazna dodaj na pocetak strabla ili smo dosli do krajnejeg elementa
		return NewTown;
	}
	if (NewTown->population < TownRootTrees->population)
	{
		TownRootTrees->left=insertNewTownTree(TownRootTrees->left, NewTown);
	}
	if (NewTown->population > TownRootTrees->population)
	{
		TownRootTrees->right = insertNewTownTree(TownRootTrees->right, NewTown);
	}

	return TownRootTrees;


}
CountryPosition insertsorededCountryInList(CountryPosition HeadofCountryList, CountryPosition NewCountryList)
{
	CountryPosition currentElement = HeadofCountryList;

	while (currentElement->next != NULL && strcmp(currentElement->next->ime, NewCountryList->ime) == 0);
	{
		currentElement = currentElement->next;
	}
	CountryAfter(currentElement, NewCountryList);

	return NULL;
}
CountryPosition CountryAfter(CountryPosition currentElement, CountryPosition NewCountryList) {
NewCountryList->next= currentElement->next;
currentElement->next = NewCountryList;
return NULL;
}
CountryPosition insertNewCountryInTree(CountryPosition CountryRootTree, CountryPosition NewCountryTree)
{
	if (CountryRootTree == NULL)
	{
		return NewCountryTree;

	}
	if (strcmp(CountryRootTree->ime, NewCountryTree->ime)<0)
	{
		CountryRootTree->left=insertNewCountryInTree(CountryRootTree->left, NewCountryTree);
	}

if (strcmp(CountryRootTree->ime, NewCountryTree->ime) >0)
{
	CountryRootTree->right = insertNewCountryInTree(CountryRootTree->right, NewCountryTree);
}

return CountryRootTree;

}
int printCountryList(CountryPosition HeadofCountryList)
{
	CountryPosition CurrentElement = HeadofCountryList->next;
	if (CurrentElement == NULL)
	{
		puts("ispis se ne moze izvrsiti, lista je prazna");
		return 0;
	}
	//ispis ide- ime drzave- svi gradovi i broj stan-, pa nova drzava...
	while (CurrentElement != NULL)
	{
		printf("ime drzave: %s\n", CurrentElement->ime);
		PrintTownTree(CurrentElement->TownRootTrees);
		CurrentElement = CurrentElement->next;

	}


	return 0;

}
int PrintTownTree(CityPosition TownRootTrees)
{
	//ispis radim kao inorder
	if (TownRootTrees)
	{
		PrintTownTree(TownRootTrees->left);
		printf("\t\t%s\t\t %d", TownRootTrees->ime, TownRootTrees->population);
		PrintTownTree(TownRootTrees->right);

	}
	return 0;
}
int printCountryTree(CountryPosition CountryRootTree)
{
	if (CountryRootTree)
	{
		printCountryTree(CountryRootTree->left);
		printf("ime drzave - %s", CountryRootTree->ime);
		printTownList(CountryRootTree->townListHead);
		printCountryTree(CountryRootTree->right);


	}
	return 0;
}
int printTownList(CityPosition townListHead)
{
	CityPosition CurrentElement = townListHead;

	while (CurrentElement != NULL)
	{
		printf("\t\t\t%s\t\t%d\n", CurrentElement->ime,CurrentElement->population);
		CurrentElement = CurrentElement->next;

	}

	return 0;

}
CountryPosition FindCertainCountry(CountryPosition HeadofCountryList)
{
	char CountryName[NAME_SIZE] = { 0 };
	CountryPosition CurrentElement = HeadofCountryList;

	puts("Unesite ima trazene drzave");
	scanf("%s", CountryName);

	while (CurrentElement!=0 && strcmp(CurrentElement->ime,CountryName)!=0)
	{
		CurrentElement = CurrentElement->next;
	}
	if (strcmp(CurrentElement->ime, CountryName) == 0)
		return CurrentElement;
	else {
		puts("države nema na listi...\n");
		return NULL;
	}

}