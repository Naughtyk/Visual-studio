#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	string file1, file2;
	cout << "������� �������� ����� ��� ������ �������� �� ��������" << endl;
	cin >> file1;

	cout << "������� �������� ����� ��� ������ ������" << endl;
	cin >> file2;
	string line1, line2;

	ifstream in1(file1); // �������� ���� ��� ������
	ifstream in2(file2); // �������� ���� ��� ������

	int secondspace;
	int order;
	int kolvo;
	string substr;
	if (in1.is_open() && in2.is_open())
	{
		while (getline(in1, line1))
		{
			getline(in2, line2);
			secondspace = line1.find(' ');
			substr = line1.substr(secondspace + 1);
			secondspace = substr.find(' ');
			kolvo = atoi(substr.substr(secondspace).c_str());
			secondspace = line2.find(' ');
			substr = line2.substr(secondspace + 1);
			secondspace = substr.find(' ');
			order = atoi(substr.substr(secondspace).c_str());
			if (order > kolvo) {
				cout << "������������ ��������� �������" << endl;
				cout << line1 << endl;
			}
		}
	}
	in1.close();     // ��������� ����
	in2.close();     // ��������� ����
	system("pause");
	return 0;
}