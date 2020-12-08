#define _CRT_SECURE_NO_WARNINGS

// Подключаем библиотеки
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <set> //подключили библиотеку для работы с set

// Используем стандартное пространство имён
using namespace std;

int main() {
	setlocale(LC_ALL, "RUS"); // Кириллица
	string filename;

	cout << "Введите название файла: " << endl;
	cin >> filename;
	string str;
	ifstream file(filename);

	// Если файл есть - читаем строку
	if (file) {
		getline(file, str);
	}
	else {
		cout << "Файл не найден" << endl;
		return 0;
	}

	// Убираем точку и запятые между скобочек
	for (int i = 0; i < size(str); i++) {
		if (str[i] == ' ')
			str.erase(i - 1, 1);
		if (str[i] == '.')
			str.erase(i, 1);
	}
	// эталонный сэт
	set<string> SET = { {"(3,3)"}, {"(0,0)"}, {"(0,1)"}, {"(0,2)"}, {"(4,4)"},
		{"(4,5)"}, {"(4,6)"}, {"(2,2)"}, {"(2,6)"}, {"(0,3)"}, {"(0,4)"}, {"(0,5)"},
		{"(0,6)"}, {"(5,5)"}, {"(5,6)"}, {"(6,6)"}, {"(1,1)"}, {"(1,2)"}, {"(1,3)"},
		{"(1,4)"}, {"(1,5)"}, {"(1,6)"}, {"(3,4)"}, {"(3,5)"}, {"(3,6)"}, {"(2,3)"}, {"(2,5)"}, { "(2,4)" } };

	// тот, который мы считали из файла
	set<string> SET2;

	// делим строку по пробелам
	char* s = new char[str.size() + 1];
	strcpy(s, str.c_str());

	char* p = strtok(s, " ");

	while (p!= NULL) {
		SET2.insert(p); // Добавляем в сэт очередной элемент
		p = strtok(NULL, " ");
	}
	
	// Ищем отсутствующий элемент
	for (auto i : SET) {
		if (SET2.find(i) == SET2.end())
			cout << i << endl;
	}

	return 0;
}