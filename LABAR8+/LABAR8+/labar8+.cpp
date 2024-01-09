/*Napisati program koji omogućava rad s binarnim stablom pretraživanja.
Treba omogućiti unošenje novog elementa u stablo, ispis elemenata(inorder, preorder, postorder i level order),
brisanje i pronalaženje nekog elementa* /
*/
#include <stdio.h>
#include <stdlib.h>
//#define _CRT_SECURE_NO_WARNINGS

struct node;
typedef struct node* Position;
typedef struct node
{
	int number;
	Position right;
	Position left;


}Node;


Position  CreateNode(int value);
int preorder(Position root);
int postorder(Position root);
int inorder(Position root);
Position insert(Position root, int value);
Position trazi(int broj, Position root);
int levelOrder(Position root);
Position DeleteCertainElement(int value, Position root);


int main()
{

	int menuchoose = 0;
	Position root = NULL;
	Position resulut = NULL;
	int broj=0;
	printf("enter root value");
	int value = 0;
	scanf("%d", &value);
	root = insert(root, value);//postavlljanje vrijednosti na root stabla

	while (1)
	{

		puts("\n..... Menu opened .....\n");
		printf("1 - Insert node\n");
		printf("2 - Print preorder\n");
		printf("3 - Print inorder\n");
		printf("4 - Print postorder\n");
		printf("5 - NADJI ELEMENT\n");

		printf("7 - exit\n");
		puts("\n enter number - "); scanf("%d", &menuchoose);
		switch (menuchoose)
		{
		case 1://obicni unos elementa, koji se postavlja gdje triba u stablu
			puts("\n enter number "); scanf("%d", &value);
			insert(root, value); break;

		case 2: puts("preorder sort - "); preorder(root); break;
		case 3:puts("inorder sort - "); inorder(root); break;
		case 4: puts("postorder sort - "); postorder(root); break;
		case 5: 
			puts("koji element zelite pretrazit u stablu?");
			scanf("%d", &broj);
			resulut = trazi(broj, root);
			if (resulut!=NULL)
			{
				puts("vas broj postoji u stablu!");
			}
			else
			{
				puts("vas broj NE postoji u stablu!");
			}; break;
		case 6: puts("level order - "); levelOrder(root); break;
		case 7:
			puts("koji element zelite izbrisat iz stabla? ");
				scanf("%d", &broj);
			root =	DeleteCertainElement(broj, root);
			; break;
		case 8: puts("exit mode - "); return 0; break;

		default:
			break;
		}

	}

}


Position insert(Position root, int value) {
	if (root == NULL)
		return CreateNode(value);

	if (value < root->number)
		root->left = insert(root->left, value);
	else if (value >= root->number)
		root->right = insert(root->right, value);

	return root;
}
Position  CreateNode(int value)
{
	Position node = NULL;
	node = (Position)malloc(sizeof(Node));
	if (node == NULL)
	{
		puts("can not allocate memory for new node...");
		return NULL;
	}

	node->number = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}
int preorder(Position root)
{
	if (root != NULL)
	{

		//korijen, lijeva strana, desna strana
		printf("%d", root->number);
		preorder(root->left);
		preorder(root->right);
	}
	return 0;
}
int postorder(Position root)
{
	if (root != NULL)
	{
		//lijeva strana, desna strana, korijen
		preorder(root->left);
		preorder(root->right);
		printf("%d", root->number);
	}
	return 0;
}
int inorder(Position root)
{
	if (root != NULL)
	{
		//lijeva strana, root, desna strana
		preorder(root->left);
		printf("%d", root->number);
		preorder(root->right);

	}
	return 0;
}
Position trazi(int SearchedNumber, Position root)
{
	if (root == NULL)
	{
		return NULL;//ako je lista prazna, vrati NULL-elementa nema u listi sigutrno
	}
	if (root->number < SearchedNumber)
	{
		root->right = trazi(SearchedNumber, root->right);
	}
	if (root->number > SearchedNumber)
	{
		root->left = trazi(SearchedNumber, root->left);
	}
	return root;

}
int levelOrder(Position root) 
{
	if (root == NULL)
		return 0;//na kraju vrati nula(trash) ionako je bitan samo ispis

	Position queue[100] = { 0 };//ovo nema smisla probavat implementirati  stog preko liste..?
	int front = 0, rear = 0;

	queue[rear++] = root;//stvaramo kopiju roota na prvi element niza, koji sad pokaziva gdje i root.

	while (front < rear) //ovaj uvjet omogucit ce izvodenje do zadnjeg elementa, ali i omogucit ulazak u iduce dubine stabla
	{
		Position current = queue[front++];

		printf("%d ", current->number);

		//u ova dva if-a se lijevo pa desno dijete dodaju na stog
		if (current->left != NULL)
			queue[rear++] = current->left;

		if (current->right != NULL)
			queue[rear++] = current->right;
	}
	return EXIT_SUCCESS;
}
Position DeleteCertainElement(int value, Position root)
{
	//prvo moram doc do elementa kojeg zelim izbrisat -value
	if (root == NULL)
		{
			puts("vasa lista je prazna...");
			return NULL;
		}
	if (value > root->number)
		{
		root->right = DeleteCertainElement(value, root->right);
		}

	else if (value < root->number)
		{
		root->left = DeleteCertainElement(value, root->left);
		}

	//sad se nalazimo na tom elementu sigurno, sad mu treba provjerit broj djece
    //prvo laksi slucaj brisanja i zamjene, ako ima 1 ili nijedno djete
	else
	{
		if (root->left == NULL && root->right != NULL)
		{
			Position temp = root->right;
			free(root);
			return temp;
		}
		if (root->right == NULL && root->left != NULL)
		{
			Position temp = root->left;
			free(root);
			return temp;
		}

		//ako ima oba djeteta, nijedan mu pokazivac ne pokaziva na NULL, pa je to odvojeni usecase
		//zamjenit ce mo tazenu vrijednsot(vrh privjeska) sa najmanjim elementom na adesnoj strani.
		Position temp = root->right;
		while (temp->left != NULL)
		{
			temp = temp->left;
		}
		root->number = temp->number;
		//i samo jos obrisaat taj isti element s dna stabla(ponavlja se).
		root->right = DeleteCertainElement(temp->number, root->right);
	}
	return root;
}