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
    ifstream file(filename);

    // Если файл есть - читаем строку
    if (file) {
        getline(file, str);
    }
    else {
        cout << "Файл не найден" << endl;
        return 0;
    }

    bool flag = false; // 2 - против часовой 
    for (int i = 0; i < size(str); i++) {
        if (str[i] == 'A') // Если А - то шестеренка меняет направление
            flag = !flag;
        else if (str[i] == 'C') // Если С - то шестеренка меняет направление
            flag = !flag;
    }
    if (flag == false)
        cout << 2 << endl;
    else
        cout << 1 << endl;

    return 0;
}