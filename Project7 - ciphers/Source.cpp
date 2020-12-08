#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>

using namespace std;

void print_menu() {
	cout << " �������� ����: " << endl;
	cout << " ������� <1> ��� ����� ��������� ������ � ������ ��� � ����" << endl;
	cout << " ������� <2> ��� ������ ����� ������" << endl;
	cout << " ������� <3> ��� ������ ��������� ��������" << endl;
	cout << " ������� <4> ��� ������ �������� ��������" << endl;
	cout << " ������� <5> ��� ������ ����� �� �����" << endl;
	cout << " ������� <6> ��� ������" << endl;
}

void print_text() {
	const int max_size = 256; // ���������, ���������� ������������ ����� ����� �����.
	char* fileIn1 = new char[max_size]; // ������ ��� �������� ����� ����� ������.
	cout << "�������� �����: \n";
	cin >> fileIn1;

	const int N = 256;
	char S[N]; //� S ����� ����������� ������ 

	ifstream in1(fileIn1); //������� ���� ��� ������
	while (!in1.eof()) //����� ������ ���������� ���� �� ������ �� ����� �����
	{
		in1.getline(S, N); //���������� ���������� ���������� � S 
		cout << S << endl; //����� ��������� ������ �� ����� 
	}
	in1.close();  //������� �������� ����

}

void write_to_file() {
	string text;
	cout << "������� �����: " << endl;
	cin.ignore();
	getline(cin, text);
	const int max_size = 256; // ���������, ���������� ������������ ����� ����� �����.
	char* fileOut1 = new char[max_size]; // ������ ��� �������� ����� ����� ������.
	cout << "�������� �����: \n";
	cin >> fileOut1;
	FILE* fo1 = fopen(fileOut1, "w");
	const char* ps;
	ps = text.c_str();
	fprintf(fo1, "%s", ps); // ������ ������ � ����
	fclose(fo1);
}

int get_variant(int count) {
	int variant;
	char s[100]; // ������ ��� ���������� �������� ������
	scanf("%s", s); // ��������� ������

	// ���� ���� �����������, �������� �� ���� � ������ ��������� ���
	while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
		printf("Incorrect input. Try again: "); // ������� ��������� �� ������
		scanf("%s", s); // ��������� ������ ��������
	}
	return variant;
}

void Caeser(bool flag) {
	char a;
	const int max_size = 256; // ���������, ���������� ������������ ����� ����� �����.
	char* fileOut2 = new char[max_size]; // ������ ��� �������� ����� ����� ������.
	char* fileName = new char[max_size]; // ������ ��� �������� ����� ����� �����.
	cout << "�������� ����� �����: \n";
	cin >> fileName;
	FILE* f = fopen(fileName, "r");

	if (f == NULL) {
		cout << "���� ����� ����������� \n";
	}
	else {
		int n, * key;
		cout << "�������� ����� ������: \n";
		cin >> fileOut2;
		FILE* fo2 = fopen(fileOut2, "w");
		cout << "������� ����: \n";
		cin >> n;
		key = new int[n];

		while ((a = fgetc(f)) != EOF) {
			if (a >= 'a' && a <= 'z') {
				if (flag) {
					a = ('a' + (a - 'a' + n) % 26);
				}
				else {
					a = ('z' - ('z' - a + n) % 26);
				}
				fprintf(fo2, "%c", a);
			}
			else if (a >= 'A' && a <= 'Z') {
				if (flag) {
					a = ('A' + (a - 'A' + n) % 26);
				}
				else {
					a = ('Z' - ('Z' - a + n) % 26);
				}
				fprintf(fo2, "%c", a);
			}
			else {
				fprintf(fo2, "%c", a);
			}
		}
		fclose(f);
		fclose(fo2);
	}
}

void Tab(bool flag) {
	char a;
	const int max_size = 256; // ���������, ���������� ������������ ����� ����� �����.
	char* fileOut2 = new char[max_size]; // ������ ��� �������� ����� ����� ������.
	char* fileName = new char[max_size]; // ������ ��� �������� ����� ����� �����.
	cout << "�������� ����� �����: \n";
	cin >> fileName;
	FILE* f = fopen(fileName, "r");

	if (f == NULL) {
		cout << "���� ����� ����������� \n";
	}
	else {
		cout << "�������� ����� ������: \n";
		cin >> fileOut2;
		FILE* fo2 = fopen(fileOut2, "w");
		while ((a = fgetc(f)) != EOF) {
			if (a == 'a') { a = 'z'; }
			else if (a == 'b') { a = 'y'; }
			else if (a == 'c') { a = 'x'; }
			else if (a == 'd') { a = 'w'; }
			else if (a == 'e') { a = 'v'; }
			else if (a == 'f') { a = 'u'; }
			else if (a == 'g') { a = 't'; }
			else if (a == 'h') { a = 's'; }
			else if (a == 'i') { a = 'r'; }
			else if (a == 'j') { a = 'q'; }
			else if (a == 'k') { a = 'p'; }
			else if (a == 'l') { a = 'o'; }
			else if (a == 'm') { a = 'n'; }
			else if (a == 'n') { a = 'm'; }
			else if (a == 'o') { a = 'l'; }
			else if (a == 'p') { a = 'k'; }
			else if (a == 'q') { a = 'j'; }
			else if (a == 'r') { a = 'i'; }
			else if (a == 's') { a = 'h'; }
			else if (a == 't') { a = 'g'; }
			else if (a == 'u') { a = 'f'; }
			else if (a == 'v') { a = 'e'; }
			else if (a == 'w') { a = 'd'; }
			else if (a == 'x') { a = 'c'; }
			else if (a == 'y') { a = 'b'; }
			else if (a == 'z') { a = 'a'; }
			fprintf(fo2, "%c", a);
		}
		fclose(f);
		fclose(fo2);
	}
}

