/*7. Napisati program koji pomoću vezanih listi (stabala)
predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.
Točnije program treba preko menija simulirati korištenje DOS naredbi:
1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT_SIZE 50
//#define _CRT_SECURE_NO_WARNINGS

struct directory;
typedef struct directory* PositionInDirectory;
typedef struct directory//strukutra u kojoj su imena direktorija i njihovih siblinga
{
	char DirectoryName[MAX_LENGHT_SIZE];
	PositionInDirectory next;
	PositionInDirectory subDirectories;

}Directory;

struct CurrentLevelinStack;
typedef struct CurrentLevelinStack * CurrentPositionLevelStack;
typedef struct CurrentLevelinStack//strukutra kojom cu pamtit na kojoj se razini direktorija nalazim
{
	PositionInDirectory directorylevel;
	CurrentPositionLevelStack next;


}LevelStack;


PositionInDirectory createdirectory(char name[MAX_LENGHT_SIZE]);
PositionInDirectory createSubDirectory(char name[MAX_LENGHT_SIZE], PositionInDirectory currentDirectory);
PositionInDirectory changedirectory(char name[MAX_LENGHT_SIZE], PositionInDirectory currentDirectory);
CurrentPositionLevelStack CreateNewStackElement(CurrentPositionLevelStack newLeveleStackElement, PositionInDirectory currentlevelinDirectory);
PositionInDirectory popFronStack(PositionInDirectory headtLevelStack);

int pushOnStack(CurrentPositionLevelStack headLevelStack, PositionInDirectory currentlevelinDirectory);
int ListDirectoryItems(PositionInDirectory currentDirectory);

int main()
{
	
	//incijalizacija varijabli strukutra na 0
	Directory headDirectory =
	{
		.DirectoryName = {0},
		.subDirectories = NULL,
		.next = NULL
	};

	LevelStack headLevelStack =
	{
		.next = NULL,
		.directorylevel = NULL


	};

	int flagforNameSearch = 0;	
	PositionInDirectory rootDirectory = createdirectory("C:");//stvaram početni 'c' direktori, koji ce bit root za stablo
	headDirectory.next = rootDirectory;
	//Directory currentdir = headDirectory;
	PositionInDirectory currentDirectory = rootDirectory;
	pushOnStack(&headLevelStack, currentDirectory);// na stog smo dodali element korijena
	/*
	headLevelStack=pushOnStach(&headLevelStack, currentDirectory);// bi li mogao ovako pozvati ju?
	*/
	while (1)
	{
		printf("\nMenu:\n");
		printf("1 - md (Create Directory)\n");
		printf("2 - cd dir (Change Directory)\n");
		printf("3 - cd.. (Go Up)\n");
		printf("4 - dir (List Contents)\n");
		printf("5 - exit\n");

		int odabir;
		char DirName[MAX_LENGHT_SIZE];
		scanf_s("%d", &odabir);

		switch (odabir)
		{
	case 1:   //stvaranje novog direktorija
			puts("Enter name of your new directory ; ");
			scanf("%s", DirName);
			createSubDirectory(DirName, currentDirectory);
			;break;
	case 2:	//promjena direktorija
			if (rootDirectory->next == NULL)//provjera ako ne postoji nijedno stablo
			{
				puts("there are no any directory yet, first add some....");
				break;
			}
			puts("Enter name of your new directory ; ");
			scanf("%s", DirName);
		
			/*while (currentdir.next != NULL && flagforNameSearch == 0) //je li mogu ovako provjeraat da li postoji ime u stablu
			{
				if (strcmp(DirName, currentdir.DirectoryName) ==1 && flagforNameSearch == 0)
				{
					flagforNameSearch = 1;
					puts("\nIME POSTOJI...\n");
				}
				else
				{
					puts("\nIME  NE POSTOJI...\n"); break;

				}
				currentdir=*(currentdir.next);//jel se mogu kako drukcije snjim kretat kroz direktorije
			}

			*/
			currentDirectory=changedirectory(DirName, currentDirectory)
			; break;

	case 3://ulazak u direktroiji prije
			if (currentDirectory != rootDirectory)
			{
				currentDirectory = popFronStack(&headLevelStack);
				puts("succsassfully entered Directory, you are currently in %s", currentDirectory->DirectoryName);
				break;
			}
			else
			{
				puts("You are already in root, cant go up. ");
				break;

			}
			; break;
	case 4: //ispis
			if (headDirectory.next == NULL); break;//provjera da opce nema direktorija

			ListDirectoryItems(currentDirectory);//ako ima ispisi trenutne subdirektorije
			break;
		case 5://prekid petlje
			printf("Exiting the program.\n");
			break;
		
		default:
			printf("\033[0;31mInvalid choice. Please enter a valid option.\033[0m\n");
			break;
		}

		free(rootDirectory);
		return 0;
	}
}

