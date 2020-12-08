/*
4.  ������. ������ � ��� ������������ ������ �� ���������� ���� ��� ����.
������� ������ � ��� ���, � ������� ���� � ���������� ���������� �����,
� �������� ���������� �����, � �����, � ��� ����� �� ����� 8 ��������.
� ��������� ����� �������� ��������� ������������������ ��������.
��������� ������� ��������� ���� ������ �� �������, ��� ���� ������,
�� ���������, ��� ���� ������� �������.
*/

// ���������� ����������
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

// ���������� ����������� ������������ ���
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS"); // ���������
    string filename;

    cout << "������� �������� �����: " << endl;
    cin >> filename;
    string str;
    ifstream file(filename);

    // ���� ���� ���� - ������ ������
    if (file) {
        getline(file, str);
    }
    else {
        cout << "���� �� ������" << endl;
        return 0;
    }

    bool flag1 = true, // ���� �� ������� �����
        flag2 = true, // ���� �� ��������� �����
        flag3 = false, // ���� �� �����
        flag4 = false; // ������ 8 ���� ��� ���

    // ������� ��������������� ������, ����� � ��� ���������� ��������
    string str2;
    str2 = str;

    transform(str2.begin(), str2.end(), str2.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if (str == str2)
        flag1 = false; // ������� ���� ���

    transform(str2.begin(), str2.end(), str2.begin(),
        [](unsigned char c) { return std::toupper(c); });

    if (str == str2)
        flag2 = false; // ��������� ���� ���
    if (any_of(str.begin(), str.end(), [](int i) {return isdigit(i); }))
        flag3 = true; // ����� ����
    if (size(str) >= 8)
        flag4 = true; // ������ ������ ������

    // ���� ������ ������
    if (size(str) == 0) {
        cout << "��� ������ �� ������" << endl;
        return 0;
    }

    // ���� ��� ����� - "�������"
    if (flag1 == true && flag2 == true && flag3 == true && flag4 == true) {
        cout << "��� ������� ������" << endl;
    }
    // �����
    else {
        cout << "��� ������, �� ���������" << endl;
    }
    return 0;
}