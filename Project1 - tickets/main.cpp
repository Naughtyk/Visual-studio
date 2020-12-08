#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Question
{
	string text;
	int sect;
	bool diff;
	int num;
};

struct Ticket
{
	int num;
	int lot;
	vector <Question> que;
};

// Это не я написал
void print(string x) {
	cout << x << endl;
}

// Вывести вопрос
void print_quest(int num, vector<Question> base) {
	cout << "Номер вопроса: " << base[num].num << endl;
	cout << "Сложность: " << base[num].diff << endl;
	cout << "Дисциплина: " << base[num].sect << endl;
	cout << "Вопрос: " << base[num].text << endl;
}

// Вывести всю базу
void print_base(vector <Question> base, int size) {

	if (size == 0) {
		cout << "База пуста" << endl;
	}
	for (int i = 0; i < size; i++)
	{
		print_quest(i, base);
	}
}

// Функция вывода вопросов в билете
void print_tick(Ticket tick) {
	for (int i = 0; i < tick.lot; i++)
	{
		cout << "Вопрос №" << i + 1 << ":" << endl;
		cout << "Дисциплина: " << tick.que[i].sect << endl;
		cout << "Сложность: " << tick.que[i].diff << endl;
		cout << "Вопрос: " << tick.que[i].text << endl;
	}
}

// Функция для генерации билета со случайными вопросами из базы
Ticket gen_tick(vector<Question> base, vector<Ticket> Tickets, int size, int size_easy, int size_disc[3]) {

	Ticket tick;
	if (size == 0) {
		cout << "В базе нет вопросов. Добавьте сначала вопрос в базу\n";
		return tick;
	}

	cout << "Укажите желаемое количество вопросов: " << endl;
	int num_of_quests;
	cin >> num_of_quests;
	if (num_of_quests < 0) { cout << "Отрицательное число вопросов? Господин проверяющий, как вы себе это представляете?" << endl; }
	if (num_of_quests >= size_easy + 2 || num_of_quests > size) {
		cout << "Слишком много вопросов (Либо количества *средних* вопросов в базе не хватает)" << endl;
		return tick;
	}

	// Записываем в билет данные
	tick.lot = num_of_quests;
	//tick.num = iter++;

	// Костыль на случай, если неравномерного распределения вопросов в базе нет
	if (int(num_of_quests / 3) > size_disc[0] ||
		int(num_of_quests / 3) > size_disc[1] ||
		int(num_of_quests / 3) > size_disc[2]) {
		cout << "Равномерного распределения вопросов по дисциплинам не получится, так как в базе они распределены неравномерно" << endl;
		return tick;
	}

	// Костыль на случай, если число вопросов в базе = числу вопросов в билете
	if (num_of_quests == size && size <= size_easy + 1) {
		for (int i = 0; i < num_of_quests; i++) {
			tick.que.push_back(base[i]);
		}
		Tickets.push_back(tick);
		print_tick(tick);
		return tick;
	}

	// Костыль на случай, если число вопросов в базе = числу средних вопросов в билете + 1
	if (num_of_quests == size_easy + 1) {
		int i = 0;
		int j = 0;
		while (i < num_of_quests - 1) {
			if (base[j].diff == true) {
				tick.que.push_back(base[j]);
				i++;
			}
			j++;
		}
		i = 0;
		while (i != 1) {
			int rnd = (i + rand() % size) % size;
			if (base[rnd].diff == false) {
				tick.que.push_back(base[rnd]);
				i++;
			}
		}
		Tickets.push_back(tick);
		print_tick(tick);
		return tick;
	}

	vector <int> mass; // Массив, содержащий номера вопросов, которые уже есть в билете

	int rnd = 0; // Инициализируем переменную, представляющую собой случайный итератор
	bool flag = false; // Флажок о том, добавлен ли уже сложный вопрос в билет
	if (size == size_easy) { flag == true; } // Проверяем, если нет сложных вопросов, тогда сразу наполняем билет средними вопросами

	int i = 0;
	int cur_disc = rand() % 3 + 1; // Текущая дисциплина, начинается со случайной. Нужна для равномерного распределения дисциплин

	// Цикл, пока не заполнится билет
	while (i < num_of_quests) {
		rnd = (i + rand() % size) % size;
		if (base[rnd].diff == false) {
			if (flag == false) {
				if (cur_disc % 3 + 1 != base[rnd].sect) { continue; }
				// Здесь добавляем сложный вопрос
				else {
					tick.que.push_back(base[rnd]);
					flag = true;
					i++;
					if (num_of_quests != size_easy + 1) { cur_disc++; }
					mass.push_back(base[rnd].num);
				}
			}
			else { continue; }
		}
		else {
			if (cur_disc % 3 + 1 != base[rnd].sect || find(begin(mass), end(mass), base[rnd].num) != end(mass)) { continue; }
			// Здесь добавляем средний вопрос
			else {
				tick.que.push_back(base[rnd]);
				cur_disc++;
				i++;
				mass.push_back(base[rnd].num);
			}
		}
	}
	Tickets.push_back(tick);
	print_tick(tick);
	return tick;
}

