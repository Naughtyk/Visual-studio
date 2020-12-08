// Подключаем библиотеки
#include <iostream>
#include <iomanip>
#include <math.h>

// Используем стандартное пространство имён
using namespace std;

// Функция, вычисляющая факториал числа
int factorial(int i){
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}

int main(){
	// Инициализируем переменные
	double a, b, h, x, y, s, p;
	int n, i;
	//cout << "Vvedite a,b,n" << endl;
	//cin >> a >> b >> n;

	// Вводим данные согласно заданию
	a = 0.1;
	b = 1;
	n = 140;
	h = (b - a) / 10;
	x = a;
	// Пробегаемся по всем x от a до б с шагом h
	do{
		// Первый член ряда
		p = s = 1;
		// Остальные члены ряда
		for (i = 1; i <= n; i++){
			p *= pow(x / 2, i) * ((pow(i, 2) + 1 ) / factorial(i));
			if (isnan(p)) break; // Если p - не число (nan), то выходим из цикла
			s += p;
		}
		// Сама функция
		y = (pow(x, 2)/4 + x / 2 + 1) * exp(x / 2);
		// Вывод
		cout << setw(15) << x << setw(15) << y << setw(15) << s << endl;
		// Делаем шаг
		x += h;
	} while (x <= b + h / 2);
	cout << endl;
	return 0;
}