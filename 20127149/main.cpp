#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include<windows.h>
#include<stdlib.h>
using namespace std;
struct QuesAns {
	string data;
	string type;
};
struct Node {
	Node* left;
	Node* right;
	QuesAns QA;
};
typedef Node* Tree;
Node* CreateNode(QuesAns QA)
{
	Tree p = new Node;
	p->left = nullptr;
	p->right = nullptr;
	p->QA = QA;
	return p;
}

void ReadFile(fstream &fi,Tree&T) {
	QuesAns QA;
	getline(fi, QA.type, ' ');
	getline(fi, QA.data, '\n');
	T = new Node;
	T->QA.data = QA.data;
	T->QA.type = QA.type;
	if (QA.type == "#A") {
		T->left = NULL;
		T->right = NULL;
	}
	else if (QA.type=="#Q") {	
		ReadFile(fi, T->left);
		ReadFile(fi, T->right);
	}
}

void Extra(Tree& T,QuesAns QA) {
	cin.ignore();
	QuesAns UpQA_1,UpQA_2;
	cout << "Input your animal :";
	getline(cin, UpQA_1.data);
	cout << endl;
	UpQA_1.type = "#A";
	cout << "Input your question :";
	getline(cin, UpQA_2.data);
	UpQA_2.type = "#Q";
	T->QA = UpQA_2;
	T->left = NULL;
	T->left = CreateNode(UpQA_1);
	T->right = NULL;
	T->right = CreateNode(QA);
	cout << "Updated";
}
void play(Tree& T) {
	if (T != NULL) {
		cout <<"\3" << T->QA.data << endl;
		cout << "Choose your answer(Y/N) : ";
		char choose;
		cin >> choose;
		if (choose == 'Y' || choose == 'y') {
			if (T->left == NULL) {
				cout << "I guested :" << T->QA.data << endl;
			}
			else {
				play(T->left);
			}
		}
		else {
			if (T->right == NULL) {
				QuesAns QA;
				QA.data = T->QA.data;
				QA.type = T->QA.type;
				cout << "Sorry I can't guest your animal! Do you want to teach me ? (Y/N) : ";
				char ch;
				cin >> ch;
				if (ch == 'Y' || ch == 'y')
					Extra(T, QA);
				else
					return;
			}
			else {
				play(T->right);
			}
		}
	}
}
void dot(int n,int time) {
	for (int i = 0; i < n; i++)
	{
		Sleep(time);
		cout << ".";
	}
	cout << endl;
}
void SaveFile(fstream& fo, Tree T) {
	if (T != NULL) {
		fo << T->QA.type << " " << T->QA.data << endl;
		SaveFile(fo, T->left);
		SaveFile(fo, T->right);
	}
}
void menu(Tree T) {
	system("color 06");
	int choose(3);
	while (choose != 2) {
		system("pause");
		system("cls");
		cout << " ---------------------- " << endl;
		cout << "| *** ANIMALS GAME *** |" << endl;
		cout << "|                      |" << endl;
		cout << "|     1. Play game     |" << endl;
		cout << "|     2. Quit game     |" << endl;
		cout << " ---------------------- " << endl;
		cout << "Please make your selection: ";
		cin >> choose;
		if (choose == 1) {
			system("cls");
			cout << "Hey boi wait a minute! Read the rule before the game! "<<endl;
			cout << "*You will answer game questions by typing (Y or y/ N or n). If you type different charactors, you will kill the program" << endl;
			cout << "*In the end if the program can't find your animal you can teach each by doing following requiements :" << endl;
			cout << "-- First, input your animal!" << endl;
			cout << "-- Second, input the  question relating to your animal" << endl;
			cout << "That's enough! Then have a good time playing !" << endl;
			/*dot(5,4000);*/
			system("cls");
			play(T);
		}
		else {
			cout << "Bye bye have a good day ! ";
			dot(5,800);
			fstream fo;
			fo.open("ques.txt", ios::out);
			SaveFile(fo, T);
		}
	}
}

int main() {
	fstream fi;
	fi.open("ques.txt", ios::in);
	Tree T;
	T = NULL;
	ReadFile(fi, T);
	menu(T);
}