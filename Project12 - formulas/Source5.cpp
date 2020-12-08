// Подключаем библиотеки
#include <iostream>
#include <vector>

// Используем стандартное пространство имён
using namespace std;

int main(){
	int n, m; // Размер матрицы
	cout << "Vvedite n, m" << endl;
	cin >> n >> m;

	// Инициализируем
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[m];
	// Заполняем с клавиатуры
	int elem;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++){
			cout << "Vvedite M[" << i << "][" << j << "]: ";
			cin >> elem;
			a[i][j] = elem;
		}
		cout << endl;
	}

	// Выводим
	cout << "massiv:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}

	int * b = new int[m];
	int tmp;
	for (int j = 0; j < m; j++){
		// ищем минимальные элементы в столбцах
		b[j] = a[0][j];
		for (int i = 1; i < n; i++)
			if (a[i][j] < b[j])
				b[j] = a[i][j];
	}
	// Сортируем пузырьком
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
	// Выводим отсортированный массив
	cout << "poluchennyi massiv:" << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}

	return 0;
}