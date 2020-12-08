#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

// ������� ������ ������������ ����
bool gamilton(int start, int** a, bool* c, int* path, int* r, int m){
	int cur = start; // �������
	int next = 0; // ���������
	path[next++] = cur; // ������ � �������� ���� ������� �������
	bool found; // ������

	// ���� �� ��� ���, ���� �� ��� ������� �� ����� �������� � ����
	while (true)
	{
		found = false;
		c[cur] = true; // ���������� � ������ ������� �������, ��� ��� ��� ��������

		// ���� �� ���� �� ���������� ��������
		for (int i = r[cur] + 1; i < m; i++)
			// ���� ��� �� ������� ������� � �� ������� ������� ���� ���� � ��� ������� � ���
			// ������� �� ���� ��������, ��
			if (i != cur && (a[cur][i]) && !c[i]){
				found = true; // ������ ������� � ���, ��� �� ���� � ��������� �������
				r[cur] = i;
				path[next++] = cur = i; // ������� ��������� � ���� ������� �������, �����
				// ������� � ���������
				break;
			}
		// ���� � ����� �� ���� ������� �� ����� �������, ���� ����� ���� �� ��������, ��
		if (!found) {
			if (next == 1) return false; // ���� ��������� ������� - ������, �� �� ��������
			r[cur] = -1;
			c[cur] = false; // �������, ��� ������� ������� ����� ���� �� ��������, ��� ��� �� ������ ����
			cur = path[--next - 1]; // ������ �� ������� ������� � ���������� � ����� ����
		}
		else
			// ���� �� �������� �� ���� �������� � ���� ���� �� ��������� � ������, �� �������
			if (next == m && (a[cur][start])) return true;
	}
}

// ������� ���������� ��� �������� �������
int** adddel_v(int** a, vector<string>& vect, int& m) {
	// a - ������� ���������, m - ����������� �������
	char versh1[256];
	cout << "1 - �������� �������, 2 - ������� �������\n";
	int k;
	cin >> k;
	if (k != 1 && k != 2) {
		cout << "������� �������� �����, ������������ � ����\n";
		return a;
	}
	cout << "������� �������� �������\n";
	cin >> versh1;
	int** matrix = 0; // �������������� ����� �������
	if (k == 1) {
		// ���� ������� � ����� ���������
		auto iter = find(vect.begin(), vect.end(), versh1);
		if (iter != vect.end()) {
			cout << "������� � ����� ��������� ��� ����\n";
			return a;
		}
		// ���� �� �����, �� ��������� �
		vect.push_back(versh1);
		m++; // ����������� �������������
		matrix = new int* [m];
		// ����� ������� ��������� ������ �� ������ ���� ������� ������ � ������� �������
		for (int i = 0; i < m; i++)
			matrix[i] = new int[m];
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < m - 1; j++) {
				matrix[i][j] = a[i][j];
				if (j == m - 2) {
					matrix[i][j+1] = 0;
				}
				if (i == m - 2) {
					matrix[i + 1][j] = 0;
				}
				if (j == m - 2 && i == m - 2) {
					matrix[i + 1][j + 1] = 0;
				}
			}
		}
	}
	if (k == 2) {
		// ���� ������� � ����� ���������
		auto iter = find(vect.begin(), vect.end(), versh1);
		if (iter == vect.end()) {
			cout << "��������� ������� ���\n" << endl;
			return a;
		}
		// ���� ��� �������, ��� ������
		int index = distance(vect.begin(), iter); // ���� ������ ������� ��� ������� ���������
		vect.erase(iter); // ������� � �� �������
		m--; // ��������� ����������� �������
		matrix = new int* [m];
		// ��������� ����� ������� ������� ����������, �������� �������� �������
		for (int i = 0; i < m; i++)
			matrix[i] = new int[m];
		for (int i = 0; i < index; i++){
			for (int j = 0; j < m+1; j++){
				matrix[i][j] = a[i][j];
			}
		}
		for (int i = index; i < m; i++){
			for (int j = 0; j < m+1; j++){
				a[i][j] = a[i + 1][j];
				matrix[i][j] = a[i][j];
			}
		}
		for (int i = 0; i < m; i++){
			for (int j = 0; j < m; j++){
				if (j >= index)
					a[i][j] = a[i][j+1];
				matrix[i][j] = a[i][j];
			}
		}

		// ����������� ������ 
		delete a;
	}
	// ������������ ����� �������
	return matrix;
}

