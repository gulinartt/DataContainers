#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor <= 0)
	{
		cout << "�� � �������" << endl;
		return;
	}
	cout << "�� ��  " << floor << " �����" << endl;
	elevator(floor - 1); //������ �� ������� ������� 1 ���� �� ����� �� return
	cout << "�� ��  " << floor << " �����" << endl;
}
int factorial(int n)
{
	if (n < 0)return 0;
	/*if (n == 0)return 1;
	else return n * factorial(n - 1);*/
	return n == 0 ? 1 : n * factorial(n - 1);
}
double power(double a, int n)
{
	//a - ��������� �������
	//n - ���������� �������
	/*if (n == 0)return 1;
	else if (n > 0)return a * power(a, n - 1);
	//else return 1 / a * power(a, n + 1);
	else return 1 / power(a, -n);*/
	return n == 0 ? 1 : n > 0 ? a * power(a, n - 1) : 1 / power(a, -n);
}
/*void fibonachi(int n, long long int a = 0, long long int b = 1)
{
	if (a>=n)return;
	cout << a << "   ";
	fibonachi(n, b, a + b);
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
	void sequence(int n)
	{
		sequence(n, 0, 1);
	}
};

void main()
{
	setlocale(0, "");
	//cout << "Hello Recursion!";
	/*int n;
	cout << "������� ����� �����: "; cin >> n;
	elevator(n);*/
	//main();
	/*int n;
	cout << "������� �����: "; cin >> n;
	cout << factorial(n) << endl;*/
	/*int a = 0, n = 0;
	cout << "������� �����: "; cin >> a;
	cout << "������� �������: "; cin >> n;
	cout << a << " ^ " << n << " = " << power(a, n) << endl;*/

	int n = 0;
	cout << "������� ������: "; cin >> n;
	Fibonacci(n);

}