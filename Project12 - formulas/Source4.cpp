// Подключаем библиотеки
#include <iostream>
#include <vector>

// Используем стандартное пространство имён
using namespace std;

int main(){
	int k; // Размер массива
	cout << "Vvedite k" << endl;
	cin >> k;

	// Векторы, содержащие цифры или другие символы
	vector <int> vector1;
	vector <char> vector2;

	char elem;
	for (int i = 0; i < k; i++) {
		cout << "Vvedite " << i + 1 << " element massiva: " << endl;
		cin >> elem;
		// Если код символа - в пределах цифр - то это цифра
		if ((elem <= '9') && (elem >= '1')) {
			vector1.push_back(atoi(string({ elem }).c_str()));
		}
		else {
			vector2.push_back(elem);
		}
	}
	// Вывод на экран
	cout << "ints: " << endl;
	for (auto i : vector1) {
		cout << i << " ";
	}
	cout << endl;
	cout << "chars: " << endl;
	for (auto i : vector2) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}