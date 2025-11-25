#include<iostream>
#include<format>
using namespace std;
using std::cin;
using std::cout;
using std::endl;



#define tab "\t"
#define delimiter "\n_____________________________________________________\n"

//Class -  обычный класс;
//Class<type> - шаблонный класс;
//Class<T> ......
//Class<double> .......



// #########################################################################
//############## Объявления класса (class declaration) #####################

//template - показывает создание шаблона.
//typename - создает шаблонный тип данных
//T - имя шаблонного типа.

template<typename T>class List
{

	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG

			cout << "EDistructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class List;
	}*Head,*Tail;

	size_t size;

	class ConstBaseIterator 
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		        // Comparison operators:
		bool operator == (const ConstBaseIterator& other)const;
		bool operator != (const ConstBaseIterator& other)const;

		           // DeReference operator
		const T& operator*()const;
         	


    };
 	                 // Constructor
public:
//========================================================================================
	class ConstIterator:public ConstBaseIterator // прямой итератор в одну сторону ->
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator --(int);
		/*          // Comparison operators:
		bool operator == (const ConstIterator& other)const Перенесено в ConstBaseInterator как посторяемую часть кода
		{
			return this->Temp == other.Temp;
		}
		bool operator != (const ConstIterator& other)const
		{
			return this->Temp != other.Temp;
		}*/
		          //Dereference operators:                                               оператор разыменования, возвращает: значение которое в адресе
		/*int operator *()const
		{
			return Temp->Data;
		}*/
		/*int& operator*()
		{
			return Temp->Data;
		}*/
	};
//=========================================================================================
	class ConstReverseIterator:public ConstBaseIterator // обратный итератор <-
	{
		//Element* Temp;
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		         //Incremento/Decremento:
		ConstReverseIterator& operator ++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator --(int);
	};
//========================================================================================
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp=nullptr):ConstIterator(Temp){}
		~Iterator(){}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	
	ConstIterator begin()const;
	ConstIterator end() const;
	Iterator begin();
	Iterator end();


	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	//------------------------ Constructors: -----------------------------------------------------
	List();
	List(const std::initializer_list<T>& il);
	// CopyConstructor
	List(const List<T>& other);
	~List();
	// Operators:
	List<T>& operator=(const List<T>& other);
	//Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	//Removing elements:
	void pop_front();
	void pop_back();
	void insert(T Data, int Index);
	void erese(int Index);
	// Methods:
	void print()const;
	void reverse_print()const;
};

//############## Конец Объявление класса (Class declaration end)    #########
// #########################################################################


//#############################################################################
// ###############   Определение класса (class definition) #######################################
// 
// 
// 
// 
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////        constBaseIterator      //////////////////////////////////////////////////
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp) {}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator() {}
// Comparison operators:
template<typename T>bool List<T>::ConstBaseIterator:: operator == (const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator != (const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

// DeReference operator
template<typename T> const T& List<T>::ConstBaseIterator:: operator*()const
{
	return Temp->Data;
}

/////////////////         constBaseIterator      //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////         const Iterators      //////////////////////////////////////////////////

template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) : ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() // Prefix increment перугрузка оператора ++ в классе Iterator
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) //Postfix increment
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--() // Prefix increment
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator --(int) //Postfix increment
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

/////////////////         const Iterators      //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////         const ReversIterator     //////////////////////////////////////////////////

template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RIDistructor:\t" << this << endl;
#endif // DEBUG
}
//Incremento/Decremento:
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator ++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator --(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

/////////////////         const ReversIterator     //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    List members    ///////////////////////////////////////////
template<typename T>typename List<T>::ConstIterator List<T>:: begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>:: end() const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>:: begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>:: end()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>:: rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>:: rend()const
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>:: rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>:: rend()
{
	return nullptr;
}
//-----------------------------------------------------------------------------
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}
// CopyConstructor
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
#ifdef DEBUG
	cout << "CopyConstructor:" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::~List()
{
	while (Head)pop_front();
#ifdef DEBUG
	cout << "LDistructor:\t" << this << endl;
#endif // DEBUG
}
   // Operators:
template<typename T>List<T>& List<T>:: operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
#ifdef DEBUG
	cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG

	return *this;
}
//Adding elements:
template<typename T>void List<T>:: push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);

	}
	else
	{
		//Element* New = new Element(Data); //1 создание элемента
		//New->pNext = Head; //2 новый элемент указывает на pNext головного элемента Head
		//Head->pPrev = New; // 3 головной элемент указывает на pNext нового элемента New
		//Head = New; //4 голова указывает на новый элемент 

		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;//инкриментируем размер
}
template<typename T>void List<T>:: push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		//Element* New = new Element(Data);
		//New->pPrev = Tail;
		//Tail->pNext = New;
		//Tail = New;

		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