// Вывод меню
void Menu()
{
	cout << "              Меню:" << endl;
	cout << "1. Добавить вопрос в базу вопросов." << endl;
	cout << "2. Вывести базу вопросов." << endl;
	cout << "3. Редактировать вопрос." << endl;
	cout << "4. Сгенерировать билет." << endl;
	cout << "5. Сохранить базу в файл." << endl;
	cout << "6. Считать базу из файла." << endl;
	cout << "0. Выход" << endl;
	cout << '\n';
	cout << "Выбрать:" << endl;
}

int get(int min, int max)
{
	int x;
	while (!(cin >> x) || (x > max) || (x < min))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Неверное число, введите заново" << endl;
	}
	return x;
}

vector<Question> ch_q(vector<Question> base, int *size_easy, int &size_disc, int *size)
{
	Question quest;
	string str;
	int *p = &size_disc;

	cout << "Выберите сложность (1 - Средне, 0 - Сложно), \n";
	switch (get(0, 1))
	{
	case 1:
	{
		quest.diff = true;
		(*size_easy)++;
		break;
	}
	case 0:
		quest.diff = false;
		break;
	default:
		break;
	}
	cout << "Выберите дисцплину (1 - Электромагнетизм, 2 - ТОЭ, 3 - Информатика), \n";

	switch (get(1, 3))
	{
	case 1:
		cout << "Введите вопрос \n";
		cin >> str;
		p[0]++;
		quest.sect = 1;
		quest.text = str;
		quest.num = (*size)++;
		base.push_back(quest);
		cout << "Вопрос добавлен в базу \n";
		break;
	case 2:
		cout << "Введите вопрос \n";
		cin >> str;
		p[1]++;
		quest.sect = 2;
		quest.text = str;
		quest.num = (*size)++;
		base.push_back(quest);
		cout << "Вопрос добавлен в базу \n";
		break;
	case 3:
		cout << "Введите вопрос \n";
		cin >> str;
		p[2]++;
		quest.sect = 3;
		quest.text = str;
		quest.num = (*size)++;
		base.push_back(quest);
		cout << "Вопрос добавлен в базу \n";
		break;
	default:
		break;
	}
	return base;
}

// Функция для изменения сложности вопроса
vector<Question> edit_quest(vector<Question> base, int size)
{
	if (size == 0) {
		cout << "В базе нет вопросов. Добавьте сначала вопрос в базу\n";
		return base;
	}
	cout << "Выберите номер вопроса" << endl;
	int num;
	cin >> num;
	if (num >= size || num < 0) {
		cout << "В базе нет вопросов с таким номером.\n";
		return base;
	}

	// Если вопрос - 1, то меняем на 0 и наоборот
	if (base[num].diff == true) {
		base[num].diff = false;
	}
	else {
		base[num].diff = true;
	}
	cout << "Вопрос успешно изменён" << endl;
	return base;
}

// функция считывания базы данных из файла
vector<Question> FromFile(vector<Question> base, int *size, int *size_easy, int &size_disc) {
	string path;
	cout << "Укажите название файла:" << endl;
	cin >> path;
	ifstream file(path);
	if (!file.is_open()) {
		cout << "Такого файла нет" << endl;
		return base;
	}
	int* p = &size_disc;
	// Считываем файл по строчкам и записываем в базу
	while (!file.eof()) {
		Question quest;
		string sdiff, ssect;
		getline(file, sdiff);
		if (sdiff == "") { break; } // Если это конец файла, то выходим из цикла
		getline(file, ssect);
		getline(file, quest.text);
		quest.num = (*size)++; // Одновременно и увеличиваем размер базы
		quest.diff = stoi(sdiff);
		if (quest.diff == true) { (*size_easy)++; }
		quest.sect = stoi(ssect);
		(p[quest.sect - 1])++;
		base.push_back(quest);
	}
	file.close();
	return base;
}

// функция записи в файл базы данных
void ToFile(vector<Question> base, int size) {
	if (size == 0) {
		cout << "В базе нет вопросов. Добавьте сначала вопрос в базу\n";
		return;
	}
	string path;
	cout << "Укажите название файла:" << endl;
	cin >> path;
	ofstream file(path);

	// Записываем построчно
	for (auto& d : base) {
		file << d.diff << "\n";
		file << d.sect << "\n";
		file << d.text << "\n";
	}
	file.close();
}

int main()
{
	setlocale(LC_ALL, "");

	int size_disc[3] = { 0,0,0 }; // Количество вопросов по каждой дисциплине
	int size_easy(0); // Количество средних вопросов
	int size = 0; // Общее число вопросов в базе
	int iter = 0; // Итератор для присваивания номеров вопросам

	// Инициализируем
	vector <Ticket> Tickets;
	vector <Question> base;

	Menu();
	while (1)
	{
		switch (get(0, 6))
		{
		case 1:
		{
			base = ch_q(base, &size_easy, *size_disc, &size);
			Menu();
			break;
		}
		case 2:
		{
			print_base(base, size);
			Menu();
			break;
		}
		case 3:
		{
			base = edit_quest(base, size);
			Menu();
			break;
		}
		case 4:
		{
			Ticket tick;
			tick = gen_tick(base, Tickets, size, size_easy, size_disc);
			Menu();
			break;
		}
		case 5:
		{
			ToFile(base, size);
			Menu();
			break;
		}
		case 6:
		{
			base = FromFile(base, &size, &size_easy, *size_disc);
			Menu();
			break;
		}
		case 0:
		{
			print("До свидания!");
			return 0;
		}
		default:
			print("Введите число из списка");
			break;
		}
	}
}

