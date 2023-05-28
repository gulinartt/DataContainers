#include <iostream>
using namespace std;
#define tab "\t"
template<typename T> class Element;
template<typename T> class Iterator;
template<typename T> class ConstIterator;
template<typename T> List<T> operator+(const List<T>& left, const List<T>& right);

template<typename T> class List
{
	template<typename T>class Element
	{
		T Data;
		Element<T>* pNext;
		Element<T>* pPrev;
	public:

		Element(T Data, Element<T>* pNext = nullptr, Element<T>* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	}/**Head, *Tail*/;//чтобы запись была короче иначе за классом вызывалось бы так:
	//Element* Head, Element* Tail

	size_t size;
	template<typename T>class ConstBaseIterator
	{
	protected:
		Element<T>* Temp;
	public:
		ConstBaseIterator(Element<T>* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator ==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const T& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	template<typename T>
	class ConstIterator :public ConstBaseIterator<T>
	{
		Element<T>* Temp;
	public:
		ConstIterator(Element<T>* Temp = nullptr) : ConstBaseIterator<T>(Temp) {}

		~ConstIterator() {}

		ConstIterator& operator++()   //Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		template<typename T>
		ConstIterator operator++(T) //Postfix increment
		{
			ConstIterator<T> old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(T)
		{
			ConstIterator<T> old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	template<typename T>
	class ConstReverseIterator :public ConstBaseIterator<T>
	{
		Element<T>* Temp;
	public:
		ConstReverseIterator(Element<T>* Temp) :ConstBaseIterator<T>(Temp) {}

		~ConstReverseIterator() {}

		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(T)
		{
			ConstReverseIterator<T> old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(T)
		{
			ConstReverseIterator<T> old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator<T>
	{
	public:
		Element<T>* Temp;
		Iterator(Element<T>* Temp = nullptr) : ConstIterator<T>(Temp) {}
		~Iterator() {}
		T& operator*()
		{
			return Temp->Data;
		}
	};
	//template<typename T>
	class ReverseIterator :public ConstReverseIterator<T>
	{
		Element<T>* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator<T>(Temp) {}
		~ReverseIterator() {}
		T& operator*()
		{
			return Temp->Data;
		}
	};
	Element<T>* Head;
	Element<T>* Tail;
	template<typename T>
	const ConstIterator<T> begin() const
	{
		return Head;
	}
	const ConstIterator<T> end()const
	{
		return nullptr;
	}
	const ConstReverseIterator<T> rbegin() const
	{
		return Tail;
	}
	const ConstReverseIterator<T> rend() const
	{
		return nullptr;
	}

	Iterator<T> begin()
	{
		return Head;
	}
	Iterator <T> end()
	{
		return nullptr;
	}
	ReverseIterator<T> rbegin()
	{
		return Tail;
	}
	ReverseIterator<T> rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List<T>& other) : List()
	{
		*this = other;
		cout << "LCopyConstractor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//-----------Operators-----
	List<T>& operator	=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	//----------------Adding elements-----------------
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element<T>(Data);
			size++;
			return;
		}
		/*//1) создаём новый элемент
		Element* New = new Element(Data);
		//2) пристыковываем новый элемент к списку
		New->pNext = Head;
		//3) пристыковываем список к новому элементу
		Head->pPrev = New;
		//4) переводим голову на новый элемент
		Head = New;*/
		Head = Head->pPrev = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element<T>(Data);
		}
		else
		{
			/*//1) создаём новый элемент
			Element* New = new Element(Data);
			//2) пристыковываем новый элемент к списку
			New->pPrev = Tail;
			//3) пристыковываем список к новому элементу
			Tail->pNext = New;
			//4) переводим голову на новый элемент
			Tail = New;*/

			/*Element* New = new Element(Data);

			New->pPrev = Tail;
			//3) пристыковываем список к новому элементу
			Tail->pNext = New;
			//4) переводим голову на новый элемент
			Tail = New;*/
			Tail = Tail->pNext = new Element<T>(Data, nullptr, Tail);
			size++;
		}
		size++;
	}

	void insert(T Data, int Index)
	{
		if (Index == size) { push_back(Data); return; }
		if (Index == 0) { push_front(Data); return; }
		if (Index > size)return;
		Element<T>* Temp;
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
		/*//1)создаём новый элемент
		Element* New = new Element(Data);
		//2)пристыковываем новый элемент к списку
		New->pNext = Temp;//справа
		New->pPrev = Temp->pPrev;//слева
		//3)пристыковываем список к элементу
		Temp->pPrev->pNext = New;
		Temp->pPrev = New; */
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}


	//---------------Removing elements:---------------
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		//1)Исключаем элемент из списка
		Head = Head->pNext;
		//2)удаляем элемент из памяти
		delete Head->pPrev;
		//3)Забываем про удаленный элемент
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			return;
		}
		//1)Исключаем элемент из списка
		Tail = Tail->pPrev;
		//2)удаляем элемент из памяти
		delete Tail->pNext;
		//3)Забываем про удаленный элемент
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == size) { pop_back(); return; }
		if (Index == 0) { pop_front(); return; }
		if (Head == Tail)return pop_front();
		if (Index > size)return;
		Element<T>* Temp;
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
		if (Temp == Tail)return pop_back();
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		Temp = nullptr;
		size--;

	}

	//---------------Metods-----------
	void print()const
	{
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element<T>* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};
template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat;
	for (List<T>::ConstIterator<T> it = left.begin(); it != left.end(); ++it)cat.push_back(*it);
	for (List<T>::ConstIterator<T> it = right.begin(); it != right.end(); ++it)cat.push_back(*it);
	return cat;
}

//#define BASE_CHECK
//#define ITERRATORS_CHECK
void main()
{
	setlocale(0, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемогоэлемента: "; cin >> index;
	cout << "Введите значение добавляемогоэлемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	int index2;
	cout << "Введите индекс удаляемого элемента: "; cin >> index2;
	list.erase(index2);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK
#ifdef ITERRATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverse_print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERRATORS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	//for (int& i : list3) i *=10;
	//for (int i : list3)cout << i << tab; cout << endl;

}