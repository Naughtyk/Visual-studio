// ���������� ����������
#include <iostream>
#include <vector>

// ���������� ����������� ������������ ���
using namespace std;

int main(){
	int n, m; // ������ �������
	cout << "Vvedite n, m" << endl;
	cin >> n >> m;

	// ��������������
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[m];
	// ��������� � ����������
	int elem;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++){
			cout << "Vvedite M[" << i << "][" << j << "]: ";
			cin >> elem;
			a[i][j] = elem;
		}
		cout << endl;
	}

	// �������
	cout << "massiv:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}

	int * b = new int[m];
	int tmp;
	for (int j = 0; j < m; j++){
		// ���� ����������� �������� � ��������
		b[j] = a[0][j];
		for (int i = 1; i < n; i++)
			if (a[i][j] < b[j])
				b[j] = a[i][j];
	}
	// ��������� ���������
	int min;
	for (int i = 0; i < m - 1; i++){
		min = i;
		for (int j = i + 1; j < m; j++)
			if (b[j] < b[min])
				min = j;
		for (int j = 0; j < n; j++){
			tmp = a[j][i];
			a[j][i] = a[j][min];
			a[j][min] = tmp;
		}
		tmp = b[i];
		b[i] = b[min];
		b[min] = tmp;
	}
	// ������� ��������������� ������
	cout << "poluchennyi massiv:" << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}

	return 0;
}