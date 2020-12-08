#include <iostream>
#include <Windows.h> // ����������� ��� SetConsoleCP() � SetConsoleOutputCP()
#include <unordered_set>

using namespace std;

// ������� ��� �������� ���������
bool isReflectionEqual(string s)
{
	// ������������ �������
	unordered_set<char> symmetric = { '�', '�', '�', '�',
						'�', '�', '�', '�', '�', '�', '�' };
	int n = s.length();
	for (int i = 0; i < n; i++)
		// ���� ����� �������������� ������
		// ������������, ����� ���
		if (symmetric.find(s[i]) == symmetric.end())
			return false;
	string rev = s;
	reverse(rev.begin(), rev.end());
	// ���������, �������� �� ������ �����������
	if (rev == s)
		return true;
	else
		return false;
}
// ��� ��������
int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "������� ������: " << endl;
	string s;
	cin >> s;
	if (isReflectionEqual(s))
		cout << "��";
	else
		cout << "���";
	return 0;
}