// ������� ���������� ��� �������� �����
void adddel_r(int** a, vector<string> vect) {
	char versh1[256], versh2[256];
	cout << "�������� ������� v1, v2, ����������� ������: \n";
	cin >> versh1 >> versh2;
	int l=-1, m=-1; int l = -1, m = -1; // �����, ����������� �� ������ � ������� ��� ������� ���������
	for (size_t i = 0; i < vect.size(); ++i) {
		char* chrstr = new char[vect[i].length() + 1];
		strcpy(chrstr, vect[i].c_str());
		if (strcmp(chrstr, versh1) == 0) { l = i; } // ������ ����������, ���� ������� ����� ������� versh1 � �������
		if (strcmp(chrstr, versh2) == 0) { m = i; } // ������ ����������, ���� ������� ����� ������� versh2 � �������
	}
	if (l == -1 || m == -1) {
		cout << "���������(-��) ������(-�) �� ����������\n";
		return;
	}
	if(a[l][m] == 1){
		cout << "����� �������\n";
		a[l][m] = 0; }
	else{
		a[l][m] = 1;
		cout << "����� ���������\n";
	}
	
}

// ������� ��������� ����������� �����
void change_r(int** a, vector<string> vect) {
	char versh1[256], versh2[256];
	cout << "�������� ������� v1, v2, ����������� ������:\n";
	cin >> versh1 >> versh2;

	int l = -1, m = -1; // �����, ����������� �� ������ � ������� ��� ������� ���������
	for (size_t i = 0; i < vect.size(); ++i) { 
		char* chrstr = new char[vect[i].length() + 1];
		strcpy(chrstr, vect[i].c_str());
		if (strcmp(chrstr, versh1) == 0) { l = i; } // ������ ����������, ���� ������� ����� ������� versh1 � �������
		if (strcmp(chrstr, versh2) == 0) { m = i; } // ������ ����������, ���� ������� ����� ������� versh2 � �������
	}
	if (l == -1 || m == -1) {
		cout << "���������(-��) ������(-�) �� ����������\n";
		return;
	}
	if (a[m][l] == 1 && a[l][m] == 1) {
		cout << "����� ��������������\n";
		return;
	}
	if (a[m][l] == 0) {
		cout << "������ ����� ���\n";
		return;
	}
	else {
		cout << "����� ��������������\n";
		a[m][l] = 0;
		a[l][m] = 1;
	}
}

// ������� ��������� �������� �������
vector<string> change_v(int** a, vector<string> vect) {
	char versh1[256], versh2[256];
	//string versh1, versh2;
	
	cout << "������� �������� �������, ������� ����� ��������: \n";
	cin >> versh1;

	cout << "������� ����� ��������: \n";
	cin >> versh2;
	
	auto iter = std::find(vect.begin(), vect.end(), versh1); // ��������, ����������� �� ��������� � ������� �������
	if (iter != vect.end()) // ���� ������� �������
		* iter = versh2; // ������ ������� �� �����
	else
		cout << "������� � ����� ��������� ���";
	return vect;
}

