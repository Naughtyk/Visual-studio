// ���������� ����������
#include <iostream>
#include <vector>

// ���������� ����������� ������������ ���
using namespace std;

int main(){
	int k; // ������ �������
	cout << "Vvedite k" << endl;
	cin >> k;

	// �������, ���������� ����� ��� ������ �������
	vector <int> vector1;
	vector <char> vector2;

	char elem;
	for (int i = 0; i < k; i++) {
		cout << "Vvedite " << i + 1 << " element massiva: " << endl;
		cin >> elem;
		// ���� ��� ������� - � �������� ���� - �� ��� �����
		if ((elem <= '9') && (elem >= '1')) {
			vector1.push_back(atoi(string({ elem }).c_str()));
		}
		else {
			vector2.push_back(elem);
		}
	}
	// ����� �� �����
	cout << "ints: " << endl;
	for (auto i : vector1) {
		cout << i << " ";
	}
	cout << endl;
	cout << "chars: " << endl;
	for (auto i : vector2) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}