#include <iostream>
#include <string>
#include <Windows.h> // ����������� ��� SetConsoleCP() � SetConsoleOutputCP()
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "������� ������: " << endl;
	string s;
	getline(cin, s);
	int i1, i2, i3;
	string doplusa, posleravno, posleplusa;
	posleplusa = s.substr(s.find("+") + 1);
	posleplusa = posleplusa.erase(s.find("="));
	posleravno = s.substr(s.find("=") + 1);
	doplusa = s.erase(s.find("+"));
	i1 = stoi(doplusa);
	i2 = stoi(posleplusa);
	i3 = stoi(posleravno);
	if (i1 + i2 == i3)
		cout << "��" << endl;
	else
		cout << "���" << endl;
	return 0;
}