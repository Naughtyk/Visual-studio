#include <iostream>
#include <string>
#include <Windows.h> // Обязательно для SetConsoleCP() и SetConsoleOutputCP()
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите строку: " << endl;
	string s;
	getline(cin, s);
	for (int i = s.size() - 1; i >= 0; i--){
		if (s[i] == ' ' || s[i] == '!' || 
			s[i] == '?' || s[i] == '.' || 
			s[i] == ',' || s[i] == ':' || 
			s[i] == ';' || s[i] == '*')
			s.erase(i, 1);
	}
	std::transform(s.begin(), s.end(), s.begin(), tolower);
	string rev = s;
	reverse(rev.begin(), rev.end());
	// Проверяем, является ли строка палиндромом
	if (rev == s)
		cout << "Да";
	else
		cout << "Нет";
	return 0;
}