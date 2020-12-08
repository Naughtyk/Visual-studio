/*
4.  Пароль. Пароль – это произвольная строка из английских букв или цифр.
Надёжный пароль – это тот, в котором есть и «маленькие» английские буквы,
и «большие» английские буквы, и цифры, а его длина не менее 8 символов.
В текстовом файле хранится некоторая последовательность символов.
Программа выводит сообщение «это вообще не пароль», или «это пароль,
но ненадёжный», или «это надёжный пароль».
*/

// Подключаем библиотеки
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

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

    bool flag1 = true, // Есть ли большие буквы
        flag2 = true, // Есть ли маленькие буквы
        flag3 = false, // Есть ли цифры
        flag4 = false; // больше 8 букв или нет

    // Создаем вспомогательную строку, чтобы с ней сравнивать исходную
    string str2;
    str2 = str;

    transform(str2.begin(), str2.end(), str2.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if (str == str2)
        flag1 = false; // Больших букв нет

    transform(str2.begin(), str2.end(), str2.begin(),
        [](unsigned char c) { return std::toupper(c); });

    if (str == str2)
        flag2 = false; // Маленьких букв нет
    if (any_of(str.begin(), str.end(), [](int i) {return isdigit(i); }))
        flag3 = true; // Цифры есть
    if (size(str) >= 8)
        flag4 = true; // Размер больше восьми

    // Если строка пустая
    if (size(str) == 0) {
        cout << "Это вообще не пароль" << endl;
        return 0;
    }

    // Если все флаги - "хорошие"
    if (flag1 == true && flag2 == true && flag3 == true && flag4 == true) {
        cout << "Это надёжный пароль" << endl;
    }
    // Иначе
    else {
        cout << "Это пароль, но ненадёжный" << endl;
    }
    return 0;
}