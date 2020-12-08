// Подключаем библиотеки
#include <iostream>
#include <math.h>

// Используем стандартное пространство имён
using namespace std;

int main(){
    double x, y, f, a, s;
    int k;
    cout << "Vvedite x "; cin >> x;
    cout << "Vvedite y "; cin >> y;
    cout << "Viberite f: 1 - sh(x), 2 - x^2, 3 - exp(x) "; cin >> k;

    switch (k){
		case 1: f = sinh(x); break;
		case 2: f = pow(x, 2); break; // Выбираем функцию
		case 3: f = exp(x); break;
		default: cout << "Ne vuibrana funkciya "; return 1;
    }
	// Проверяем х
    if (x > abs(y)) {
        s = 2 * pow(f, 3) + 3 * pow(y, 2); // Вычисляем
    }
    else if (x > 3 && x < abs(y)) {
        s = fabs(f - y);
    }
    else {
        s = pow(fabs(f - y), 1 / 3.);
    }
    cout << "RESULT = " << s << endl;
    return 0;
}