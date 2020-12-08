// Подключаем библиотеки
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Используем стандартное пространство имён
using namespace std;

int main(){

	string s;
	vector <int> vect;
	cout << "Vvedite chisla cherez probel: ";
	getline(cin, s);

	// Делим строку по пробелам и добавляем в вектор числа
	string word = "";
	for (auto x : s){
		if (x == ' '){
			vect.push_back(stoi(word));
			word = "";
		}
		else{
			word = word + x;
		}
	}

	// сортируем с помощью функции sort библиотеки algorithm
	sort(vect.begin(), vect.end());

	// Выводим на экран
	for (auto i: vect) {
		cout << i << " ";
	}

	return 0;
}