void Grid(bool flag) {

	char a;
	const int max_size = 256; // ���������, ���������� ������������ ����� ����� �����.
	char* fileOut2 = new char[max_size]; // ������ ��� �������� ����� ����� ������.
	char* fileName = new char[max_size]; // ������ ��� �������� ����� ����� �����.
	cout << "�������� ����� �����: \n";
	cin >> fileName;
	FILE* f = fopen(fileName, "r");

	if (f == NULL) {
		cout << "���� ����� ����������� \n";
	}
	else {
		cout << "�������� ����� ������: \n";
		cin >> fileOut2;
		FILE* fo2 = fopen(fileOut2, "w");

		const int SIZE = 5;
		int grid[SIZE][SIZE] = { {0, 0, 1, 0, 1},
							  {1, 1, 0, 1, 0},
							  {0, 0, 0, 0, 1},
							  {0, 1, 0, 1, 0},
							  {1, 0, 1, 0, 0} }; // ������� �������

		a = 1;
		while (a != EOF) {
			// ����������
			if (flag) {
				// ������ ����� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
						if (grid[i][j] == 1) {
							a = fgetc(f);
							if (a != EOF)
								fprintf(fo2, "%c", a);
							else
								fprintf(fo2, "%c", ('a' + j + i * SIZE));
						}
						else
							fprintf(fo2, "%c", ('a' + j + i * SIZE));

				// ������� ������� �� 90 �������� �� ������� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
						if (grid[SIZE - j - 1][i] == 1)
							if (grid[i][j] == 1) {
								a = fgetc(f);
								if (a != EOF)
									fprintf(fo2, "%c", a);
								else
									fprintf(fo2, "%c", ('a' + j + i * SIZE));
							}
							else
								fprintf(fo2, "%c", ('a' + j + i * SIZE));

				// ������� ������� �� 180 �������� �� ������� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
						if (grid[SIZE - i - 1][SIZE - j - 1] == 1)
							if (grid[i][j] == 1) {
								a = fgetc(f);
								if (a != EOF)
									fprintf(fo2, "%c", a);
								else
									fprintf(fo2, "%c", ('a' + j + i * SIZE));
							}
							else
								fprintf(fo2, "%c", ('a' + j + i * SIZE));

				// ������� ������� �� 270 �������� �� ������� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++)
						if (grid[j][SIZE - i - 1] == 1)
							if (grid[i][j] == 1) {
								a = fgetc(f);
								if (a != EOF)
									fprintf(fo2, "%c", a);
								else
									fprintf(fo2, "%c", ('a' + j + i * SIZE));
							}
							else
								fprintf(fo2, "%c", ('a' + j + i * SIZE));
			}
			// ������������
			else {
				// ������ ����� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++) {
						a = fgetc(f);
						if (a != EOF)
						if (grid[i][j] == 1)
								fprintf(fo2, "%c", a);
					}

				// ������� ������� �� 90 �������� �� ������� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++) {
						a = fgetc(f);
						if (a != EOF)
							if (grid[SIZE - j - 1][i] == 1)
								fprintf(fo2, "%c", a);
					}

				// ������� ������� �� 180 �������� �� ������� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++) {
						a = fgetc(f);
						if (a != EOF)
							if (grid[SIZE - i - 1][SIZE - j - 1] == 1)
								fprintf(fo2, "%c", a);
					}

				// ������� ������� �� 270 �������� �� ������� �������
				for (int i = 0; i < SIZE; i++)
					for (int j = 0; j < SIZE; j++) {
						a = fgetc(f);
						if (a != EOF)
							if (grid[j][SIZE - i - 1] == 1)
								fprintf(fo2, "%c", a);
					}
			}
		}
		fclose(f);
		fclose(fo2);
	}
}

void Password(string correctPassword) {
	string password;
	cout << "������: " << endl;
	while (1)
	{
		cin >> password;
		if (password != correctPassword)
			cout << "�������� ������" << endl;
		else
		{
			break;
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	string correctPassword = "1";
	string password;
	int variant1, variant2; // ��������� ����� ����/����
	bool flag; // ���������� ��� ������������

	Password(correctPassword);

	do {
		print_menu(); // ������� ���� �� �����
		variant1 = get_variant(6); // �������� ����� ���������� ������ ����
		switch (variant1) {
		case 1:
			write_to_file();
			break;
		case 2:
			Password(correctPassword);
			cout << " ������� <1> ��� ����������" << endl;
			cout << " ������� <2> ��� ����������" << endl;
			variant2 = get_variant(2);
			if (variant2 == 1) {
				Caeser(flag = true);
			}
			else {
				Caeser(flag = false);
			}
			break;
		case 3:
			Password(correctPassword);
			cout << " ������� <1> ��� ����������" << endl;
			cout << " ������� <2> ��� ����������" << endl;
			variant2 = get_variant(2);
			if (variant2 == 1) {
				Tab(flag = true);
			}
			else {
				Tab(flag = false);
			}
			break;
		case 4:
			Password(correctPassword);
			cout << " ������� <1> ��� ����������" << endl;
			cout << " ������� <2> ��� ����������" << endl;
			variant2 = get_variant(2);
			if (variant2 == 1) {
				Grid(flag = true);
			}
			else {
				Grid(flag = false);
			}
			break;
		case 5:
			print_text();
			break;
		}
		if (variant1 != 6)
			system("pause"); // ����������� ����������, ����� ������������ ��� ������� ��������� ���������� ���������� ������
	} while (variant1 != 6);
	return 0;
}