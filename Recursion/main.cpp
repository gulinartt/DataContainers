#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor <= 0)
	{
		cout << "�� � �������" << endl;
		return;
	}
	cout << "�� �� " << floor << " ����� " << endl;
	elevator(floor - 1);
}

int factorial(int n)
{
	if (n < 0)return 0;
	/*if (n == 0)return 1;
	return n * factorial(n - 1);*/
	return n==0?1:n * factorial(n - 1);
}
double power(double a, int n)
{
	/*if (n == 0)return 1;
	else if (n > 0)return a * power(a, n - 1);
	else return 1 / power(a, -n);*/
	return n == 0 ? 1 : n > 0 ? a * power(a, -n) : 1 / power(a, -n);
}
/*void Fibonacci(int n, long long int a = 0, long long int b = 1)
{
	if (a >= n)return;
	cout << a << "\t";
	Fibonacci(n, b, a + b);
}*/

class Fibonacci
{
	static void sequence(int n, long long int a, long long int b)
	{
		if (a > n)return;
		cout << a << "\t";
		sequence(n, b, a + b);
	}
public:
	static void sequence(int n)
	{
		sequence(n, 0, 1);
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello Recursion!";
	/*int n;
	cout << "������� ����� �����: "; cin >> n;
	elevator(n);*/

	/*int n;
	cout << "������� �����: "; cin >> n;
	cout << factorial(n) << endl;*/

	/*int n;
	double a;
	cout << "������� ���������: "; cin >> a;
	cout << "������� �������: "; cin >> n;
	cout << a << " ^ " << n << " = " << power(a, n) << endl;*/

	int n;
	cout << "������� ������: "; cin >> n;
	//Fibonacci(n);
	Fibonacci(n, 200, 300);

	//main();
}