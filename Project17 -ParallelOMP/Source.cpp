#include <iostream>
#include <ctime>
#include <omp.h>
#include <stdio.h>

using namespace std;

// Последовательное вычисление частичных сумм массива in и запись их в новый массив out
int* sum_arr_posled(int* massiv_in, int size) {
	int* massiv_out = new int[size];
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += massiv_in[i];
		massiv_out[i] = sum;
	}
	return massiv_out;
}

// функция для конкретного потока при параллельном вычислении
void func(int* segment, int thread, int* h, int size, int num_thread) {
	int* h0 = new int[size / num_thread];
	int* h1 = new int[size / num_thread];
	for (int i = 0; i < size / num_thread; i++) {
		h0[i] = 0;
		h1[i] = 0;
	}

	for (int i = 0; i < size / num_thread; i++) {
		if (thread != 0) {
			for (int j = 0; j < thread; j++) {
				for (int k = 0; k <= i; k++)
					h0[i] += segment[j + k * num_thread];
			}
		}
		if (thread != num_thread - 1) {
			for (int j = thread + 1; j < num_thread; j++) {
				for (int k = 0; k < i; k++)
					h1[i] += segment[j + k * num_thread];
			}
		}
		for (int j = 0; j <= i; j++)
			h[i * num_thread + thread] += segment[thread + j * num_thread];
		h[i * num_thread + thread] += h0[i] + h1[i];
	}

	/*
	if (thread != 0) {
		for (int i = 0; i < size / num_thread; i++){
			for (int j = 0; j < thread; j++) {
				for (int k = 0; k <= i; k++) {
					h0[i] += segment[j + k * num_thread];
					//cout << "s[" << thread - 1 << "][" << k << "]: " << segment[thread - 1][k] << " ";
				}
				//cout << "h0[" << i << "]: " << h0[i] << endl;
			}
			//cout << endl;
		}
	}
	if (thread != num_thread - 1) {
		for (int i = 0; i < size / num_thread; i++) {
			for (int j = thread + 1; j < num_thread; j++) {
				for (int k = 0; k < i; k++) {
					h1[i] += segment[j + k * num_thread];
					//cout << "s[" << thread + 1 << "][" << k << "]: " << segment[thread + 1][k] << " ";
				}
				//cout << "h1[" << i << "]: " << h1[i] << endl;
			}
			//cout << endl;
		}
	}*/
	/*
	for (int i = 0; i < size / num_thread; i++) {
		for (int j = 0; j <= i; j++)
			h[i * num_thread + thread] += segment[thread + j * num_thread];
		h[i * num_thread + thread] += h0[i] + h1[i];
	}*/
	delete[] h0;
	delete[] h1;
}

// Параллельное вычисление частичных сумм массива in и запись их в новый массив out 
int* sum_arr_parall(int* massiv, int size, int num_thread) {

	int* h = new int[size];

#pragma omp parallel for num_threads(num_thread)
	for (int i = 0; i < size; i++) {
		h[i] = 0;
	}

#pragma omp parallel for num_threads(num_thread)
		for (int i = 0; i < num_thread; i++) {
			func(massiv, omp_get_thread_num(), h, size, num_thread);
		}
	return h;
}

// Генерируем случайный массив размера size
int* generate_massive(int size) {

	int* massiv = new int[size];

	srand(time(0)); // инициализация генерации случайных чисел

	// генерируем целый случайный массив из 10 элементов от 1 до 10
	
	for (int i = 0; i < size; i++)
		massiv[i] = rand() % 10;
	//for (int i = 0; i < size; i++)
		//massiv[i] = 5 + 5 * i;

	return massiv;
}

// Функция вычисления размера массива M
void sizeMfun() {

	//int M = 0;
	unsigned int start_time;
	unsigned int end_time;
	unsigned int search_time1;
	unsigned int search_time2;
	int num_thread = 16;

	for (int size = 2; size <= 50000; size *= 2) {
		//for (int size = 16; size <= 16; size *= 2) {
		int* array = new int[size];
		int* sum_posled = new int[size];
		int* sum_parall = new int[size];
		array = generate_massive(size);

		start_time = clock(); // начальное время
		sum_posled = sum_arr_posled(array, size);
		end_time = clock(); // конечное время
		search_time1 = end_time - start_time; // искомое время

		start_time = clock(); // начальное время
		sum_parall = sum_arr_parall(array, size, num_thread);
		end_time = clock(); // конечное время
		search_time2 = end_time - start_time; // искомое время

		cout << "size: " << size << endl;
		cout << "Posled Time: " << search_time1 << endl;
		cout << "Parall Time: " << search_time2 << endl;

		/*
		cout << "\nMassiv: " << endl;
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}

		cout << "\nPosled massiv: " << endl;
		for (int i = 0; i < size; i++) {
			cout << sum_posled[i] << " ";
		}

		cout << "\nParall massiv: " << endl;
		for (int i = 0; i < size; i++) {
			cout << sum_parall[i] << " ";
		}
		*/

		delete[] sum_parall;
		delete[] array;
		delete[] sum_posled;
	}
}

void diagramm(int M) {
	int size = 2 * M;
	unsigned int start_time;
	unsigned int end_time;
	unsigned int search_time;
	int* array = new int[size];
	int* sum_parall = new int[size];
	int i = 0;
	for (int num_thread = 1; num_thread <= 16; num_thread *= 2){
		array = generate_massive(size);
		start_time = clock(); // начальное время
		sum_parall = sum_arr_parall(array, size, num_thread);
		end_time = clock(); // конечное время
		search_time = end_time - start_time; // искомое время
		i++;

		cout << "num_threads: " << num_thread << endl;
		cout << "time: " << search_time << endl;

		delete[] sum_parall;
		delete[] array;
	}
}

int main() {

	
	int size = 16;
	int num_thread = 2;
	int* array = new int[size];
	int* sum_posled = new int[size];
	int* sum_parall = new int[size];

	array = generate_massive(size);
	
	cout << "Massiv: " << endl;
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	sum_posled = sum_arr_posled(array, size);
	cout << "Posled massiv: " << endl;
	for (int i = 0; i < size; i++) {
		cout << sum_posled[i] << " ";
	}
	cout << endl;
	sum_parall = sum_arr_parall(array, size, num_thread);
	cout << "Parall massiv: " << endl;
	for (int i = 0; i < size; i++) {
		cout << sum_parall[i] << " ";
	}
	cout << endl;
	delete[] sum_parall;
	delete[] array;
	delete[] sum_posled;

	sizeMfun();

	diagramm(16384);

	cout << "End" << endl;

	return 0;
}
