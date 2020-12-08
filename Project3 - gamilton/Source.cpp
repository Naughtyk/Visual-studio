#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

// Функция поиска гамильтонова пути
bool gamilton(int start, int** a, bool* c, int* path, int* r, int m){
	int cur = start; // Текущий
	int next = 0; // Следующий
	path[next++] = cur; // Запись в конечный путь текущей вершины
	bool found; // флажок

	// Цикл до тех пор, пока не все вершины не будут записаны в путь
	while (true)
	{
		found = false;
		c[cur] = true; // Записываем в массив текущую вершину, так как она посещена

		// Цикл по всем не пройденным вершинам
		for (int i = r[cur] + 1; i < m; i++)
			// Если это не текущая вершина и из текущей вершины есть путь в эту вершину и эта
			// вершина не была посещена, то
			if (i != cur && (a[cur][i]) && !c[i]){
				found = true; // флажок говорит о том, что мы ушли в следующую вершину
				r[cur] = i;
				path[next++] = cur = i; // Сначала добавляем в путь текущую вершину, затем
				// прыгаем в следующую
				break;
			}
		// Если в цикле не было найдено ни одной вершины, куда можно было бы прыгнуть, то
		if (!found) {
			if (next == 1) return false; // Если следующая вершина - первая, то до свидания
			r[cur] = -1;
			c[cur] = false; // Говорим, что текущая вершина снова была не посещена, так как мы отсюда ушли
			cur = path[--next - 1]; // уходим из текущей вершины в предыдущую в нашем пути
		}
		else
			// Если мы прошлись по всем вершинам и есть путь из последней в первую, то спасибо
			if (next == m && (a[cur][start])) return true;
	}
}

// Функция добавления или удаления вершины
int** adddel_v(int** a, vector<string>& vect, int& m) {
	// a - матрица смежности, m - размерность матрицы
	char versh1[256];
	cout << "1 - добавить вершину, 2 - удалить вершину\n";
	int k;
	cin >> k;
	if (k != 1 && k != 2) {
		cout << "Введено неверное число, возвращаемся в меню\n";
		return a;
	}
	cout << "Укажите название вершины\n";
	cin >> versh1;
	int** matrix = 0; // Инициализируем новую матрицу
	if (k == 1) {
		// Ищем вершину с таким названием
		auto iter = find(vect.begin(), vect.end(), versh1);
		if (iter != vect.end()) {
			cout << "Вершина с таким названием уже есть\n";
			return a;
		}
		// Если не нашли, то добавляем её
		vect.push_back(versh1);
		m++; // Размерность увеличивается
		matrix = new int* [m];
		// Новую матрицу заполняем исходя из старой плюс нулевая строка и нулевой столбец
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
		// Ищем вершину с таким названием
		auto iter = find(vect.begin(), vect.end(), versh1);
		if (iter == vect.end()) {
			cout << "Указанной вершины нет\n" << endl;
			return a;
		}
		// Если она найдена, идём дальше
		int index = distance(vect.begin(), iter); // Ищем индекс вершины для матрицы смежности
		vect.erase(iter); // Удаляем её из вектора
		m--; // Уменьшаем размерность матрицы
		matrix = new int* [m];
		// Заполняем новую матрицу старыми элементами, исключая удалённую вершину
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

		// Освобождаем память 
		delete a;
	}
	// Возвращается новая матрица
	return matrix;
}

// Функция добавления или удаления ребра
void adddel_r(int** a, vector<string> vect) {
	char versh1[256], versh2[256];
	cout << "Выберите вершины v1, v2, соединяемые ребром: \n";
	cin >> versh1 >> versh2;
	int l=-1, m=-1; int l = -1, m = -1; // числа, указывающие на строку и столбец для матрицы смежности
	for (size_t i = 0; i < vect.size(); ++i) {
		char* chrstr = new char[vect[i].length() + 1];
		strcpy(chrstr, vect[i].c_str());
		if (strcmp(chrstr, versh1) == 0) { l = i; } // Строка выполнится, если найдётся такая вершина versh1 в векторе
		if (strcmp(chrstr, versh2) == 0) { m = i; } // Строка выполнится, если найдётся такая вершина versh2 в векторе
	}
	if (l == -1 || m == -1) {
		cout << "Указанной(-ых) вершин(-ы) не обнаружено\n";
		return;
	}
	if(a[l][m] == 1){
		cout << "Ребро удалено\n";
		a[l][m] = 0; }
	else{
		a[l][m] = 1;
		cout << "Ребро добавлено\n";
	}
	
}

