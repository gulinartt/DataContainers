#include<iostream>
using namespace std;

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
};

int Element::count = 0; //Статическую переменную можно проинициализировать только за пределами класса

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList() //конструктор по умолчанию, который создает пустой список
	{
		Head = nullptr; //если список пуст, то его голова указывает на 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
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
};

void main()
{
	setlocale(LC_ALL, "");
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

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print(); 
}