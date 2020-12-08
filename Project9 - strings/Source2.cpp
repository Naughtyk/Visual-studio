#include <iostream>
#include <Windows.h> // Обязательно для SetConsoleCP() и SetConsoleOutputCP()
#include <unordered_set>

using namespace std;

// Функция для проверки отражения
bool isReflectionEqual(string s)
{
	// Симметричные символы
	unordered_set<char> symmetric = { 'Н', 'Ш', 'Х', 'Ф',
						'А', 'П', 'О', 'Д', 'Ж', 'М', 'Т' };
	int n = s.length();
	for (int i = 0; i < n; i++)
		// Если любой несимметричный символ
		// присутствует, ответ НЕТ
		if (symmetric.find(s[i]) == symmetric.end())
			return false;
	string rev = s;
	reverse(rev.begin(), rev.end());
	// Проверяем, является ли строка палиндромом
	if (rev == s)
		return true;
	else
		return false;
}
// Код драйвера
int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите строку: " << endl;
	string s;
	cin >> s;
	if (isReflectionEqual(s))
		cout << "Да";
	else
		cout << "Нет";
	return 0;
}