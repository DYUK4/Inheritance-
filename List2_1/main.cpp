#include<iostream>
#include<format>
using namespace std;
using std::cin;
using std::cout;
using std::endl;



#define tab "\t"
#define delimiter "\n_____________________________________________________\n"

class List
{
//===========================================================================
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
			cout << "EDistructor:\t" << this << endl;
		}
		friend class List;
	}*Head,*Tail;
//======================================================================================
	size_t size;

	class ConstBaseIterator 
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		// Comparison operators:
		bool operator == (const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator != (const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		           // DeReference operator
		const int& operator*()const
		{
			return Temp->Data;
		}
         	


    };
 	                 // Constructor
public:

//========================================================================================
	class ConstIterator:public ConstBaseIterator // прямой итератор в одну сторону ->
	{
	public:
		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		ConstIterator& operator++() // Prefix increment перугрузка оператора ++ в классе Iterator
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int) //Postfix increment
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--() // Prefix increment
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator --(int) //Postfix increment
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
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
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RIDistructor:\t" << this << endl;
		}
		         //Incremento/Decremento:
		ConstReverseIterator& operator ++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator --(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		//         //Comperison operators:
		//bool operator ==(const ConstReverseIterator& other)const
		//{
		//	return this->Temp == other.Temp;
		//}
		//bool operator != (const ConstReverseIterator& other)const
		//{
		//	return this->Temp != other.Temp;
		//}
		//Dereference operators;
		/*const int& operator*()const
		{
			return Temp->Data;
		}*/
		/*int& operator *()
		{
			return Temp->Data;
		}*/
	};
//========================================================================================
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp=nullptr):ConstIterator(Temp){}
		~Iterator(){}

		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}

		int& operator*()
		{
			return Temp->Data;
		}
	};
	
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end() const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstReverseIterator rbegin()const
	{
		return Tail;
	}
	ConstReverseIterator rend()const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
//-----------------------------------------------------------------------------
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	            // CopyConstructor
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDistructor:\t" << this << endl;
	}
	           // Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	           //Adding elements:
	void push_front(int Data)
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
	void push_back(int Data)
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
	void pop_front()
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
	void pop_back()
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
	void insert(int Data,int Index)
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
			for(int i=Index; i<size-1;i++)
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
		Temp->pPrev=Temp->pPrev->pNext=new Element(Data,Temp,Temp->pPrev);

		size++;
	}
	void erese(int Index)
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
	void print()const
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
	void reverse_print()const
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
};
List operator+(const List& left, const List& right)
{
	List buffer = left;//CopyConstructor
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)// почему ошибка? нехватает константных методов begin end
	{
		buffer.push_back(*it);
		//*it *= 10;
	}

	return buffer;
}
void Grow(List& list)
{
	for (List::Iterator it = list.begin(); it != list.end();++it)
		*it *= 10;
}


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
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	//List list2=list1;
	//list2 = list1;
	/*list2.print();
	list2.reverse_print();*/
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;


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