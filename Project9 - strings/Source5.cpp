/*
Лытдыбр.
Пользователь набирает строку –
текст на русском языке,
но забывает переключить раскладку клавиатуры на русский язык.
Получается «абракадабра». Программа восстанавливает текст.
*/

#include <iostream>
#include <string>
#include <Windows.h> // Обязательно для SetConsoleCP() и SetConsoleOutputCP()
#include <algorithm>
#include <map>    //подключили библиотеку для работы с map

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите строку: " << endl;
	string s;
	getline(cin, s);
	map <char, char> Map = { { 'й', 'q' }, {'ц', 'w'},
	{'у', 'e'},{'к', 'r'},{'е', 't'},
	{'н', 'y'},{'г', 'u'},{'ш', 'i'},
	{'щ', 'o'},{'з', 'p'},{'х', '['},
	{'ъ',']'},{'ф', 'a'},{'ы', 's'},{'в', 'd'},
	{'а', 'f'},{'п', 'g'},{'р', 'h'},
	{'о', 'j'},{'л', 'k'},{'д', 'l'},
	{'ж', ';'},{'э', '\''},{'я', 'z'},{'ч', 'x'},
	{'с', 'c'},{'м', 'v'},{'и', 'b'},
	{'т', 'n'},{'ь', 'm'},{'б', ','},{'ю', '.'},{'.', '/'}, {' ', ' '} };

	for (int i = 0; i < size(s); i++) {
		cout << find_if(Map.begin(), Map.end(), [&](const pair<int, int> a)
			{return a.second == s[i]; })->first;
	}

	return 0;
}