// Подключаем библиотеки
#include <iostream>
#include <math.h>

// Используем стандартное пространство имён
using namespace std;

int main() {

    double x, y, z, a, b, c, s;
    cout << "Vvedite x: ";
    cin >> x;

    cout << "Vvedite y: ";
    cin >> y;

    cout << "Vvedite z: ";
    cin >> z;

	// Вычисляем составные части формулы
    a = abs(pow(x, y / x) - pow(y / x, 1 / 3.));

    b = (y - x);

    c = (cos(y) - z / b) / (1 + pow(b, 2));

	// Объединяем
    s = a + b * c;

    cout << "Result s = " << s << endl;

    return 0;
}
