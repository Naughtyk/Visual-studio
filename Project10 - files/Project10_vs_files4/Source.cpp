#define _CRT_SECURE_NO_WARNINGS

// Подключаем библиотеки
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <Windows.h>

// Используем стандартное пространство имён
using namespace std;

int main() {

	setlocale(LC_ALL, "Russian"); // Кириллица
	char a;
	const int max_size = 256; // Константа, содержащая максимальную длину имени файла.
	char* fileName = new char[max_size]; // Строка для хранения имени файла ввода.
	cout << "Название файла ввода: \n";
	cin >> fileName;
	ifstream ifs(fileName);

	if (!ifs) {
		cout << "Файл не найден" << endl;
		return 0;
	}

	// Если файл есть - читаем его построчно
	string s = "", s1;
	while (getline(ifs, s1)) {
		s += s1 + "\n";
	}

	// Закрываем файл
	ifs.close();
	int n, * key;
	cout << "Введите ключ: \n";
	cin >> n;
	key = new int[n];
	// Поэлементно обрабатываем текст
	for (auto a : s) {
		if (a >= 'a' && a <= 'z') {
			a = ('a' + (a - 'a' + n) % 26);
			cout << a;
		}
		else if (a >= 'A' && a <= 'Z') {
			a = ('A' + (a - 'A' + n) % 26);
			cout << a;
		}
		else if (a >= 'а' && a <= 'я') {
			a = ('а' + (a - 'а' + n) % 32);
			cout << a;
		}
		else if (a >= 'А' && a <= 'Я') {
			a = ('А' + (a - 'А' + n) % 32);
			cout << a;
		}
		else {
			cout << a;
		}
	}
	return 0;
}