// ���������� ����������
#include <fstream>
#include <string>
#include <iostream>

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

    bool flag = false; // 2 - ������ ������� 
    for (int i = 0; i < size(str); i++) {
        if (str[i] == 'A') // ���� � - �� ���������� ������ �����������
            flag = !flag;
        else if (str[i] == 'C') // ���� � - �� ���������� ������ �����������
            flag = !flag;
    }
    if (flag == false)
        cout << 2 << endl;
    else
        cout << 1 << endl;

    return 0;
}