#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	cout << "������� ���������� t, �: " << endl;
	float t;
	cin >> t;
	if (t < 0) {
		cout << "����� �� ����� ���� �������������" << endl;
		return 0;
	}
	float S;
	float g = 9.8;
	S = g * t * t / 2;
	cout << "���������� �� ����� �� ����: " << S << " ������" << endl;


	return 0;
}