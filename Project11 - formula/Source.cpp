#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	cout << "Введите переменную t, с: " << endl;
	float t;
	cin >> t;
	if (t < 0) {
		cout << "Время не может быть отрицательным" << endl;
		return 0;
	}
	float S;
	float g = 9.8;
	S = g * t * t / 2;
	cout << "Расстояние от сруба до воды: " << S << " метров" << endl;


	return 0;
}