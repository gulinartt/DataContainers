#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------------------\n"

template<typename T>T** Allocate(const int rows, const int cols);
template<typename T>void Clear(T** arr, const int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols);
void FillRand(double** arr, const int rows, const int cols);

template<typename T>void Print(T arr[], const int n);//выводит массив на экран
template<typename T>void Print(T** arr, const int rows, const int cols);

template<typename T>T* push_back(T arr[], int& n, T value);
template<typename T>T* push_front(T arr[], int& n, T value);
template<typename T>T* insert(T arr[], int& n, T value, int m);

template<typename T>T* pop_back(T arr[], int& n);
template<typename T>T* pop_front(T arr[], int& n);
template<typename T>T* erase(T arr[], int& n, int m);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);

template<typename T>void push_col_back(T** arr, const int rows, int& cols);
template<typename T>void pop_col_back(T** arr, const int rows, int& cols);


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
	cout << "Введите размер массива: "; cin >> n;
	double* arr = new double[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "Введите добавляемое в конец значение "; cin >> value;
	arr = push_back(arr, n, (double)value);
	Print(arr, n);

	cout << "Введите добавляемое в начало значение "; cin >> value;
	Print(arr = push_front(arr, n, (double)value), n);

	cout << "Введите добавляемое значение в позицию с заданным индексом "; cin >> value;
	cout << "Введите индекс добавляемого значения: "; cin >> m;
	Print(arr = insert(arr, n, (double)value, m), n);

	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_front(arr, n), n);

	cout << "Введите индекс удаляемого значения  "; cin >> m;
	Print(arr = erase(arr, n, m), n);

	delete[]arr;
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << " Введите количество строк: "; cin >> rows;
	cout << " Введите количество столбцов: "; cin >> cols;

	double** arr = Allocate<double>(rows, cols);

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
	cout << delimiter << endl;
	Clear(arr, rows);

#endif // DYNAMIC_MEMORY_2

}
template<typename T>T** Allocate(const int rows, const int cols)
{
	T** arr = new T * [rows];//1)создаём массив указателей
	//2) выделяем память под строки, и адреса строк записываем в элементы массива указателей
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols];
	}
	return arr;
}
template<typename T>void Clear(T** arr, const int rows)
{
	//1)Cначала удаляем строки ДДМ:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2)удаляем массив указателей:
	delete[]arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
	}
}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		*(arr + i) /= 100;
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
void FillRand(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 10000;
			arr[i][j] /= 100;
		}
	}
}

template<typename T>void Print(T arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
template<typename T>void Print(T** arr, const int rows, const int cols)
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

template<typename T>T* push_back(T arr[], int& n, T value)
{
	//1)Создаём новый массив нужного размера
	T* buffer = new T[n + 1]{};
	//2)копируем всё содержимое исходного массива в новый массив
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) удаляем исходный массив
	delete[] arr;
	//4)подменяем адрес исходного массива адресом нового массива:
	arr = buffer;
	//5) только послеэтого в конец массива 'arr' можно дописать ещё один элемент
	arr[n] = value;
	//6) после добавления элемента в массив, количество его элементов увеличивается 
	n++;
	return buffer;
}
template<typename T>T* push_front(T arr[], int& n, T value)
{
	T* buffer = new T[n + 1]{};

	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;

	buffer[0] = value;
	n++;
	return buffer;
}
template<typename T>T* insert(T arr[], int& n, T value, int m)
{
	if (m < 0 || m > n)return arr;

	T* buffer = new T[n + 1]{};

	/*for (int i = 0; i < m; i++)	buffer[i] = arr[i];
	for (int i = m; i < n; i++)	buffer[i + 1] = arr[i];*/
	//или
	for (int i = 0; i < n; i++)
	{
		/*if (i < m) buffer[i] = arr[i];
		else   buffer[i + 1] = arr[i];*/
		//или
		//(i < m ? buffer[i] : buffer[i + 1]) = arr[i];
		//или
		buffer[i < m ? i : i + 1] = arr[i];
	}
	delete[]arr;

	buffer[m] = value;
	n++;
	return buffer;
}
template<typename T>T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n]{};
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[]arr;
	return buffer;
}
template<typename T>T* pop_front(T arr[], int& n)
{
	T* buffer = new T[--n]{};
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[]arr;
	return buffer;
}
template<typename T>T* erase(T arr[], int& n, int m)
{
	if (m < 0 || m > n)return arr;

	T* buffer = new T[--n]{};
	for (int i = 0; i < n; i++)	buffer[i] = arr[i < m ? i : i + 1];
	delete[]arr;
	return buffer;
}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	T** buffer = new T * [rows + 1] {};
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[] arr;
	buffer[rows] = new T[cols]{};
	rows++;
	return buffer;
}
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	//Удаляем последнюю строку массива:
	delete[] arr[rows - 1];
	//2) Переопределяем массив указателей:
	T** buffer = new T * [--rows] {};
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[]arr;
	return buffer;
}
template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols + 1]{};
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}
template<typename T>void pop_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols - 1]{};
		for (int j = 0; j < cols - 1; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols--;
}