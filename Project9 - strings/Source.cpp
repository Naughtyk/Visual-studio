#include <algorithm>
#include <string>
#include <iostream>
#include <Windows.h> // Обязательно для SetConsoleCP() и SetConsoleOutputCP()
using namespace std;

int main(){
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string s = "01234";
	string s1 = "УПТИН";
	string str;
	cout << "Введите строку: " << endl;
	cin >> str;
	do {
		char c0 = s[0], c1 = s[1], c2 = s[2], c3 = s[3], c4 = s[4];
		int i0 = atoi(&c0), i1 = atoi(&c1), i2 = atoi(&c2), i3 = atoi(&c3), i4 = atoi(&c4);
		if (s1[i0] == str[0] &&
			s1[i1] == str[1] &&
			s1[i2] == str[2] &&
			s1[i3] == str[3] &&
			s1[i4] == str[4]) {
			if (next_permutation(s.begin(), s.end())) {
				char c0 = s[0], c1 = s[1], c2 = s[2], c3 = s[3], c4 = s[4];
				int i0 = atoi(&c0), i1 = atoi(&c1), i2 = atoi(&c2), i3 = atoi(&c3), i4 = atoi(&c4);
				cout << s1[i0] << s1[i1] << s1[i2] << s1[i3] << s1[i4] << endl;
				break;
			}
			else{
				cout << "Следующего нет" << endl;
				break;
			}
		}
	} while (next_permutation(s.begin(), s.end()));
}
