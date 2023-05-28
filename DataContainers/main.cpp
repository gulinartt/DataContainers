#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------------------\n"

int** Allocate(const int rows, const int cols);
void Clear(int** arr, const int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);//��������� ������ ���������� ������� �� n ���������
void FillRand(int** arr, const int rows, const int cols);

void Print(int arr[], const int n);//������� ������ �� �����
void Print(int** arr, const int rows, const int cols);

int* push_back(int arr[], int& n, int value);
int* push_front(int arr[], int& n, int value);
int* insert(int arr[], int& n, int value, int m);

int* pop_back(int arr[], int& n);
int* pop_front(int arr[], int& n);
int* erase(int arr[], int& n, int m);

int** push_row_back(int** arr, int& rows, const int cols);
int** pop_row_back(int** arr, int& rows, const int cols);

void push_col_back(int** arr, const int rows, int& cols);
void pop_col_back(int** arr, const int rows, int& cols);


//#define POINTERS_AND_ARRAYS
//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(0, "");
#ifdef POINTERS_AND_ARRAYS
	const int n = 5;
	int arr[n] = { 3,5,8,13,21 };

	cout << arr << endl;
	cout << *arr << endl;

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;

	for (int i = 0; i < n; i++)
	{
		cout << *(arr + i) << "\t";
	}
	cout << endl;
#endif // POINTERS_AND_ARRAYS


#ifdef DYNAMIC_MEMORY_1
	int n, m;
	cout << "������� ������ �������: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "������� ����������� � ����� �������� "; cin >> value;
	Print(arr, n);
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "������� ����������� � ������ �������� "; cin >> value;
	Print(arr = push_front(arr, n, value), n);

	cout << "������� ����������� �������� � ������� � �������� �������� "; cin >> value;
	cout << "������� ������ ������������ ��������: "; cin >> m;
	Print(arr = insert(arr, n, value, m), n);

	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_front(arr, n), n);

	cout << "������� ������ ���������� ��������  "; cin >> m;
	Print(arr = erase(arr, n, m), n);

	delete[]arr;
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << " ������� ���������� �����: "; cin >> rows;
	cout << " ������� ���������� ��������: "; cin >> cols;

	int** arr = Allocate(rows, cols);

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 200);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	pop_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	Clear(arr, rows);

#endif // DYNAMIC_MEMORY_2

}
int** Allocate(const int rows, const int cols)
{

	int** arr = new int* [rows];//1)������ ������ ����������
	//2) �������� ������ ��� ������, � ������ ����� ���������� � �������� ������� ����������
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	return arr;

}
void Clear(int** arr, const int rows)
{
	//1)C������ ������� ������ ���:
	for (int i = 0; i < rows; i++)
	{
		delete[]arr[i];
	}
	//2)������� ������ ����������:
	delete[]arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		//arr[i] = rand() % 100;
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
	}
}
void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}

void Print(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
}

int* push_back(int arr[], int& n, int value)
{
	//1)������ ����� ������ ������� �������
	int* buffer = new int[n + 1] {};
	//2)�������� �� ���������� ��������� ������� � ����� ������
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) ������� �������� ������
	delete[] arr;
	//4)��������� ����� ��������� ������� ������� ������ �������:
	arr = buffer;
	//5) ������ ���������� � ����� ������� 'arr' ����� �������� ��� ���� �������
	arr[n] = value;
	//6) ����� ���������� �������� � ������, ���������� ��� ��������� ������������� 
	n++;
	return buffer;
}
int* push_front(int arr[], int& n, int value)
{
	int* buffer = new int[n + 1] {};

	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;

	buffer[0] = value;
	n++;
	return buffer;
}
int* insert(int arr[], int& n, int value, int m)
{
	if (m < 0 || m > n)return arr;

	int* buffer = new int[n + 1] {};

	/*for (int i = 0; i < m; i++)	buffer[i] = arr[i];
	for (int i = m; i < n; i++)	buffer[i + 1] = arr[i];*/
	//���
	for (int i = 0; i < n; i++)
	{
		/*if (i < m) buffer[i] = arr[i];
		else   buffer[i + 1] = arr[i];*/
		//���
		//(i < m ? buffer[i] : buffer[i + 1]) = arr[i];
		//���
		buffer[i < m ? i : i + 1] = arr[i];
	}
	delete[]arr;

	buffer[m] = value;
	n++;
	return buffer;
}
int* pop_back(int arr[], int& n)
{
	int* buffer = new int[--n] {};
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[]arr;
	return buffer;
}
int* pop_front(int arr[], int& n)
{
	int* buffer = new int[--n] {};
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[]arr;
	return buffer;
}
int* erase(int arr[], int& n, int m)
{
	if (m < 0 || m > n)return arr;

	int* buffer = new int[--n] {};
	for (int i = 0; i < n; i++)	buffer[i] = arr[i < m ? i : i + 1];
	delete[]arr;
	return buffer;
}

int** push_row_back(int** arr, int& rows, const int cols)
{
	int** buffer = new int* [rows + 1] {};
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[]arr;
	buffer[rows] = new int[cols] {};
	rows++;
	return buffer;
}
int** pop_row_back(int** arr, int& rows, const int cols)
{
	//������� ��������� ������ �������:
	delete[] arr[rows - 1];
	//2) �������������� ������ ����������:
	int** buffer = new int* [--rows] {};
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[]arr;
	return buffer;
}
void push_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1] {};
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}
void pop_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1] {};
		for (int j = 0; j < cols - 1; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols--;
}