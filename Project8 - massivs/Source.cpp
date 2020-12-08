#define _CRT_SECURE_NO_WARNINGS 
// Чтобы работали функции, возвращающие указатели

// Подключаем библиотеки
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>

// Используем стандартное пространство имён
using namespace std;

// Функция для считывания корректного номера выбора в меню
int get_variant(int count) {
    int variant;
    char s[100]; // строка для считывания введённых данных
    scanf("%s", s); // считываем строку

    // пока ввод некорректен, сообщаем об этом и просим повторить его
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
        printf("Incorrect input. Try again: "); // выводим сообщение об ошибке
        scanf("%s", s); // считываем строку повторно
    }
    return variant;
}

// Нарисовать меню
void print_menu() {
    cout << " Нажмите <1> для считывания массива из файла" << endl;
    cout << " Нажмите <2> для вывода массива на экран" << endl;
    cout << " Нажмите <3> для решения задачи1" << endl;
    cout << " Нажмите <4> для решения задачи2" << endl;
    cout << " Нажмите <5> для решения задачи3" << endl;
    cout << " Нажмите <6> для решения задачи4" << endl;
    cout << " Нажмите <7> для решения задачи5" << endl;
	cout << " Нажмите <8> для считывания матрицы из файла" << endl;
	cout << " Нажмите <9> для вывода матрицы на экран" << endl;
    cout << " Нажмите <10> для выхода" << endl;
}

// вывести на экран массив
void print_massiv(int* massiv, int n) {
	for (int i = 0; i < n; i++)
		cout << massiv[i] << " ";
	cout << endl;
}

// вывести на экран матрицу
void print_matrix(int** matrix, int m, int k) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

// Чтение массива из файла
int* read_from_file(int* massiv, int& n) {
    cout << "Введите название файла: ";
    char file[256];
    string str;
    cin >> file;
    ifstream i(file);

	// Если файл открыт
    if (i) {
        getline(i, str); // читаем построчно
        n = atoi(str.c_str()); // преобразуем в int (размер массива)
        massiv = new int[n];
		// Далее считываем сам массив
        for (int j = 0; j < n; j++) {
            getline(i, str);
            massiv[j] = atoi(str.c_str());
        }
    }
    else {
        cout << "Файл не найден" << endl;
    }
    i.close(); // закрываем файл
	// возвращаем массив
    return massiv;
}

// Чтение матрицы из файла
int** read_matrix_from_file(int** matrix, int &m, int &k) {
	string path;
	string line;
	cout << "Введите название файла (путь к файлу) для считывания: " << endl;
	cin >> path;
	ifstream in(path); // открываем файл для чтения

	if (in.is_open()) {
		getline(in, line);
		// В этой переменной будет храниться строка
		char* chrstr = new char[line.length() + 1];
		// Копируем в неё строку
		strcpy(chrstr, line.c_str());
		// Далее делим строку на "слова" по пробелам
		char* f = strtok(chrstr, " ");
		m = stoi(f); // Строки
		f = strtok(NULL, " ");
		k = stoi(f); // Столбцы

		// Выделяем динамическую память для матрицы
		matrix = new int* [m];
		for (int i = 0; i < m; i++)
			matrix[i] = new int[k];

		// Заполняем её нулями
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				matrix[i][j] = 0;
			}
		}

		// Далее считываем построчно матрицу
		for (int i = 0; i < m; i++) {
			getline(in, line);
			// В этой переменной будет храниться строка
			char* chrstr = new char[line.length() + 1];
			// Копируем в неё строку
			strcpy(chrstr, line.c_str());
			// Далее делим строку на "слова" по пробелам
			char* f = strtok(chrstr, " ");
			for (int j = 0; j < k; j++) {
				matrix[i][j] = stoi(f);
				f = strtok(NULL, " ");
			}
			delete[] chrstr;
		}
	}
	else {
		cout << "Файла с таким названием не найдено\n";
	}
	in.close(); // закрываем файл
	// Возвращаем матрицу
	return matrix;
}