PositionInDirectory createdirectory(char name[MAX_LENGHT_SIZE])
{
	PositionInDirectory newdirectory = NULL;
	newdirectory = (PositionInDirectory)malloc(sizeof(PositionInDirectory));//alocirana memorija za novi clan koji cu dodat na stog

	if (newdirectory == NULL)// provjera uspjesnosti stavrnaja direktorija
	{
		puts("can not make new directory");
		return NULL;// ako vracam null, pošto ne moze se napraviti novi, postavi ga na zadnji i ppokazivaj null


	}
	else
	{
		strcpy(newdirectory->DirectoryName, name);
		if (newdirectory->DirectoryName == 0)// provjera uspjesnosti postavljanja imena, je li ga mogu ovako usporedit s 0, posto je char,a inicijalizran je tako
		{
			puts(" problem with setting name of direcetory");
			return NULL;
		}
		else
		{

			newdirectory->next = NULL;
			newdirectory->subDirectories = NULL;//oba pokazivaca, na 0(trenutno posljendji)
			return newdirectory;
		}


	}



}
int ListDirectoryItems(PositionInDirectory currentDirectory)
{
	/*ispis svih pod direktorija odredenog direktorija*/
	printf("Contents of directory -- '%s' --\n", currentDirectory->DirectoryName);
	PositionInDirectory subdirectory = currentDirectory->subDirectories;
	while (subdirectory != NULL)
	{
		printf("- %s\n", subdirectory->DirectoryName);
		subdirectory = subdirectory->next;

	}
	if (currentDirectory->subDirectories == NULL)
	{
		printf("this directory is empty...\n");
	}

	return 0;

}
PositionInDirectory createSubDirectory(char name[MAX_LENGHT_SIZE], PositionInDirectory currentDirectory)
{
	PositionInDirectory newdirectory = NULL;
	newdirectory = createdirectory(name);
	if (newdirectory == NULL)
	{
		puts("You wasnt able to create new dir");
		return NULL;
	}
	newdirectory->next = currentDirectory->next;
	currentDirectory->next = newdirectory;
	return newdirectory;


}
PositionInDirectory changedirectory(char name[MAX_LENGHT_SIZE], PositionInDirectory currentDirectory)
{
	PositionInDirectory subdirectotry = currentDirectory->subDirectories;

	while (subdirectotry != NULL)
	{
		if (strcmp(name, subdirectotry->DirectoryName) == 0)
		{
			return subdirectotry;
		}
		subdirectotry = subdirectotry->next;
	}
	printf("Directory '%s' not found.\n", name);
	return currentDirectory;//ostaje nepromjenjen ako ga ne nademo
}
CurrentPositionLevelStack CreateNewStackElement(CurrentPositionLevelStack newLeveleStackElement, PositionInDirectory currentlevelinDirectory)
{

	newLeveleStackElement->directorylevel = currentlevelinDirectory;//postavi informaciju u kojem je direktoriju

	newLeveleStackElement->next = NULL;

	return newLeveleStackElement;
}
PositionInDirectory popFronStack(PositionInDirectory headtLevelStack)
{
	CurrentPositionLevelStack DeletingEleemnt = headtLevelStack->next;
	PositionInDirectory directorylevel = NULL;

	if (!DeletingEleemnt)
	{
		return NULL;
	}
	else
	{
		directorylevel = DeletingEleemnt->directorylevel;//predaje razinu 
		headtLevelStack->next = DeletingEleemnt->next;
		free(DeletingEleemnt);
		return directorylevel;

	}


}
int pushOnStack(CurrentPositionLevelStack headLevelStack, PositionInDirectory currentlevelinDirectory)
{
	CurrentPositionLevelStack newLeveleStackElement = NULL;//novi element na stogu
	if (!newLeveleStackElement) {
		puts("Can't allocate memory!\n");
		return NULL;
	}

	newLeveleStackElement = (CurrentPositionLevelStack)malloc(sizeof(CurrentPositionLevelStack));
	newLeveleStackElement = CreateNewStackElement(newLeveleStackElement, currentlevelinDirectory);

	//postavljanje pokzivaca stoga
	newLeveleStackElement->next = headLevelStack->next;
	headLevelStack->next = newLeveleStackElement;//elemenet dodan na vrh stoga LIFO
		
	return 0;
}
/*

CurrentPositionLevelStack pushOnStack(CurrentPositionLevelStack headLevelStack, PositionInDirectory currentlevelinDirectory)
{
	CurrentPositionLevelStack newLeveleStackElement = NULL;//novi element na stogu
	if (!newLeveleStackElement) {
		puts("Can't allocate memory!\n");
		return NULL;
	}

	newLeveleStackElement = (CurrentPositionLevelStack)malloc(sizeof(CurrentPositionLevelStack));
	newLeveleStackElement = CreateNewStackElement(newLeveleStackElement, currentlevelinDirectory);

	//postavljanje pokzivaca stoga
	newLeveleStackElement->next = headLevelStack->next;
	headLevelStack->next = newLeveleStackElement;//elemenet dodan na vrh stoga LIFO
		
	return headLevelStack;
}

*/