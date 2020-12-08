#include <iostream>
#include <cmath>

#define M_PI 3.14159265358979323846

using namespace std;

class Triangle {
private:
	double AB;
	double AC; // Стороны
	double BC;
	int A;
	int B; // Углы
	int C;
	double A_BC;
	double B_AC; // Высоты
	double C_AB;
public:
	Triangle();
	Triangle(double, double, double);
	Triangle(double, double, int);
	Triangle(double, int, int);
	void setAB(double);
	void setBC(double);
	void setAC(double);
	double getAB();
	double getBC();
	double getAC();
	double perim();
	double Area();
	void GetType();
	bool isTriangle();
	~Triangle();
};
Triangle::~Triangle() {}
Triangle::Triangle() {
	AB = 1;
	BC = 1;
	AC = 1;
	A = M_PI / 3;
	B = M_PI / 3;
	C = M_PI / 3;
	A_BC = 0.5;
	B_AC = 0.5;
	C_AB = 0.5;
}
Triangle::Triangle(double ab, double bc, double ac) {
	AB = ab;
	A = acos(ac * ac + ab * ab - bc * bc) / (2 * ac * ab);
	BC = bc;
	B = acos(bc * bc + ab * ab - ac * ac) / (2 * bc * ab);
	AC = ac;
	C = acos(bc * bc + ac * ac - ab * ab) / (2 * ac * bc);
	A_BC = ab * sin(B);
	B_AC = bc * sin(C);
	C_AB = ab * sin(A);
}
Triangle::Triangle(double ab, double bc, int b) {
	AB = ab;
	BC = bc;
	AC = sqrt(bc * bc + ab * ab - 2 * ab * bc);
	B = B * M_PI / 180;
	A = acos(AC * AC + ab * ab - bc * bc) / (2 * AC * ab);
	C = acos(bc * bc + AC * AC - ab * ab) / (2 * AC * bc);
	A_BC = ab * sin(B);
	B_AC = bc * sin(C);
	C_AB = ab * sin(A);
}
Triangle::Triangle(double ab, int a, int b) {
	AB = ab;
	C = (180 - (a + b)) * M_PI / 180;
	A = a * M_PI / 180;
	B = b * M_PI / 180;
	AC = ab * sin(b) / sin(C);
	BC = ab * sin(a) / sin(C);
	A_BC = ab * sin(b);
	B_AC = BC * sin(C);
	C_AB = AC * sin(a);
}
void Triangle::setAB(double a) {
	if (a < 0) {
		cout << "side can't be negative\n";
	}
	else {
		AB = a;
	}
}
void Triangle::setBC(double b) {
	if (b < 0) {
		cout << "side can't be negative\n";
	}
	else {
		BC = b;
	}
}
void Triangle::setAC(double c) {
	if (c < 0) {
		cout << "side can't be negative\n";
	}
	else {
		AC = c;
	}
}
double Triangle::getAB() {
	return AB;
}
double Triangle::getBC() {
	return BC;
}
double Triangle::Triangle::getAC() {
	return AC;
}
double Triangle::perim() {
	if (isTriangle()) {
		return AB + AC + BC;
	}
	else {
		cout << "\nЭто не треугольник\n";
	}
	return 0;
}
double Triangle::Area() {
	if (isTriangle()) {
		double p = (AB + AC + BC) / 2.0;
		return sqrt(p * (p - AB) * (p - AC) * (p - BC));
	}
	else {
		cout << "\nЭто не треугольник\n";
	}
	return 0;
}
void Triangle::GetType() {
	if (isTriangle()) {
		if (AB == BC && AB == AC) {
			cout << "Равносторонний\n";
			return;
		}
		else if (AB == BC || AB == AC || BC == AC) {
			cout << "Равнобедренный\n";
			if (AB == sqrt(BC * BC + AC * AC) || BC == sqrt(AB * AB + AC * AC) || AC == sqrt(BC * BC + AB * AB)) cout << "Прямоугольный\n";
		}
		else cout << "Обычный\n";
	}
	else {
		cout << "\nЭто не треугольник\n";
	}
}
bool Triangle::isTriangle() {
	if (AB >= BC + AC || BC >= AC + AB || AC >= BC + AB) {
		return false;
	}
	return true;
}
int main() {
	setlocale(LC_ALL, "Russian");
	Triangle A(-1.0, 2.0, 3.0);
	A.GetType();
	cout << "\nПлощадь: \n" << A.Area();
	cout << "\nПериметр: \n" << A.perim();
	return 0;
}