// Функция изменения направления ребра
void change_r(int** a, vector<string> vect) {
	char versh1[256], versh2[256];
	cout << "Выберите вершины v1, v2, соединяемые ребром:\n";
	cin >> versh1 >> versh2;

	int l = -1, m = -1; // числа, указывающие на строку и столбец для матрицы смежности
	for (size_t i = 0; i < vect.size(); ++i) { 
		char* chrstr = new char[vect[i].length() + 1];
		strcpy(chrstr, vect[i].c_str());
		if (strcmp(chrstr, versh1) == 0) { l = i; } // Строка выполнится, если найдётся такая вершина versh1 в векторе
		if (strcmp(chrstr, versh2) == 0) { m = i; } // Строка выполнится, если найдётся такая вершина versh2 в векторе
	}
	if (l == -1 || m == -1) {
		cout << "Указанной(-ых) вершин(-ы) не обнаружено\n";
		return;
	}
	if (a[m][l] == 1 && a[l][m] == 1) {
		cout << "Ребро двунаправленно\n";
		return;
	}
	if (a[m][l] == 0) {
		cout << "Такого ребра нет\n";
		return;
	}
	else {
		cout << "Ребро перенаправлено\n";
		a[m][l] = 0;
		a[l][m] = 1;
	}
}

// Функция изменения названия вершины
vector<string> change_v(int** a, vector<string> vect) {
	char versh1[256], versh2[256];
	//string versh1, versh2;
	
	cout << "Укажите название вершины, которое нужно изменить: \n";
	cin >> versh1;

	cout << "Введите новое название: \n";
	cin >> versh2;
	
	auto iter = std::find(vect.begin(), vect.end(), versh1); // Итератор, указывающий на найденный в векторе элемент
	if (iter != vect.end()) // Если элемент нашёлся
		* iter = versh2; // Меняем элемент на новый
	else
		cout << "Вершины с таким названием нет";
	return vect;
}

// Функция вывода вектора названий вершин
void show_vector(vector<string> a){
	for (auto it = a.begin(); it != a.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

// Функция вывода матрицы смежности
void show_matrix(int** matrix, int m) {
	// Вывод матрицы смежности 
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

}

// Вывод меню
void Menu()
{
	cout << "              Меню:" << endl;
	cout << "1. Добавить или удалить вершину." << endl;
	cout << "2. Добавить или удалить ребро." << endl;
	cout << "3. Изменить название вершины." << endl;
	cout << "4. Изменить направление ребра." << endl;
	cout << "5. Вывести названия вершин." << endl;
	cout << "6. Вывести матрицу смежности." << endl;
	cout << "7. Найти гамильтонов путь." << endl;
	cout << "8. Считать данные из файла." << endl;
	cout << "0. Выход" << endl;
	cout << '\n';
	cout << "Выбрать:" << endl;
}

// Считывание числа из потока ввода
int get(int min, int max){
	int x;
	while (!(cin >> x) || (x > max) || (x < min)){
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Неверное число, введите заново" << endl;
	}
	return x;
}

// Считывание из файла
void FromFile(vector<string> vect, int** matrix, int m) {
// Считывание из файла и заполнение matrix
	string line;
	string path;
	cout << "Введите название файла (путь к файлу) для считывания: " << endl;
	cin >> path;

	ifstream in(path); // открываем файл для чтения
	if (in.is_open()){
		// Сперва считываем названия вершин
		while (getline(in, line)) {
			if (line == "#") { break; }
			vect.push_back(line.substr(line.find(" ") + 1));
			m++;
		}
		// Выделяем динамическую память для матрицы смежности
		matrix = new int* [m];
		for (int i = 0; i < m; i++)
			matrix[i] = new int[m];

		// Заполняем её нулями
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				matrix[i][j] = 0;
			}
		}

		// Считываем остальные строки файла - рёбра
		while (getline(in, line)) {
			// В этой переменной будет храниться строка
			char* chrstr = new char[line.length() + 1];
			// Копируем в неё строку
			strcpy(chrstr, line.c_str());
			// Далее делим строку на "слова" по пробелам
			char* f = strtok(chrstr, " ");
			int i = 0, j = 0, k = 0;
			while (f) {
				if (k == 0) {
					i = stoi(f); // Преобразуем String в Int - индекс строк для матрицы смежности
					f = strtok(NULL, " ");
					k++;
				}
				else {
					j = stoi(f); // Преобразуем String в Int - индекс стобцов для матрицы смежности
					f = strtok(NULL, " ");
					break;
				}
			}
			// Считанные i, j - индексы строки и столбца для матрицы смежности
			matrix[i - 1][j - 1] = 1;
			delete[] chrstr;
		}
	}
	else {
		cout << "Файла с таким названием не найдено\n";
	}
	in.close(); // закрываем файл
}

int main() {

	vector<string> vect; // Вектор, содержащий названия вершин
	setlocale(LC_ALL, ""); // Устанавливаем русский текст
	int** matrix = 0; // Матрица смежности
	int m = 0; // Размерность матрицы (количество вершин)

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
			bool* c = new bool[m]; // Массив, содержащий вершины, которые уже были песещены
			int* path = new int[m]; // Массив, содержащий гамильтонов путь
			int* r = new int[m]; // Массив, содержащий количество пройденных уже вершин

			printf("Solution:\n");
			for (int i = 0; i < m; i++) {
				c[i] = false;
				r[i] = -1;
			}
			if (gamilton(0, matrix, c, path, r, m)){ // Вызываем функцию, которая вернёт 1, если путь нашёлся, иначе 0
				for (int i = 0; i < m; i++) {
					cout << vect[path[i]] << " "; // Выводим путь
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
			cout << "До свидания!";
			return 0;
		}
		default:
			cout << "Введите число из списка\n";
			break;
		}
	}
}