// Решаем первую задачу "Горящие коробки"
void task1(int* massiv, int n) {
	if (n == 0) {
		cout << "Массив пустой" << endl;
		return;
	}
	if (n == 1) {
		cout << massiv[0] << endl;
		return;
	}

    int box_number;
    cout << "Введите номер коробки: ";
    cin >> box_number;
    int time1 = 0; // Время до выбранной коробки
    int time2 = 0; // Время после выбранной коробки

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

// Решаем вторую задачу "Встреча"
void task2(int* massiv, int n) {
	if (n == 0) {
		cout << "Массив пустой" << endl;
		return;
	}
	if (n == 1) {
		cout << "Номер дома - 0" << endl;
		return;
	}
	int sum = 0;
	// Сначала суммируем все расстояния
	for (int i = 0; i < n; i++) {
		sum += massiv[i];
	}
	// Находим среднее
	int average = sum / n;
	int min = massiv[n-1];
	int index = 0;
	// Далее ищем минимум
	for (int i = 0; i < n; i++) {
		if (abs(massiv[i] - average) < min) {
			min = abs(massiv[i] - average);
			index = i; // записываем индекс минимума
		}
	}
	cout << "Номер дома - " << index << endl;
}

// Решаем третью задачу "Бомбы"
void task3(int* massiv, int n) {

	// Сначала рассматриваем крайние случаи
	if (n == 0) {
		cout << "Массив пустой" << endl;
		return;
	}
	if (n == 1) {
		if (massiv[0] == 0)
			cout << "Количество целых клеток - 1" << endl;
		else
			cout << "Количество целых клеток - 0" << endl;
		return;
	}

	// Создаем вспомогательный массив, на котором будем отмечать взорванные поля
	int* massiv2 = new int[n];
	for (int i = 0; i < n; i++)
		massiv2[i] = massiv[i];
	// Сперва смотрим по краям массива
	if (massiv[0] == 1) {
		massiv2[0] = 1;
		massiv2[1] = 1;
	}
	if (massiv[n - 1] == 1) {
		massiv2[n - 2] = 1;
		massiv2[n - 1] = 1;
	}
	// Затем по всему остальному массиву
	for (int i = 1; i < n - 1; i++) {
		if (massiv[i] == 1) {
			massiv2[i - 1] = 1;
			massiv2[i] = 1;
			massiv2[i + 1] = 1;
		}
	}
	// Теперь считаем клетки, которые уцелели (0)
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (massiv2[i] == 0)
			sum++;
	}
	cout << "Количество целых клеток - " << sum << endl;
	delete [] massiv2;
}

// Решаем четвертую задачу "Форма для льда"
void task4(int** matrix, int m, int k) {
	// Сразу считаем весь лёд
	int sum = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < k; j++)
			sum += matrix[i][j];
	// крайние случаи, если матрица - это одномерный массив
	if (m == 1) {
		for (int j = 1; j < k - 1; j++)
			if (matrix[0][j] == 1 && matrix[0][j - 1] == 0 && matrix[0][j + 1] == 0)
				sum--;
		cout << "Ячеек со льдом останется через час - " << sum << endl;
		return;
	}
	if (k == 1) {
		for (int i = 1; i < m - 1; i++)
			if (matrix[i][0] == 1 && matrix[i - 1][0] == 0 && matrix[i + 1][0] == 0)
				sum--;
		cout << "Ячеек со льдом останется через час - " << sum << endl;
		return;
	}
	// Если матрица нормальная, то смотрим сначала все углы
	if (matrix[0][0] == 1 && matrix[0][1] == 0 && matrix[1][0] == 0)
		sum--;
	if (matrix[m - 1][k - 1] == 1 && matrix[m - 2][k - 1] == 0 && matrix[m - 1][k - 2] == 0)
		sum--;
	if (matrix[m - 1][0] == 1 && matrix[m - 1][1] == 0 && matrix[m - 2][0] == 0)
		sum--;
	if (matrix[0][k - 1] == 1 && matrix[0][k - 2] == 0 && matrix[1][k - 1] == 0)
		sum--;
	// Затем все края
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
	// И наконец всё, что не по краям
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
	cout << "Ячеек со льдом останется через час - " << sum << endl;
}

// Решаем пятую задачу "Супер-бомбы"
void task5(int** matrix, int m, int k) {
	int sum = 0;
	// Смотрим сначала крайние случае, если матрица - это одномерный массив
	if (m == 1) {
		for (int j = 0; j < k ; j++)
			if (matrix[0][j] == 1){
				cout << "Клеток останется целыми - " << 0 << endl;
				return;
			}
		cout << "Клеток останется целыми - " << k << endl;
		return;
	}
	if (k == 1) {
		for (int i = 0; i < m; i++)
			if (matrix[i][0] == 1) {
				cout << "Клеток останется целыми - " << 0 << endl;
				return;
			}
		cout << "Клеток останется целыми - " << m << endl;
		return;
	}

	// Иначе создаем вспомогательную матрицу, по аналогии с задачей 3
	int** matrix2 = new int* [m];
	for (int i = 0; i < m; i++)
		matrix2[i] = new int[k];
	// Заполняем её нулями
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			matrix2[i][j] = 0;
		}
	}
	// Взрываем все строки и столбцы, где есть бомба
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
	// Считаем уцелевшие клетки
	for (int i = 0; i < m; i++)
		for (int j = 0; j < k; j++)
			if (matrix2[i][j] == 0)
				sum++;
	cout << "Клеток останется целыми - " << sum << endl;
}

int main(){
    setlocale(LC_ALL, "Russian");

    int variant; // для выбора в меню
    int* massiv = nullptr; // Массив
	int** matrix = 0; // Матрица
    int n = 0; // Размерность массива
	int m = 0, k = 0; // Размерность матрицы

    do {
        print_menu(); // выводим меню на экран
        variant = get_variant(10); // получаем номер выбранного пункта меню
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
            system("pause"); // задерживаем выполнение, чтобы пользователь мог увидеть результат выполнения выбранного пункта
    } while (variant != 10);
    return 0;
}