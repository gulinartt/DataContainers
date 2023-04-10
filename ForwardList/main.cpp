//ForwardList
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------------------\n"

class Element //Структура элемента
{
	//переменные члены
	int Data;       //значение элемента
	Element* pNext; //адрес следующего элемента
	static int count;

	//не будем реализовывать инкапсуляцию, начнем сразу с конструктора
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList; //это открывает нам прямой доступ к 
	//закрытым полям элемента из класса список
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	friend class Iterator;
};

int Element::count = 0; //Статическую переменную можно проинициализировать только за пределами класса

class Iterator //class Iterator пишем для обеспечения операций над итератором
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList() //конструктор по умолчанию, который создает пустой список
	{
		Head = nullptr; //если список пуст, то его голова указывает на 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList() //конструктор копирования
	{
		*this = other;
	}
	ForwardList(ForwardList&& other) :ForwardList() //MoveConstructor - конструктор переноса
	{
		*this = std::move(other); //move - это функция
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		//прежде чем делать побитовое копирование, удалить старые значения:
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) // MoveAssignment
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		return *this;
	}

	//				Adding elements:
	void push_front(int Data) //метод, который добавляет элемент в начало списка
	{
		/*
		//1) Создаем новый элемент:
		Element* New = new Element(Data);

		//2) Новый элемент должен указывать на начало списка:
		New->pNext = Head; //в адрес нового элемента ложем адрес, который лежит в голове,
		//а в голове лежит адрес начального элемента

		// Какие отношения между классами реализует наследование? 
		// (что бы что-то унаследовать от чего-то 
		// нужно убедиться, что что-то является чем-то)
		// Из-за инкапсуляции мы не можем просто так получить доступ 
		// к переменным членам другого класса (friend)

		//3) Переводим Голову списка на новый элемент:
		Head = New;
		*/

		Head = new Element(Data, Head); //оператор присвоить работает справа налево
		//оператор new возвращает адрес выделенной памяти
		size++;
	}
	//nullptr - это тот же физический ноль
	void push_back(int Data) //добавление элемента в конец списка
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до конца списка:
		Element* Temp = Head; //указатель Temp - локальная переменная, созданная в методе push_back
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//По завершении этого цикла Temp указывает на последний элемент списка

		//3) Вставляем новый элемент в конец списка:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index) //вставляет значение по указанному индексу
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;
		//1) Создаем новый элемент:
		Element* New = new Element(Data);

		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3) Поместить элемент в список на нужную позицию:
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//				Removing elemtnts:
	void pop_front() //удаляет значение с начала списка
	{
		//1) Запоминаем адресс удаляемого эдементаЖ
		Element* Erased = Head;
		//2) Переводим Голову на следующий элемент,
		//   и таким образом, исключаем удаляемый элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти:
		delete Erased;
	}
	void pop_back() //удаляет значение с конца списка
	{
		//1) Доходим до предпоследнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		//2) Удаляем последний элемент из памяти:
		delete Temp->pNext;
		//3) Зануляем адрес последнего элемента:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		if (Index > size)return;
		//1) Доходим до элемента перед удаляемым:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//2) Запоминаем адрес удаляемого элемента:
		Element* Erased = Temp->pNext;
		//3) Исключаем удаляемый элемент из списка:
		Temp->pNext = Temp->pNext->pNext;
		//4) Удаляем элемент из памяти:
		delete Erased;
		size--;
	}

	//				Methods:
	void print()const
	{
		/*
		Element* Temp = Head; //Temp - это итератор.
		//Итератор - это указвтель, при помощи которого
		//можно получить доступ к элементам структуры данных.
		while (Temp) //пока в Tempпе не нулевой адрес
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			//выводим Temp - адрес элемента, Temp->Data -  значение элемента, Temp->pNext - адрес следующего элемента
			Temp = Temp->pNext; //переход на следующий элемент
		}
		*/
		for(Element* Temp=Head;Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элемнтов списка: " << size << endl;
		cout << "Общее количество элемнтов:  " << Element::count << endl; 
		//по хорошему к статическим переменным обращаются так Element::count, потому что они находятся в классе
		//а не в объектах, и это нужно показать вот таким вот образом
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left; //фактически оператор плюс выполняет конкатенацию списков
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	return cat; //cat локальная переменная, поэтому удаляется, нужен конструктор копирования в классе, 
	            //чтобы он копировался на место вызова
}

//#define BASE_CHECK
//#define OPERATOR_PLUS
//#define RANGE_BASE_FOR_ARRAY

void print(int arr[]) //когда мы передаем в функцию массив, то в функцию копируется 
                      //указательна этот массив
{
	cout << typeid(arr).name() << endl; //указатель на массив
	cout << sizeof(arr) << endl; //возвращается адрес указателя в байтах
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	//3/функция
}
void print(const ForwardList& list)
{
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();

	/*ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print(); */
#endif // BASE_CHECK


#ifdef OPERATOR_PLUS
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	list1 = list1;

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	//ForwardList list3 = list1 + list2; //CopyConstructor
	cout << delimiter << endl;
	ForwardList list3;
	list3 = list1 + list2; //оператор присваивания должен делать побитовое копирование, 
	                       //также как и конструктор копирования
	cout << delimiter << endl;
	list3.print();
#endif // OPERATOR_PLUS

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	//2/ если он(функция) не может вот так вот посчитать размер, он тогда ищет begin(), end()
	//и begin() и end() возвращают итераторы, а в итерараторах мы уже сами обеспечиваем
	//нужное поведение в зависимости от того какой у нас контейнер


	cout << endl;
	cout << typeid(arr).name() << endl; //тип данных массива - пять элементов типа int
	cout << sizeof(arr) << endl; //размер массива в байтах

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	//1/в main() этот код отработал, но как только мы его вынесли в функцию
	//прога начинает ругаться

	print(arr);
#endif // RANGE_BASE_FOR_ARRAY

	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for(int i:list)
	{
		cout << i << tab;
	}
	cout << endl;
}