#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<windows.h>
#include<string.h>
#include<fstream>
using namespace std;

struct node
{
	char word[20];
	char meaning[300];
	node* left;
	node* right;
};
node* root = NULL;

void writefile_dictionary(char word[20], char meaning[300]);
node* Create(char word[20], char meaning[300]);
node* Insert(node* root, char word[20], char meaning[300]);
void Display_Dictionary(node* root);
void search(node* root, char word[20]);
void update(node*& root, char word[20]);
node* min_val(node* root);
node* Delete(node* root, char word[20]);
void menu_header();

node* Create(char word[20], char meaning[300])
{
	node* temp = new node();
	strcpy_s(temp->word, word);
	strcpy_s(temp->meaning, meaning);
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

node* Insert(node* root, char word[20], char meaning[300])
{
	if (root == NULL)
	{
		node* root = Create(word, meaning);
		return root;
	}
	if (strcmp(word, root->word) < 0)
	{
		root->left = Insert(root->left, word, meaning);
		return root;
	}
	else if (strcmp(word, root->word) > 0)
	{
		root->right = Insert(root->right, word, meaning);
		return root;
	}
	else if (strcmp(word, root->word) == 0)
	{
		cout << "The word is already in dictionary!" << endl;
		return root;
	}
	return root;
}

void Display_Dictionary(node* root)
{
	if (root != NULL)
	{
		Display_Dictionary(root->left);
		printf("Word: %s \n", root->word);
		printf("Meaning: %s \n\n", root->meaning);
		Display_Dictionary(root->right);
	}
}

void search(node* root, char word[20])
{
	if (root == NULL)
	{
		cout << endl;
		cout << " ________________________________ " << endl;
		cout << "|                                |" << endl;
		cout << "| The word is not in Dictionary! |" << endl;
		cout << "|________________________________|" << endl << endl;
	}
	else if (strcmp(word, root->word) == 0)
	{
		cout << "_______________________________________________________" << endl << endl;
		printf("Word: %s \n", root->word);
		printf("Meaning: %s \n", root->meaning);
		cout << "_______________________________________________________" << endl;
	}
	else if (strcmp(word, root->word) < 0)
	{
		return search(root->left, word);
	}
	else if (strcmp(word, root->word) > 0)
	{
		return search(root->right, word);
	}
}

void update(node*& root, char word[20])
{
	if (root == NULL)
	{
		cout << endl;
		cout << " ________________________________ " << endl;
		cout << "|                                |" << endl;
		cout << "| The word is not in Dictionary! |" << endl;
		cout << "|________________________________|" << endl << endl;
	}
	else if (strcmp(word, root->word) == 0)
	{
		cout << "_______________________________________________________" << endl << endl;
		printf("Existing Meaning: %s \n", root->meaning);
		cout << "Enter New Meaning: ";
		scanf_s("\n");
		scanf_s("%[^\n]%*c", root->meaning, 300);

		cout << "_______________________________________________________" << endl << endl;
	}
	else if (strcmp(word, root->word) < 0)
	{
		return update(root->left, word);
	}
	else if (strcmp(word, root->word) > 0)
	{
		return update(root->right, word);
	}
}

node* min_val(node* root)
{
	node* curr = root;
	while (curr->left != NULL)
	{
		curr = curr->left;
	}
	return curr;
}


node* Delete(node* root, char word[20])
{
	if (root == NULL)
	{
		return root;
	}
	else if (strcmp(word, root->word) < 0)
	{
		root->left = Delete(root->left, word);
	}
	else if (strcmp(word, root->word) > 0)
	{
		root->right = Delete(root->right, word);
	}
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		else if (root->left == NULL) {
			node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			node* temp = root->left;
			free(root);
			return temp;
		}
		else
		{
			node* temp = min_val(root->right);
			strcpy_s(root->word, temp->word);
			strcpy_s(root->meaning, temp->meaning);

			root->right = Delete(root->right, temp->word);
		}
	}
	return root;
}

