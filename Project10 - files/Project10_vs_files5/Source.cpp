// Подключаем библиотеки
#include <fstream>
#include <string>
#include <iostream>

// Используем стандартное пространство имён
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS"); // Кириллица
    string filename;
    cout << "Введите название файла: " << endl;
    cin >> filename;
    string str;
    ifstream file(filename); // Открываем файл

    // Если он есть - читаем строку
    if (file) {
        getline(file, str);
    }
    else {
        cout << "Файл не найден" << endl;
        return 0;
    }
    file.close();

    // Считаем максимальный отступ от 0
    int min = 0, max = 0, k = 0;
    for (auto i: str) {
        if (i == 'L') {
            k--;
            if (min > k)
                min = k;
        }
        if (i == 'R') {
            k++;
            if (max < k)
                max = k;
        }
    }
    // Выводим ответ
    cout << max + abs(min) + 1 << endl;

    return 0;
}