#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------------------------\n"

class Element //��������� ��������
{
	//���������� �����
	int Data;       //�������� ��������
	Element* pNext; //����� ���������� ��������
	static int count;

	//�� ����� ������������� ������������, ������ ����� � ������������
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
	friend class ForwardList; //��� ��������� ��� ������ ������ � 
	//�������� ����� �������� �� ������ ������
};

int Element::count = 0; //����������� ���������� ����� ������������������� ������ �� ��������� ������

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList() //����������� �� ���������, ������� ������� ������ ������
	{
		Head = nullptr; //���� ������ ����, �� ��� ������ ��������� �� 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data) //�����, ������� ��������� ������� � ������ ������
	{
		/*
		//1) ������� ����� �������:
		Element* New = new Element(Data);

		//2) ����� ������� ������ ��������� �� ������ ������:
		New->pNext = Head; //� ����� ������ �������� ����� �����, ������� ����� � ������,
		//� � ������ ����� ����� ���������� ��������

		// ����� ��������� ����� �������� ��������� ������������? 
		// (��� �� ���-�� ������������ �� ����-�� 
		// ����� ���������, ��� ���-�� �������� ���-��)
		// ��-�� ������������ �� �� ����� ������ ��� �������� ������ 
		// � ���������� ������ ������� ������ (friend)

		//3) ��������� ������ ������ �� ����� �������:
		Head = New;
		*/

		Head = new Element(Data, Head); //�������� ��������� �������� ������ ������
		//�������� new ���������� ����� ���������� ������
		size++;
	}
	//nullptr - ��� ��� �� ���������� ����
	void push_back(int Data) //���������� �������� � ����� ������
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� ����� �������:
		//Element* New = new Element(Data);

		//2) ������� �� ����� ������:
		Element* Temp = Head; //��������� Temp - ��������� ����������, ��������� � ������ push_back
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//�� ���������� ����� ����� Temp ��������� �� ��������� ������� ������

		//3) ��������� ����� ������� � ����� ������:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index) //��������� �������� �� ���������� �������
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;
		//1) ������� ����� �������:
		Element* New = new Element(Data);

		//2) ������� �� ������� ��������:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3) ��������� ������� � ������ �� ������ �������:
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//				Removing elemtnts:
	void pop_front() //������� �������� � ������ ������
	{
		//1) ���������� ������ ���������� ���������
		Element* Erased = Head;
		//2) ��������� ������ �� ��������� �������,
		//   � ����� �������, ��������� ��������� ������� �� ������:
		Head = Head->pNext;
		//3) ������� ������� �� ������:
		delete Erased;
	}
	void pop_back() //������� �������� � ����� ������
	{
		//1) ������� �� �������������� �������� ������:
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		//2) ������� ��������� ������� �� ������:
		delete Temp->pNext;
		//3) �������� ����� ���������� ��������:
		Temp->pNext = nullptr;
		size--;
	}

	//				Methods:
	void print()const
	{
		/*
		Element* Temp = Head; //Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ ��������
		//����� �������� ������ � ��������� ��������� ������.
		while (Temp) //���� � Temp�� �� ������� �����
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			//������� Temp - ����� ��������, Temp->Data -  �������� ��������, Temp->pNext - ����� ���������� ��������
			Temp = Temp->pNext; //������� �� ��������� �������
		}
		*/
		for(Element* Temp=Head;Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� �������� ������: " << size << endl;
		cout << "����� ���������� ��������:  " << Element::count << endl; 
		//�� �������� � ����������� ���������� ���������� ��� Element::count, ������ ��� ��� ��������� � ������
		//� �� � ��������, � ��� ����� �������� ��� ����� ��� �������
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
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
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print(); 
}