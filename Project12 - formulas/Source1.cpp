// ���������� ����������
#include <iostream>
#include <math.h>

// ���������� ����������� ������������ ���
using namespace std;

int main() {

    double x, y, z, a, b, c, s;
    cout << "Vvedite x: ";
    cin >> x;

    cout << "Vvedite y: ";
    cin >> y;

    cout << "Vvedite z: ";
    cin >> z;

	// ��������� ��������� ����� �������
    a = abs(pow(x, y / x) - pow(y / x, 1 / 3.));

    b = (y - x);

    c = (cos(y) - z / b) / (1 + pow(b, 2));

	// ����������
    s = a + b * c;

    cout << "Result s = " << s << endl;

    return 0;
}
