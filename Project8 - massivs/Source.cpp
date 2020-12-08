#define _CRT_SECURE_NO_WARNINGS 
// ����� �������� �������, ������������ ���������

// ���������� ����������
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>

// ���������� ����������� ������������ ���
using namespace std;

// ������� ��� ���������� ����������� ������ ������ � ����
int get_variant(int count) {
    int variant;
    char s[100]; // ������ ��� ���������� �������� ������
    scanf("%s", s); // ��������� ������

    // ���� ���� �����������, �������� �� ���� � ������ ��������� ���
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
        printf("Incorrect input. Try again: "); // ������� ��������� �� ������
        scanf("%s", s); // ��������� ������ ��������
    }
    return variant;
}

// ���������� ����
void print_menu() {
    cout << " ������� <1> ��� ���������� ������� �� �����" << endl;
    cout << " ������� <2> ��� ������ ������� �� �����" << endl;
    cout << " ������� <3> ��� ������� ������1" << endl;
    cout << " ������� <4> ��� ������� ������2" << endl;
    cout << " ������� <5> ��� ������� ������3" << endl;
    cout << " ������� <6> ��� ������� ������4" << endl;
    cout << " ������� <7> ��� ������� ������5" << endl;
	cout << " ������� <8> ��� ���������� ������� �� �����" << endl;
	cout << " ������� <9> ��� ������ ������� �� �����" << endl;
    cout << " ������� <10> ��� ������" << endl;
}

// ������� �� ����� ������
void print_massiv(int* massiv, int n) {
	for (int i = 0; i < n; i++)
		cout << massiv[i] << " ";
	cout << endl;
}

// ������� �� ����� �������
void print_matrix(int** matrix, int m, int k) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

// ������ ������� �� �����
int* read_from_file(int* massiv, int& n) {
    cout << "������� �������� �����: ";
    char file[256];
    string str;
    cin >> file;
    ifstream i(file);

	// ���� ���� ������
    if (i) {
        getline(i, str); // ������ ���������
        n = atoi(str.c_str()); // ����������� � int (������ �������)
        massiv = new int[n];
		// ����� ��������� ��� ������
        for (int j = 0; j < n; j++) {
            getline(i, str);
            massiv[j] = atoi(str.c_str());
        }
    }
    else {
        cout << "���� �� ������" << endl;
    }
    i.close(); // ��������� ����
	// ���������� ������
    return massiv;
}

// ������ ������� �� �����
int** read_matrix_from_file(int** matrix, int &m, int &k) {
	string path;
	string line;
	cout << "������� �������� ����� (���� � �����) ��� ����������: " << endl;
	cin >> path;
	ifstream in(path); // ��������� ���� ��� ������

	if (in.is_open()) {
		getline(in, line);
		// � ���� ���������� ����� ��������� ������
		char* chrstr = new char[line.length() + 1];
		// �������� � �� ������
		strcpy(chrstr, line.c_str());
		// ����� ����� ������ �� "�����" �� ��������
		char* f = strtok(chrstr, " ");
		m = stoi(f); // ������
		f = strtok(NULL, " ");
		k = stoi(f); // �������

		// �������� ������������ ������ ��� �������
		matrix = new int* [m];
		for (int i = 0; i < m; i++)
			matrix[i] = new int[k];

		// ��������� � ������
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				matrix[i][j] = 0;
			}
		}

		// ����� ��������� ��������� �������
		for (int i = 0; i < m; i++) {
			getline(in, line);
			// � ���� ���������� ����� ��������� ������
			char* chrstr = new char[line.length() + 1];
			// �������� � �� ������
			strcpy(chrstr, line.c_str());
			// ����� ����� ������ �� "�����" �� ��������
			char* f = strtok(chrstr, " ");
			for (int j = 0; j < k; j++) {
				matrix[i][j] = stoi(f);
				f = strtok(NULL, " ");
			}
			delete[] chrstr;
		}
	}
	else {
		cout << "����� � ����� ��������� �� �������\n";
	}
	in.close(); // ��������� ����
	// ���������� �������
	return matrix;
}