void menu_header()
{
	cout << endl << endl << endl;

	cout << "\t______ _____ _____ _____ _____ ___   _       ______ _____ _____ _____ _____ _____ _   _   ___  ________   __" << endl;
	cout << "\t|  _  \\_   _|  __ \\_   _|_   _/ _ \\ | |      |  _  \\_   _/  __ \\_   _|_   _|  _  | \\ | | / _ \\ | ___ \\ \\ / /" << endl;
	cout << "\t| | | | | | | |  \\/ | |   | |/ /_\\ \\| |      | | | | | | | /  \\/ | |   | | | | | |  \\| |/ /_\\ \\| |_/ /\\ V / " << endl;
	cout << "\t| | | | | | | | __  | |   | ||  _  || |      | | | | | | | |     | |   | | | | | | . ` ||  _  ||    /  \\ /  " << endl;
	cout << "\t| |/ / _| |_| |_\\ \\_| |_  | || | | || |____  | |/ / _| |_| \\__/\\ | |  _| |_\\ \\_/ / |\\  || | | || |\\ \\  | |  " << endl;
	cout << "\t|___/  \\___/ \\____/\\___/  \\_/\\_| |_/\\_____/  |___/  \\___/ \\____/ \\_/  \\___/ \\___/\\_| \\_/\\_| |_/\\_| \\_| \\_/  " << endl << endl;


	cout << endl << endl;
	cout << "\t\t       ----------------------------MAIN MENU--------------------------" << endl;

	cout << "\t\t ______________________________________ ____________________________________" << endl;
	cout << "\t\t|                                      |                                    |" << endl;
	cout << "\t\t|  (1) Insert Word/Meaning             |   (2) Search Word/Meaning          |" << endl;
	cout << "\t\t|  (3) Update Meaning                  |   (4) Delete Word/Meaning          |" << endl;
	cout << "\t\t|  (5) Display All Words/Meaning       |   (6) Exit                         |" << endl;
	cout << "\t\t|______________________________________|____________________________________|" << endl;
	cout << endl << endl;
}

void writefile_dictionary(char word[20], char meaning[300])
{

	fstream myfile;
	myfile.open("Dictionary.txt", ios::app);
	if (!myfile)
	{
		cout << "No file created";
	}

	else
	{

		myfile << "Word: " << word;
		myfile << endl;
		myfile << "Meaning: " << meaning;
		myfile << endl;
		myfile << endl;
	}

	myfile.close();
}


void main()
{
	int choice1;
	string choice2, choice3;
	bool terminate = false;
	char word[20], meaning[300];
	cout << endl;

	system("color 0E");

	Beep(3020, 1100);
	char l = 219;

	cout << endl << endl << endl;
	cout << "Loading.";
	cout << endl;
	for (int i = 0; i < 12; i++)
	{
		Beep(3000, 500);
		cout << l;
	}
	do
	{

		system("cls");

		menu_header();

		cout << "Enter serial no. from menu to proceed: ";
		cin >> choice1;

		switch (choice1)
		{
		case 1:
			do
			{
				printf("\nInput Word:- ");
				scanf_s("%s", word, 20);
				printf("Input Meaning:- ");
				scanf_s("\n");
				scanf_s("%[^\n]%*c", meaning, 300);
				root = Insert(root, word, meaning);
				writefile_dictionary(word, meaning);
				cout << endl;
				cout << "Enter another word? (yes/no): ";
				cin >> choice3;
			} while (choice3 == "yes" || choice3 == "Yes");
			cout << endl;
			break;
		case 2:
			printf("\nInput Word:- ");
			scanf_s("%s", word, 20);
			search(root, word);
			cout << endl;
			break;
		case 3:
			printf("\nInput Word:- ");
			scanf_s("%s", word, 20);
			update(root, word);
			cout << endl;
			break;
		case 4:
			printf("\nInput Word:- ");
			scanf_s("%s", word, 20);
			Delete(root, word);
			cout << "\nWord deleted succesfully!" << endl;
			cout << endl;
			break;
		case 5:
			cout << endl << endl << endl;
			cout << "Fetching Data.";
			cout << endl;
			for (int i = 0; i < 16; i++)
			{
				Beep(2000, 500);
				cout << l;
			}
			system("cls");
			menu_header();
			cout << endl;
			cout << "          ______________________________";
			cout << endl << "         |  __________________________  |";
			cout << endl << "         | |                          | |";
			cout << endl << "         | |    COMPLETE DICTIONARY   | |";
			cout << endl << "         | |__________________________| |";
			cout << endl << "         |______________________________|" << endl << endl;

			cout << "_______________________________________________________" << endl << endl;
			Display_Dictionary(root);
			cout << "_______________________________________________________" << endl << endl;
			break;
		case 6:
			terminate = true;
			choice2 = "no";
			cout << endl;
			break;
		default:
			cout << endl << "Invalid serial no. entered!" << endl << endl;
		}
		if (terminate != true)
		{
			cout << "Would you like to open menu again? (yes/no): ";
			cin >> choice2;
			cout << endl;
		}
	} while (choice2 == "yes" || choice2 == "Yes");
	system("pause");
}
