//ForwardList
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	friend class Iterator;
};

int Element::count = 0; //����������� ���������� ����� ������������������� ������ �� ��������� ������

class Iterator //class Iterator ����� ��� ����������� �������� ��� ����������
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
	ForwardList() //����������� �� ���������, ������� ������� ������ ������
	{
		Head = nullptr; //���� ������ ����, �� ��� ������ ��������� �� 0
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
	ForwardList(const ForwardList& other) :ForwardList() //����������� �����������
	{
		*this = other;
	}
	ForwardList(ForwardList&& other) :ForwardList() //MoveConstructor - ����������� ��������
	{
		*this = std::move(other); //move - ��� �������
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
		//������ ��� ������ ��������� �����������, ������� ������ ��������:
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
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		if (Index > size)return;
		//1) ������� �� �������� ����� ���������:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//2) ���������� ����� ���������� ��������:
		Element* Erased = Temp->pNext;
		//3) ��������� ��������� ������� �� ������:
		Temp->pNext = Temp->pNext->pNext;
		//4) ������� ������� �� ������:
		delete Erased;
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
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left; //���������� �������� ���� ��������� ������������ �������
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	return cat; //cat ��������� ����������, ������� ���������, ����� ����������� ����������� � ������, 
	            //����� �� ����������� �� ����� ������
}

//#define BASE_CHECK
//#define OPERATOR_PLUS
//#define RANGE_BASE_FOR_ARRAY

void print(int arr[]) //����� �� �������� � ������� ������, �� � ������� ���������� 
                      //����������� ���� ������
{
	cout << typeid(arr).name() << endl; //��������� �� ������
	cout << sizeof(arr) << endl; //������������ ����� ��������� � ������
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	//3/�������
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

	cout << "������� ������ ���������� ��������: "; cin >> index;
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
	list3 = list1 + list2; //�������� ������������ ������ ������ ��������� �����������, 
	                       //����� ��� � ����������� �����������
	cout << delimiter << endl;
	list3.print();
#endif // OPERATOR_PLUS

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	//2/ ���� ��(�������) �� ����� ��� ��� ��� ��������� ������, �� ����� ���� begin(), end()
	//� begin() � end() ���������� ���������, � � ������������ �� ��� ���� ������������
	//������ ��������� � ����������� �� ���� ����� � ��� ���������


	cout << endl;
	cout << typeid(arr).name() << endl; //��� ������ ������� - ���� ��������� ���� int
	cout << sizeof(arr) << endl; //������ ������� � ������

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	//1/� main() ���� ��� ���������, �� ��� ������ �� ��� ������� � �������
	//����� �������� ��������

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