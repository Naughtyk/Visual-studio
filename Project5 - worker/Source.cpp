#define _CRT_SECURE_NO_WARNINGS // Чтобы можно было вызвать fopen

// Подключаем библиотеки
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
// Используемся стандартное пространство имён
using namespace std;

// Описываем структуру Worker
struct Worker
{
	string Name;
	string Post;
	int  ZP = 0;
};

// Объявляем глобально размер массива структур Worker, который далее будет считан из файла 1.txt
int size;

// Функция считывания из файла 1.txt массива структур Worker 
Worker* read(string filename){
	string line;
	ifstream in(filename); // окрываем файл для чтения
	if (!in) {
		cout << "Введено неверное имя файла для чтения" << endl;
		return 0;
	}
	getline(in, line);
	::size = atoi(line.c_str()); // Узнаём размер массива из первой строки файла
	Worker* Sheet = new Worker[::size]; // Динамически создаём массив

	// Считываем по очереди всех worker 
	for (int j = 0; j < ::size; j++) {
		getline(in, line);
		Sheet[j].Name = line;
		getline(in, line);
		Sheet[j].Post = line;
		getline(in, line);
		Sheet[j].ZP = atoi(line.c_str());
		getline(in, line);
	}
	in.close(); // закрываем файл
	return Sheet;
}

// Функция вывода на экран всего массива Worker 
void print(Worker* worker)
{
	for (int i = 0; i < ::size; i++) {
		cout << "Name: " << worker[i].Name << endl
			<< "Post: " << worker[i].Post << endl
			<< "ZP: " << worker[i].ZP << endl;
	}
}

// Функция вывода на экран только одного Worker из массива
void print_1_worker(Worker worker)
{
	cout << "Name: " << worker.Name << endl
		<< "Post: " << worker.Post << endl
		<< "ZP: " << worker.ZP << endl;
}

// Функция сортировки массива по фамилиям
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

// Функция записи в бинарный файл всего массива 
void write_to_file(Worker* worker, string filename_binary) {
	// запись массива в файл
	ofstream fout(filename_binary, ios::binary);
	for (int i = 0; i < ::size; ++i){
		fout.write(reinterpret_cast<char*>(&worker[i]), sizeof(Worker));
	}
	fout.close();
}

// Функция сравнения зарплаты worker и средней зарплаты всех worker из массива
bool compare(Worker worker, int sr_zp)
{
	if (worker.ZP > sr_zp) {
		return true;
	}
	else {
		return false;
	}
}

// Функция чтения данных из бинарного файла и вывода на экран тех worker, чьи зарплаты выше средней
void print_from_binary(int sr_zp, string filename_read_from_binary) {
	Worker worker;
	Worker worker_prew;
	FILE* fp;
	fp = fopen(filename_read_from_binary.c_str(), "rb");
	if (!fp) {
		cout << "Введено неверное имя файла чтения данных из бинарного файла" << endl;
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
	// вызываем по очереди функции
	string filename = "1.txt";
	string filename_binary = "2.dat";
	string filename_read_from_binary = "2.dat";
	cout << "Введите название файла для считывания данных" << endl;
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

	cout << "Введите название бинарного файла для записи" << endl;
	cin >> filename_binary;
	cout << "Введите название бинарного файла для считывания" << endl;
	cin >> filename_read_from_binary;

	write_to_file(Sheet, filename_binary);
	cout << endl << endl;

	// Вычисляем среднюю зарплату всех worker 
	int sr_zp = 0;
	for (int i = 0; i < ::size; i++) {
		sr_zp = sr_zp + Sheet[i].ZP;
	}
	sr_zp = sr_zp / ::size;

	print_from_binary(sr_zp, filename_read_from_binary);

	return 0;
}