#define _CRT_SECURE_NO_WARNINGS

// ���������� ����������
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <Windows.h>

// ���������� ����������� ������������ ���
using namespace std;

int main() {

	setlocale(LC_ALL, "Russian"); // ���������
	char a;
	const int max_size = 256; // ���������, ���������� ������������ ����� ����� �����.
	char* fileName = new char[max_size]; // ������ ��� �������� ����� ����� �����.
	cout << "�������� ����� �����: \n";
	cin >> fileName;
	ifstream ifs(fileName);

	if (!ifs) {
		cout << "���� �� ������" << endl;
		return 0;
	}

	// ���� ���� ���� - ������ ��� ���������
	string s = "", s1;
	while (getline(ifs, s1)) {
		s += s1 + "\n";
	}

	// ��������� ����
	ifs.close();
	int n, * key;
	cout << "������� ����: \n";
	cin >> n;
	key = new int[n];
	// ����������� ������������ �����
	for (auto a : s) {
		if (a >= 'a' && a <= 'z') {
			a = ('a' + (a - 'a' + n) % 26);
			cout << a;
		}
		else if (a >= 'A' && a <= 'Z') {
			a = ('A' + (a - 'A' + n) % 26);
			cout << a;
		}
		else if (a >= '�' && a <= '�') {
			a = ('�' + (a - '�' + n) % 32);
			cout << a;
		}
		else if (a >= '�' && a <= '�') {
			a = ('�' + (a - '�' + n) % 32);
			cout << a;
		}
		else {
			cout << a;
		}
	}
	return 0;
}