// ���������� ����������
#include <iostream>
#include <iomanip>
#include <math.h>

// ���������� ����������� ������������ ���
using namespace std;

// �������, ����������� ��������� �����
int factorial(int i){
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}

int main(){
	// �������������� ����������
	double a, b, h, x, y, s, p;
	int n, i;
	//cout << "Vvedite a,b,n" << endl;
	//cin >> a >> b >> n;

	// ������ ������ �������� �������
	a = 0.1;
	b = 1;
	n = 140;
	h = (b - a) / 10;
	x = a;
	// ����������� �� ���� x �� a �� � � ����� h
	do{
		// ������ ���� ����
		p = s = 1;
		// ��������� ����� ����
		for (i = 1; i <= n; i++){
			p *= pow(x / 2, i) * ((pow(i, 2) + 1 ) / factorial(i));
			if (isnan(p)) break; // ���� p - �� ����� (nan), �� ������� �� �����
			s += p;
		}
		// ���� �������
		y = (pow(x, 2)/4 + x / 2 + 1) * exp(x / 2);
		// �����
		cout << setw(15) << x << setw(15) << y << setw(15) << s << endl;
		// ������ ���
		x += h;
	} while (x <= b + h / 2);
	cout << endl;
	return 0;
}