// ������ ������ ������ "������� �������"
void task1(int* massiv, int n) {
	if (n == 0) {
		cout << "������ ������" << endl;
		return;
	}
	if (n == 1) {
		cout << massiv[0] << endl;
		return;
	}

    int box_number;
    cout << "������� ����� �������: ";
    cin >> box_number;
    int time1 = 0; // ����� �� ��������� �������
    int time2 = 0; // ����� ����� ��������� �������

    for (int i = 0; i <= box_number; i++) {
        time1 += massiv[i];
    }
    for (int i = box_number; i < n; i++) {
        time2 += massiv[i];
    }
    if (time1 >= time2)
        cout << time1 << endl;
    else
        cout << time2 << endl;
}

// ������ ������ ������ "�������"
void task2(int* massiv, int n) {
	if (n == 0) {
		cout << "������ ������" << endl;
		return;
	}
	if (n == 1) {
		cout << "����� ���� - 0" << endl;
		return;
	}
	int sum = 0;
	// ������� ��������� ��� ����������
	for (int i = 0; i < n; i++) {
		sum += massiv[i];
	}
	// ������� �������
	int average = sum / n;
	int min = massiv[n-1];
	int index = 0;
	// ����� ���� �������
	for (int i = 0; i < n; i++) {
		if (abs(massiv[i] - average) < min) {
			min = abs(massiv[i] - average);
			index = i; // ���������� ������ ��������
		}
	}
	cout << "����� ���� - " << index << endl;
}

// ������ ������ ������ "�����"
void task3(int* massiv, int n) {

	// ������� ������������� ������� ������
	if (n == 0) {
		cout << "������ ������" << endl;
		return;
	}
	if (n == 1) {
		if (massiv[0] == 0)
			cout << "���������� ����� ������ - 1" << endl;
		else
			cout << "���������� ����� ������ - 0" << endl;
		return;
	}

	// ������� ��������������� ������, �� ������� ����� �������� ���������� ����
	int* massiv2 = new int[n];
	for (int i = 0; i < n; i++)
		massiv2[i] = massiv[i];
	// ������ ������� �� ����� �������
	if (massiv[0] == 1) {
		massiv2[0] = 1;
		massiv2[1] = 1;
	}
	if (massiv[n - 1] == 1) {
		massiv2[n - 2] = 1;
		massiv2[n - 1] = 1;
	}
	// ����� �� ����� ���������� �������
	for (int i = 1; i < n - 1; i++) {
		if (massiv[i] == 1) {
			massiv2[i - 1] = 1;
			massiv2[i] = 1;
			massiv2[i + 1] = 1;
		}
	}
	// ������ ������� ������, ������� ������� (0)
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (massiv2[i] == 0)
			sum++;
	}
	cout << "���������� ����� ������ - " << sum << endl;
	delete [] massiv2;
}

