// ���������� ����������
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// ���������� ����������� ������������ ���
using namespace std;

int main(){

	string s;
	vector <int> vect;
	cout << "Vvedite chisla cherez probel: ";
	getline(cin, s);

	// ����� ������ �� �������� � ��������� � ������ �����
	string word = "";
	for (auto x : s){
		if (x == ' '){
			vect.push_back(stoi(word));
			word = "";
		}
		else{
			word = word + x;
		}
	}

	// ��������� � ������� ������� sort ���������� algorithm
	sort(vect.begin(), vect.end());

	// ������� �� �����
	for (auto i: vect) {
		cout << i << " ";
	}

	return 0;
}