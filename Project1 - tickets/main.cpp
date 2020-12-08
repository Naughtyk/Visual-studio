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

// ��� �� � �������
void print(string x) {
	cout << x << endl;
}

// ������� ������
void print_quest(int num, vector<Question> base) {
	cout << "����� �������: " << base[num].num << endl;
	cout << "���������: " << base[num].diff << endl;
	cout << "����������: " << base[num].sect << endl;
	cout << "������: " << base[num].text << endl;
}

// ������� ��� ����
void print_base(vector <Question> base, int size) {

	if (size == 0) {
		cout << "���� �����" << endl;
	}
	for (int i = 0; i < size; i++)
	{
		print_quest(i, base);
	}
}

// ������� ������ �������� � ������
void print_tick(Ticket tick) {
	for (int i = 0; i < tick.lot; i++)
	{
		cout << "������ �" << i + 1 << ":" << endl;
		cout << "����������: " << tick.que[i].sect << endl;
		cout << "���������: " << tick.que[i].diff << endl;
		cout << "������: " << tick.que[i].text << endl;
	}
}

// ������� ��� ��������� ������ �� ���������� ��������� �� ����
Ticket gen_tick(vector<Question> base, vector<Ticket> Tickets, int size, int size_easy, int size_disc[3]) {

	Ticket tick;
	if (size == 0) {
		cout << "� ���� ��� ��������. �������� ������� ������ � ����\n";
		return tick;
	}

	cout << "������� �������� ���������� ��������: " << endl;
	int num_of_quests;
	cin >> num_of_quests;
	if (num_of_quests < 0) { cout << "������������� ����� ��������? �������� �����������, ��� �� ���� ��� �������������?" << endl; }
	if (num_of_quests >= size_easy + 2 || num_of_quests > size) {
		cout << "������� ����� �������� (���� ���������� *�������* �������� � ���� �� �������)" << endl;
		return tick;
	}

	// ���������� � ����� ������
	tick.lot = num_of_quests;
	//tick.num = iter++;

	// ������� �� ������, ���� �������������� ������������� �������� � ���� ���
	if (int(num_of_quests / 3) > size_disc[0] ||
		int(num_of_quests / 3) > size_disc[1] ||
		int(num_of_quests / 3) > size_disc[2]) {
		cout << "������������ ������������� �������� �� ����������� �� ���������, ��� ��� � ���� ��� ������������ ������������" << endl;
		return tick;
	}

	// ������� �� ������, ���� ����� �������� � ���� = ����� �������� � ������
	if (num_of_quests == size && size <= size_easy + 1) {
		for (int i = 0; i < num_of_quests; i++) {
			tick.que.push_back(base[i]);
		}
		Tickets.push_back(tick);
		print_tick(tick);
		return tick;
	}

	// ������� �� ������, ���� ����� �������� � ���� = ����� ������� �������� � ������ + 1
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

	vector <int> mass; // ������, ���������� ������ ��������, ������� ��� ���� � ������

	int rnd = 0; // �������������� ����������, �������������� ����� ��������� ��������
	bool flag = false; // ������ � ���, �������� �� ��� ������� ������ � �����
	if (size == size_easy) { flag == true; } // ���������, ���� ��� ������� ��������, ����� ����� ��������� ����� �������� ���������

	int i = 0;
	int cur_disc = rand() % 3 + 1; // ������� ����������, ���������� �� ���������. ����� ��� ������������ ������������� ���������

	// ����, ���� �� ���������� �����
	while (i < num_of_quests) {
		rnd = (i + rand() % size) % size;
		if (base[rnd].diff == false) {
			if (flag == false) {
				if (cur_disc % 3 + 1 != base[rnd].sect) { continue; }
				// ����� ��������� ������� ������
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
			// ����� ��������� ������� ������
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

// ����� ����
void Menu()
{
	cout << "              ����:" << endl;
	cout << "1. �������� ������ � ���� ��������." << endl;
	cout << "2. ������� ���� ��������." << endl;
	cout << "3. ������������� ������." << endl;
	cout << "4. ������������� �����." << endl;
	cout << "5. ��������� ���� � ����." << endl;
	cout << "6. ������� ���� �� �����." << endl;
	cout << "0. �����" << endl;
	cout << '\n';
	cout << "�������:" << endl;
}

int get(int min, int max)
{
	int x;
	while (!(cin >> x) || (x > max) || (x < min))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "�������� �����, ������� ������" << endl;
	}
	return x;
}

vector<Question> ch_q(vector<Question> base, int *size_easy, int &size_disc, int *size)
{
	Question quest;
	string str;
	int *p = &size_disc;

	cout << "�������� ��������� (1 - ������, 0 - ������), \n";
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
	cout << "�������� ��������� (1 - ����������������, 2 - ���, 3 - �����������), \n";

	switch (get(1, 3))
	{
	case 1:
		cout << "������� ������ \n";
		cin >> str;
		p[0]++;
		quest.sect = 1;
		quest.text = str;
		quest.num = (*size)++;
		base.push_back(quest);
		cout << "������ �������� � ���� \n";
		break;
	case 2:
		cout << "������� ������ \n";
		cin >> str;
		p[1]++;
		quest.sect = 2;
		quest.text = str;
		quest.num = (*size)++;
		base.push_back(quest);
		cout << "������ �������� � ���� \n";
		break;
	case 3:
		cout << "������� ������ \n";
		cin >> str;
		p[2]++;
		quest.sect = 3;
		quest.text = str;
		quest.num = (*size)++;
		base.push_back(quest);
		cout << "������ �������� � ���� \n";
		break;
	default:
		break;
	}
	return base;
}

// ������� ��� ��������� ��������� �������
vector<Question> edit_quest(vector<Question> base, int size)
{
	if (size == 0) {
		cout << "� ���� ��� ��������. �������� ������� ������ � ����\n";
		return base;
	}
	cout << "�������� ����� �������" << endl;
	int num;
	cin >> num;
	if (num >= size || num < 0) {
		cout << "� ���� ��� �������� � ����� �������.\n";
		return base;
	}

	// ���� ������ - 1, �� ������ �� 0 � ��������
	if (base[num].diff == true) {
		base[num].diff = false;
	}
	else {
		base[num].diff = true;
	}
	cout << "������ ������� ������" << endl;
	return base;
}

// ������� ���������� ���� ������ �� �����
vector<Question> FromFile(vector<Question> base, int *size, int *size_easy, int &size_disc) {
	string path;
	cout << "������� �������� �����:" << endl;
	cin >> path;
	ifstream file(path);
	if (!file.is_open()) {
		cout << "������ ����� ���" << endl;
		return base;
	}
	int* p = &size_disc;
	// ��������� ���� �� �������� � ���������� � ����
	while (!file.eof()) {
		Question quest;
		string sdiff, ssect;
		getline(file, sdiff);
		if (sdiff == "") { break; } // ���� ��� ����� �����, �� ������� �� �����
		getline(file, ssect);
		getline(file, quest.text);
		quest.num = (*size)++; // ������������ � ����������� ������ ����
		quest.diff = stoi(sdiff);
		if (quest.diff == true) { (*size_easy)++; }
		quest.sect = stoi(ssect);
		(p[quest.sect - 1])++;
		base.push_back(quest);
	}
	file.close();
	return base;
}

// ������� ������ � ���� ���� ������
void ToFile(vector<Question> base, int size) {
	if (size == 0) {
		cout << "� ���� ��� ��������. �������� ������� ������ � ����\n";
		return;
	}
	string path;
	cout << "������� �������� �����:" << endl;
	cin >> path;
	ofstream file(path);

	// ���������� ���������
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

	int size_disc[3] = { 0,0,0 }; // ���������� �������� �� ������ ����������
	int size_easy(0); // ���������� ������� ��������
	int size = 0; // ����� ����� �������� � ����
	int iter = 0; // �������� ��� ������������ ������� ��������

	// ��������������
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
			print("�� ��������!");
			return 0;
		}
		default:
			print("������� ����� �� ������");
			break;
		}
	}
}