// ������ ��������� ������ "����� ��� ����"
void task4(int** matrix, int m, int k) {
	// ����� ������� ���� ��
	int sum = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < k; j++)
			sum += matrix[i][j];
	// ������� ������, ���� ������� - ��� ���������� ������
	if (m == 1) {
		for (int j = 1; j < k - 1; j++)
			if (matrix[0][j] == 1 && matrix[0][j - 1] == 0 && matrix[0][j + 1] == 0)
				sum--;
		cout << "����� �� ����� ��������� ����� ��� - " << sum << endl;
		return;
	}
	if (k == 1) {
		for (int i = 1; i < m - 1; i++)
			if (matrix[i][0] == 1 && matrix[i - 1][0] == 0 && matrix[i + 1][0] == 0)
				sum--;
		cout << "����� �� ����� ��������� ����� ��� - " << sum << endl;
		return;
	}
	// ���� ������� ����������, �� ������� ������� ��� ����
	if (matrix[0][0] == 1 && matrix[0][1] == 0 && matrix[1][0] == 0)
		sum--;
	if (matrix[m - 1][k - 1] == 1 && matrix[m - 2][k - 1] == 0 && matrix[m - 1][k - 2] == 0)
		sum--;
	if (matrix[m - 1][0] == 1 && matrix[m - 1][1] == 0 && matrix[m - 2][0] == 0)
		sum--;
	if (matrix[0][k - 1] == 1 && matrix[0][k - 2] == 0 && matrix[1][k - 1] == 0)
		sum--;
	// ����� ��� ����
	for (int j = 1; j < k - 1; j++) {
		if (matrix[0][j] == 1 && matrix[0][j - 1] + matrix[0][j + 1] + matrix[1][j] < 2)
			sum--;
		if (matrix[m - 1][j] == 1 && matrix[m - 1][j - 1] + matrix[m - 1][j + 1] + matrix[m - 2][j] < 2)
			sum--;
	}
	for (int i = 1; i < m - 1; i++) {
		if (matrix[i][0] == 1 && matrix[i - 1][0] + matrix[i + 1][0] + matrix[i][0] < 2)
			sum--;
		if (matrix[i][k - 1] == 1 && matrix[i - 1][k - 1] + matrix[i + 1][k - 1] + matrix[i][k - 2] < 2)
			sum--;
	}
	// � ������� ��, ��� �� �� �����
	for (int i = 1; i < m - 1; i++) {
		for (int j = 1; j < k - 1; j++) {
			if (matrix[i][j] == 1 &&
				matrix[i - 1][j] + 
				matrix[i + 1][j] + 
				matrix[i][j - 1] + 
				matrix[i][j + 1] < 3)
				sum--;
		}
	}
	cout << "����� �� ����� ��������� ����� ��� - " << sum << endl;
}

// ������ ����� ������ "�����-�����"
void task5(int** matrix, int m, int k) {
	int sum = 0;
	// ������� ������� ������� ������, ���� ������� - ��� ���������� ������
	if (m == 1) {
		for (int j = 0; j < k ; j++)
			if (matrix[0][j] == 1){
				cout << "������ ��������� ������ - " << 0 << endl;
				return;
			}
		cout << "������ ��������� ������ - " << k << endl;
		return;
	}
	if (k == 1) {
		for (int i = 0; i < m; i++)
			if (matrix[i][0] == 1) {
				cout << "������ ��������� ������ - " << 0 << endl;
				return;
			}
		cout << "������ ��������� ������ - " << m << endl;
		return;
	}

	// ����� ������� ��������������� �������, �� �������� � ������� 3
	int** matrix2 = new int* [m];
	for (int i = 0; i < m; i++)
		matrix2[i] = new int[k];
	// ��������� � ������
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			matrix2[i][j] = 0;
		}
	}
	// �������� ��� ������ � �������, ��� ���� �����
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			if (matrix[i][j] == 1) {
				for (int i2 = 0; i2 < m; i2++)
					matrix2[i2][j] = 1;
				for (int j2 = 0; j2 < k; j2++)
					matrix2[i][j2] = 1;
			}
		}
	}
	// ������� ��������� ������
	for (int i = 0; i < m; i++)
		for (int j = 0; j < k; j++)
			if (matrix2[i][j] == 0)
				sum++;
	cout << "������ ��������� ������ - " << sum << endl;
}

int main(){
    setlocale(LC_ALL, "Russian");

    int variant; // ��� ������ � ����
    int* massiv = nullptr; // ������
	int** matrix = 0; // �������
    int n = 0; // ����������� �������
	int m = 0, k = 0; // ����������� �������

    do {
        print_menu(); // ������� ���� �� �����
        variant = get_variant(10); // �������� ����� ���������� ������ ����
        switch (variant) {
        case 1:
            massiv = read_from_file(massiv, n);
            break;
        case 2:
            print_massiv(massiv, n);
            break;
        case 3:
            task1(massiv, n);
            break;
        case 4:
            task2(massiv, n);
            break;
        case 5:
            task3(massiv, n);
            break;
        case 6:
            task4(matrix, m, k);
            break;
        case 7:
            task5(matrix, m, k);
            break;
		case 8:
			matrix = read_matrix_from_file(matrix, m, k);
			break;
		case 9: 
			print_matrix(matrix, m, k);
			break;
        }
        if (variant != 10)
            system("pause"); // ����������� ����������, ����� ������������ ��� ������� ��������� ���������� ���������� ������
    } while (variant != 10);
    return 0;
}