//Removing elements:
template<typename T>void List<T>:: pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;


	}
	size--;
}
template<typename T>void List<T>:: pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}
template<typename T>void List<T>:: insert(T Data, int Index) // индекс это всегда натуральное число!!! как и size
{
	if (Index > size)return;
	if (Index == 0)return push_front(Data);
	if (Index == size)return push_back(Data);
	//if (Index<0 || Index>size)return;

	Element* Temp;

	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = Index; i < size - 1; i++)
			//for (int i = 0; i < size - Index - 1; i++)
		{
			Temp = Temp->pPrev;
		}

	}
	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/

	//Temp = Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp);
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);

	size++;
}
template<typename T>void List<T>:: erese(int Index)
{
	if (Index > size)return;
	if (Index == 0)return pop_front();
	if (Index == size)return pop_back();

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)
		{
			Temp = Temp->pPrev;
		}
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}
// Methods: 
template<typename T>void List<T>:: print()const
{
	cout << delimiter << endl;
	cout << "Head:\t" << Head << endl;

	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout
		<< Temp->pPrev << tab
		<< Temp << tab
		<< Temp->Data << tab
		<< Temp->pNext << endl;

	cout << "Teal:\t" << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << delimiter << endl;
}
template<typename T>void List<T>:: reverse_print()const
{
	cout << delimiter << endl;
	cout << "Tail:\t" << Tail << endl;

	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout
		<< Temp->pPrev << tab
		<< Temp << tab
		<< Temp->Data << tab
		<< Temp->pNext << endl;

	cout << "Head:\t" << Head << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << delimiter << endl;
}

//////////////////////////////    List members    ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;//CopyConstructor
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)// почему ошибка? нехватает константных методов begin end
	{
		buffer.push_back(*it);
		//*it *= 10;
	}

	return buffer;
}
template<typename T>void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end();++it)
		*it *= 10;
}

// ##### Конец определения класса (Class definition end) #########################
//###################################################################################

//========================================================================================



//#define BASE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		// list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();

	/*list.reverse_print();
	for (int i = 0; i < 100; i++)list.pop_back();
	list.reverse_print();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	//list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erese(index);
	list.print();

#endif // BASE_CHECK
	//List list = { 3,5,8,13,21 };
	//list.print(); 
	///*int index;
	//int value;
	//cout << "Введте индекс добавляемого элемента:"; cin >> index;
	//cout << "Введите значение добавляемого элемента:"; cin >> value;
	//list.insert(value, index);
	//list.print();
	//list.reverse_print();*/
	//for (int i : list)cout << i << tab;		cout << endl;
	//for (List::ReverseIterator it = list.rbegin(); it != list.rend();it++)
	//{
	//cout << *it << tab;
	//}
	//
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	//List list2=list1;
	//list2 = list1;
	/*list2.print();
	list2.reverse_print();*/
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;

	List<std::string>s_list = { "Хорошо","живет","на","свете","Винни","Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;

	List<double>d_list = { 2.7,3.14,5.4,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;
	d_list.print();

	List<std::string>b_list = { "Хорошо","Живет","на","свете","ноут","бук" };
	for (std::string i : b_list)cout << i << tab; cout << endl;
}

    //вид 34 ООП
//                    Двусвязный список
//Двусвязным называется список - каждый элемент которого хранит адрес не только следущего но и предыдущего элемента. т.е у него есть кроме pNext есть еще pPrev(хранит адрес предыдущего элемента) Это позволяет ходить по списку в обоих направлениях как от начала до конца так и от конца к началу. Такая возможность уменьшает время доступа к элементу в два раза, но делает список более тяжелым по скольку каждый элемент хранит больше служебной информации. 

// У двусвязного списка кроме головы которая указывает на начальный элемент списка, есть еще и хвост Tail - который указывает на последний элемент списка. В двусвязный список можно зайти как и через голову так и через хвост, если список пуст его голова и хвост указывают на ноль. Если список содержит один единственный элемент он одновременно является и головой и хвостом списка. А так же он является и первым и последний элемент списка с какой стороны не посмотреть.

// В отдельном проекте реализовать двусвязный список

//композиция и агрегирование - на данный момент композиция 

//35 2_07
//1 insert() / erase();
//2  Оптимизировать общий случай добавления элементов до одного выражения;
//3 создать Commit

// 37 видео 2/45
//добить итераторы

// Выражение Start выполняется 1 раз- перед первой итерацией;
// видео 38 1.44


                       // Шаблоны классов
// Шаблонным называется класс тип полей которого определяетя при создании обьекта т.е поля шаблонного класса могут быть любого типа. При обращении к шаблонному классу обязательно нужно указывать тип его членов явным образом т.е если к обыченому классу мы обращаемся так Class - обычный класс, то к шаблонному классу обращаемся так Class<type> - шаблон. Причем тип может быть как шаблонный так и конкретный Class<double> . Все методы внутри  шаблонном классе автоматически становятся шаблоннымы 
// Для того что бы сделать класс шаблонным перед ним достаточно просто создать шаблон
 // template - показывает создание шаблони 
// typenem - создание шаблонного тип данных
// T - имя шаблонного типа
//     Если внутри шаблонного класса созданы другие классы то они являются не шаблонными а обычными классами, но любую переменную член и любой метод такого вложенного класса можно сделать шаблонными 

// 39 видео 15 min
// 40 ёёёёёёёёёёёёёёёёёёёёёёёёёёёёёёёёё
// constIterator = конструктор

//Параметры по умолчанию могут быть только в прототипах функций (ConstIterator(Element* Temp = nullptr))ConstIterator(Element* Temp)
//
//
// 41 video 1.28