// ������� ������ ������� �������� ������
void show_vector(vector<string> a){
	for (auto it = a.begin(); it != a.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

// ������� ������ ������� ���������
void show_matrix(int** matrix, int m) {
	// ����� ������� ��������� 
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

}

// ����� ����
void Menu()
{
	cout << "              ����:" << endl;
	cout << "1. �������� ��� ������� �������." << endl;
	cout << "2. �������� ��� ������� �����." << endl;
	cout << "3. �������� �������� �������." << endl;
	cout << "4. �������� ����������� �����." << endl;
	cout << "5. ������� �������� ������." << endl;
	cout << "6. ������� ������� ���������." << endl;
	cout << "7. ����� ����������� ����." << endl;
	cout << "8. ������� ������ �� �����." << endl;
	cout << "0. �����" << endl;
	cout << '\n';
	cout << "�������:" << endl;
}

// ���������� ����� �� ������ �����
int get(int min, int max){
	int x;
	while (!(cin >> x) || (x > max) || (x < min)){
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "�������� �����, ������� ������" << endl;
	}
	return x;
}

// ���������� �� �����
void FromFile(vector<string> vect, int** matrix, int m) {
// ���������� �� ����� � ���������� matrix
	string line;
	string path;
	cout << "������� �������� ����� (���� � �����) ��� ����������: " << endl;
	cin >> path;

	ifstream in(path); // ��������� ���� ��� ������
	if (in.is_open()){
		// ������ ��������� �������� ������
		while (getline(in, line)) {
			if (line == "#") { break; }
			vect.push_back(line.substr(line.find(" ") + 1));
			m++;
		}
		// �������� ������������ ������ ��� ������� ���������
		matrix = new int* [m];
		for (int i = 0; i < m; i++)
			matrix[i] = new int[m];

		// ��������� � ������
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				matrix[i][j] = 0;
			}
		}

		// ��������� ��������� ������ ����� - ����
		while (getline(in, line)) {
			// � ���� ���������� ����� ��������� ������
			char* chrstr = new char[line.length() + 1];
			// �������� � �� ������
			strcpy(chrstr, line.c_str());
			// ����� ����� ������ �� "�����" �� ��������
			char* f = strtok(chrstr, " ");
			int i = 0, j = 0, k = 0;
			while (f) {
				if (k == 0) {
					i = stoi(f); // ����������� String � Int - ������ ����� ��� ������� ���������
					f = strtok(NULL, " ");
					k++;
				}
				else {
					j = stoi(f); // ����������� String � Int - ������ ������� ��� ������� ���������
					f = strtok(NULL, " ");
					break;
				}
			}
			// ��������� i, j - ������� ������ � ������� ��� ������� ���������
			matrix[i - 1][j - 1] = 1;
			delete[] chrstr;
		}
	}
	else {
		cout << "����� � ����� ��������� �� �������\n";
	}
	in.close(); // ��������� ����
}

int main() {

	vector<string> vect; // ������, ���������� �������� ������
	setlocale(LC_ALL, ""); // ������������� ������� �����
	int** matrix = 0; // ������� ���������
	int m = 0; // ����������� ������� (���������� ������)

	Menu();
	while (1) {
		switch (get(0, 8)) {
		case 8:
		{
			FromFile(vect, matrix, m);
			Menu();
			break;
		}
		case 1:
		{
			matrix = adddel_v(matrix, vect, m);
			Menu();
			break;
		}
		case 2:
		{
			adddel_r(matrix, vect);
			Menu();
			break;
		}
		case 3:
		{
			vect = change_v(matrix, vect);
			Menu();
			break;
		}
		case 4:
		{
			change_r(matrix, vect);
			Menu();
			break;
		}
		case 5:
		{
			show_vector(vect);
			Menu();
			break;
		}
		case 6:
		{
			show_matrix(matrix, m);
			Menu();
			break;
		}
		case 7:
		{
			bool* c = new bool[m]; // ������, ���������� �������, ������� ��� ���� ��������
			int* path = new int[m]; // ������, ���������� ����������� ����
			int* r = new int[m]; // ������, ���������� ���������� ���������� ��� ������

			printf("Solution:\n");
			for (int i = 0; i < m; i++) {
				c[i] = false;
				r[i] = -1;
			}
			if (gamilton(0, matrix, c, path, r, m)){ // �������� �������, ������� ����� 1, ���� ���� �������, ����� 0
				for (int i = 0; i < m; i++) {
					cout << vect[path[i]] << " "; // ������� ����
				}
				cout << vect[path[0]] << endl;
			}
			else
				printf("Solution Not Found!\n");
			Menu();
			break;
		}
		case 0:
		{
			cout << "�� ��������!";
			return 0;
		}
		default:
			cout << "������� ����� �� ������\n";
			break;
		}
	}
}