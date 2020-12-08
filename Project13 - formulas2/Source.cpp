// ���������� ����������
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <algorithm>

#define M_PI 3.14159265358979323846

// ���������� ����������� ������������ ���
using namespace std;

int main() {

	vector <double> raznost;

	double a, b, h, c;

	c = 3 * M_PI / 7;

	a = 2 * M_PI / 3;
	b = M_PI;
	h = M_PI / 10;

	int K;
	cout << "Vvedite K" << endl;
	cin >> K;
	if (K <= 10) {
		cout << "Nevernoe K" << endl;
		return 0;
	}

	// �������������� ����������
	double x, y, s, p, d;

	// ������ ������ �������� �������
	x = a;

	cout << setw(15) << "x" << setw(15) << "y" << setw(15) << "s" << endl;
	// ����������� �� ���� x �� a �� � � ����� h
	do {
		// ������ ���� ����
		s = sin(a);
		p = 1;
		// ��������� ����� ����
		for (int i = 1; i <= K; i++) {
			d = sin(a + M_PI * i / 2);
			p *= x/i;
			if (isnan(p)) break; // ���� p - �� ����� (nan), �� ������� �� �����
			s += p * d;
		}
		// ���� �������
		y = sin(x + a);
		// �����
		cout << setw(15) << x << setw(15) << y << setw(15) << s << endl;
		raznost.push_back(abs(s - y));
		// ������ ���
		x += h;
	} while (x <= b + h / 2);
	
	double maxElement = *max_element(raznost.begin(), raznost.end());

	double minElement = *min_element(raznost.begin(), raznost.end());

	cout << "raznost izmenyaetsya v predelah ot " << minElement << " do " << maxElement << endl;

	cout << endl;
	return 0;
}