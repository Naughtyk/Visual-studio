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
    ifstream file(filename); // ��������� ����

    // ���� �� ���� - ������ ������
    if (file) {
        getline(file, str);
    }
    else {
        cout << "���� �� ������" << endl;
        return 0;
    }
    file.close();

    // ������� ������������ ������ �� 0
    int min = 0, max = 0, k = 0;
    for (auto i: str) {
        if (i == 'L') {
            k--;
            if (min > k)
                min = k;
        }
        if (i == 'R') {
            k++;
            if (max < k)
                max = k;
        }
    }
    // ������� �����
    cout << max + abs(min) + 1 << endl;

    return 0;
}