#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int i = 0;

std::vector <int> vect; // ������, ���������� �������� �����, ��� ������� ����� ������� ���������� �� ������ �� 1

struct tnode {                // ���� ������
	int word;                  // ��������� �� ������ (�����)
	int cntl = 0; // ������� �����
	int cntr = 0; // ������� ������
	struct tnode* left;          // ����� �������
	struct tnode* right;         // ������ �������
};

// ������� ���������� ���� � ������
struct tnode* addtree(struct tnode* p, int w) {
	if (p == NULL) {
		p = (struct tnode*)malloc(sizeof(struct tnode));
		p->word = w;
		p->cntl = p->cntr = 0;
		p->left = p->right = NULL;
	}
	else if (w < p->word) {
		p->cntl++;
		p->left = addtree(p->left, w);
	}
	else {
		p->cntr++;
		p->right = addtree(p->right, w);
	}
	return p;
}

// ������� �������� ���������
void freemem(tnode* tree) {
	if (tree != NULL) {
		freemem(tree->left);
		freemem(tree->right);
		free(tree);
	}
}

// ������ ����� �������
void preOrderTravers(struct tnode* root) {

	ofstream out; // ����� ��� ������
	out.open("out.txt", ios::app); // �������� ���� ��� ������
	if (out.is_open()) {
		if (root) {
			out << (root->word) << std::endl;
			preOrderTravers(root->left);
			preOrderTravers(root->right);
			out.close();
		}
	}
}

// ������� ����� � ������ ��������
int CountSubitems(struct tnode* p) {
	int cnt = 0, cntl = 0, cntr = 0;
	if (p == NULL) {
		return 0;
	}
	else {
		cntl = CountSubitems(p->left);
		cntr = CountSubitems(p->right);
		p->cntl = cntl;
		p->cntr = cntr;
		return cntl + cntr + 1;
	}
}

// ������ � ������ ���� �����, ���������� �� ��������
void Countwords(struct tnode* p) {
	if (p == NULL) {
		return;
	}
	else {
		if (p->cntl == p->cntr + 1 || p->cntl == p->cntr - 1) {
			vect.push_back(p->word);
		}
		Countwords(p->left);
		Countwords(p->right);
	}
}

// ����� �������� �� �������� �����
int find() {
	float middle = 0; // ���� ������� ������� �����
	int size = 0;
	for (auto it = vect.begin(); it != vect.end(); ++it)
	{
		middle += *it;
		size++;
	}
	middle /= size;

	int answer = 0;
	float diff = middle; // ������� ����� ������� � �������

	for (auto it = vect.begin(); it != vect.end(); ++it) // �������� �� ���� ��������� �������
	{
		if ((*it) > middle && (*it) - middle < diff) {
			answer = (*it);
			diff = answer - middle;
		}
		else if ((*it) < middle && middle - (*it) < diff) {
			answer = (*it);
			diff = middle - answer;
		}
		else if ((*it) == middle) {
			answer = (*it);
			diff = 0;
		}
	}
	return answer;
}

// ������� ����� ������������ �������� � ���������
tnode* FindMin(tnode* root) {
	while (root->left) {
		root = root->left;
	}
	return root;
}

// ������� ������� �������� ��������
struct tnode* Delete(struct tnode* root, int data) {
	if (root == NULL) return root;
	else if (data < root->word)
		root->left = Delete(root->left, data);
	else if (data > root->word)
		root->right = Delete(root->right, data);
	else {
		// ����� ���
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//1
		else if (root->left == NULL) {
			struct tnode* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			struct tnode* temp = root;
			root = root->left;
			delete temp;
		}
		// 2 
		else {
			struct tnode* temp = FindMin(root->right);
			root->word = temp->word;
			root->right = Delete(root->right, temp->word);
		}
	}
	return root;
}

/*
void printing(struct tnode* root) {
	if (root) {
		cout << "left: " << (root->cntl) << " " << "right: " << (root->cntr) <<  std::endl;
		printing(root->left);
		printing(root->right);
	}
}
*/

int main() {
	struct tnode* root;
	root = NULL;
	string line;
	ifstream in("in.txt"); // �������� ���� ��� ������
	if (in.is_open())
	{
		while (getline(in, line))
		{
			root = addtree(root, stoi(line));
		}
	}
	in.close(); // ��������� ����
	/*
	while (cin >> word) {
		if (word == 0) { break; }
		root = addtree(root, word);
	}
	*/
	Countwords(root);

	Delete(root, find());
	ofstream out; // ����� ��� ������
	out.open("out.txt"); // ������� ��, ��� ����
	out.close();
	preOrderTravers(root);
	//freemem(root);
	return 0;
}