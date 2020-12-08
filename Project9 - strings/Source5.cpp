/*
�������.
������������ �������� ������ �
����� �� ������� �����,
�� �������� ����������� ��������� ���������� �� ������� ����.
���������� ������������. ��������� ��������������� �����.
*/

#include <iostream>
#include <string>
#include <Windows.h> // ����������� ��� SetConsoleCP() � SetConsoleOutputCP()
#include <algorithm>
#include <map>    //���������� ���������� ��� ������ � map

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "������� ������: " << endl;
	string s;
	getline(cin, s);
	map <char, char> Map = { { '�', 'q' }, {'�', 'w'},
	{'�', 'e'},{'�', 'r'},{'�', 't'},
	{'�', 'y'},{'�', 'u'},{'�', 'i'},
	{'�', 'o'},{'�', 'p'},{'�', '['},
	{'�',']'},{'�', 'a'},{'�', 's'},{'�', 'd'},
	{'�', 'f'},{'�', 'g'},{'�', 'h'},
	{'�', 'j'},{'�', 'k'},{'�', 'l'},
	{'�', ';'},{'�', '\''},{'�', 'z'},{'�', 'x'},
	{'�', 'c'},{'�', 'v'},{'�', 'b'},
	{'�', 'n'},{'�', 'm'},{'�', ','},{'�', '.'},{'.', '/'}, {' ', ' '} };

	for (int i = 0; i < size(s); i++) {
		cout << find_if(Map.begin(), Map.end(), [&](const pair<int, int> a)
			{return a.second == s[i]; })->first;
	}

	return 0;
}