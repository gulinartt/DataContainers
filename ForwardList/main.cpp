#include "ForwardList.cpp"

//#define BASE_CHACK
//#define OPERATOR_PLUS
//#define RANGE_BASED_FOR_ARRA
//#define RANGE_BASED_FOR_LIST
// #define PROFORMANS_TEST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHACK
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
	/*cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value,index);
	list.print();*/
	cout << "введите номер удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();

	/*ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/
#endif // BASE_CHACK

#ifdef OPERATOR_PLUS
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	list1 = list1;
	cout << delimiter << endl;

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimiter << endl;

	//ForwardList list3 = list1 + list2; //CopyConstractor
	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
#endif // OPERATOR_PLUS

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	//Range-based for
	for (int i : arr)     //синтаксис for который используется исключительно с диапазонами
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };

	/*for (int i : list)    //синтаксис for который используется исключительно с диапазонами
	{
		i *= 10;
		cout << i << tab;
	}*/
	cout << endl;
	print(list);
	list.print();
#endif // RANGE_BASED_FOR_LIST

#ifdef PROFORMANS_TEST
	int n;
	cout << "Введите размер списка: "; cin >> n;

	clock_t start = clock();
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand()); //намного медленнее
		list.push_front(rand() % 100);
	}

	clock_t end = clock();
	double delta = double(end - start) / CLOCKS_PER_SEC;

	cout << "список заполнен за :" << delta << "сек" << endl;
	//list.print();
	start = clock();
	ForwardList<int> list2 = list;
	end = clock();
	delta = double(end - start) / CLOCKS_PER_SEC;
	cout << "список скопирован за " << delta << endl;
	//list2.print();  
#endif // PROFORMANS_TEST
	ForwardList<int> i_list = { 3,5,8,13,21 };
	for (int i : i_list)cout << i << tab; cout << endl;

	ForwardList<double> d_list = { 2.7,3.14,5.1,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Хорошо","живет","на","свете", "Винни", "Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;

}