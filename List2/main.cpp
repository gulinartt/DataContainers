#include<iostream>
using namespace std;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail; // ������� ��������� �� ������� ������ �� �������
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elemnts:
	void push_front(int Data) // �����, ��� ��������� ������� � ������ ������
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;	//�������� ����� 'return' ��������� ������ �������  
			        //� ���������� ���������� �� ����� ������. 
		}
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) �������������� ����� ������� � ������:
		New->pNext = Head;
		//3) �������������� ������ � ������ ��������:
		Head->pPrev = New;
		//4) ��������� ������ �� ����� �������:
		Head = New;
		size++;
	}
	void push_back(int Data) // ��������� ������� � ����� ������
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		Element* Temp; // ��������
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) �������������� ����� ������� � ������:
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		//3) �������������� ������ � ��������:
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;

		size++;
	}

	//					Removing elements:
	void pop_front() 
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		//1) ��������� ������� �� ������:
		Head = Head->pNext;
		//2) ������� ������ �� ������:
		delete Head->pPrev;
		//3) "��������" ��� ��������� �������:
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
	}
	void reverse_print()const // ������� ������ �� ����� � �������� �����������, ����� �������
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
}