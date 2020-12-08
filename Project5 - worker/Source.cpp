#define _CRT_SECURE_NO_WARNINGS // ����� ����� ���� ������� fopen

// ���������� ����������
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
// ������������ ����������� ������������ ���
using namespace std;

// ��������� ��������� Worker
struct Worker
{
	string Name;
	string Post;
	int  ZP = 0;
};

// ��������� ��������� ������ ������� �������� Worker, ������� ����� ����� ������ �� ����� 1.txt
int size;

// ������� ���������� �� ����� 1.txt ������� �������� Worker 
Worker* read(string filename){
	string line;
	ifstream in(filename); // �������� ���� ��� ������
	if (!in) {
		cout << "������� �������� ��� ����� ��� ������" << endl;
		return 0;
	}
	getline(in, line);
	::size = atoi(line.c_str()); // ����� ������ ������� �� ������ ������ �����
	Worker* Sheet = new Worker[::size]; // ����������� ������ ������

	// ��������� �� ������� ���� worker 
	for (int j = 0; j < ::size; j++) {
		getline(in, line);
		Sheet[j].Name = line;
		getline(in, line);
		Sheet[j].Post = line;
		getline(in, line);
		Sheet[j].ZP = atoi(line.c_str());
		getline(in, line);
	}
	in.close(); // ��������� ����
	return Sheet;
}

// ������� ������ �� ����� ����� ������� Worker 
void print(Worker* worker)
{
	for (int i = 0; i < ::size; i++) {
		cout << "Name: " << worker[i].Name << endl
			<< "Post: " << worker[i].Post << endl
			<< "ZP: " << worker[i].ZP << endl;
	}
}

// ������� ������ �� ����� ������ ������ Worker �� �������
void print_1_worker(Worker worker)
{
	cout << "Name: " << worker.Name << endl
		<< "Post: " << worker.Post << endl
		<< "ZP: " << worker.ZP << endl;
}

// ������� ���������� ������� �� ��������
Worker* sort(Worker* arr) {
	int i, sorted;
	int n = ::size;
	Worker tmp;
	sorted = 0;
	while (!sorted) {
		sorted = 1;
		for (i = 0; i < n - 1; i++)
			if (strcmp(arr[i].Name.c_str(), arr[i + 1].Name.c_str()) > 0) {
				sorted = false;
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		n--;
	}
	return arr;
}

// ������� ������ � �������� ���� ����� ������� 
void write_to_file(Worker* worker, string filename_binary) {
	// ������ ������� � ����
	ofstream fout(filename_binary, ios::binary);
	for (int i = 0; i < ::size; ++i){
		fout.write(reinterpret_cast<char*>(&worker[i]), sizeof(Worker));
	}
	fout.close();
}

// ������� ��������� �������� worker � ������� �������� ���� worker �� �������
bool compare(Worker worker, int sr_zp)
{
	if (worker.ZP > sr_zp) {
		return true;
	}
	else {
		return false;
	}
}

// ������� ������ ������ �� ��������� ����� � ������ �� ����� ��� worker, ��� �������� ���� �������
void print_from_binary(int sr_zp, string filename_read_from_binary) {
	Worker worker;
	Worker worker_prew;
	FILE* fp;
	fp = fopen(filename_read_from_binary.c_str(), "rb");
	if (!fp) {
		cout << "������� �������� ��� ����� ������ ������ �� ��������� �����" << endl;
		return;
	}
	while (!feof(fp)){
		worker_prew = worker;
		fread(&worker, sizeof(Worker), 1, fp);
		if (!(worker_prew.Name == worker.Name && worker_prew.Post == worker.Post && worker_prew.ZP == worker.ZP)) {
			if (compare(worker, sr_zp)) {
				print_1_worker(worker);
			}
		}
	}
}

int main(int argc, char* argv[]){
	setlocale(LC_ALL, "RUS");
	// �������� �� ������� �������
	string filename = "1.txt";
	string filename_binary = "2.dat";
	string filename_read_from_binary = "2.dat";
	cout << "������� �������� ����� ��� ���������� ������" << endl;
	cin >> filename;
	Worker* Sheet = read(filename);
	if (Sheet == 0) {
		return 0;
	}
	print(Sheet);
	Sheet = sort(Sheet);
	cout << endl;
	cout << "Sheet after sort: " << endl << endl;
	print(Sheet);

	cout << "������� �������� ��������� ����� ��� ������" << endl;
	cin >> filename_binary;
	cout << "������� �������� ��������� ����� ��� ����������" << endl;
	cin >> filename_read_from_binary;

	write_to_file(Sheet, filename_binary);
	cout << endl << endl;

	// ��������� ������� �������� ���� worker 
	int sr_zp = 0;
	for (int i = 0; i < ::size; i++) {
		sr_zp = sr_zp + Sheet[i].ZP;
	}
	sr_zp = sr_zp / ::size;

	print_from_binary(sr_zp, filename_read_from_binary);

	return 0;
}