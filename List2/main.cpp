#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------------\n"

 
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
	}*Head,*Tail;
	
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp; // вынесли из ConstIterator
	public:
		ConstBaseIterator(Element* Temp=nullptr):Temp(Temp){}
		~ConstBaseIterator(){}
		//           Comparison operators: операторы сравнения
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//         Dereference operator: два варианта разыменования
		const int operator* ()const // по конст ссылке 
		{
			return Temp->Data;
		}

	};
public:
	class ConstIterator:public ConstBaseIterator //переименовывыем Iterator в ConstIterator через ctr+r r для list1 list2 list3	  
	{
		//Element* Temp;
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		ConstIterator& operator++()//Prefix increment ++X
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator& operator++(int)//Postfix increment  X++
		{
			ConstIterator old = *this;// запоминает старое значение 
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--() // pref Decrement --X
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int) // Post Decrement X--
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		////                            Comparison operators: операторы сравнения
		//bool operator==(const ConstIterator& other)const
		//{
		//	return this->Temp == other.Temp;
		//}
		//bool operator!=(const ConstIterator& other)const
		//{
		//	return this->Temp != other.Temp;
		//}

		////         Dereference operator: два варианта разыменования
		//int operator* ()const // по конст ссылке 
		//{
		//	return Temp->Data;
		//}

		 // Убираем не константный итератор разыменования
		//int& operator*()// не буден не конст разыменование и не константный оператор
		//{
		//	return Temp->Data;
		//}

	};


	class ConstReverseIterator:public ConstBaseIterator// переименовывыем ReverseIterator в ConstReverseIterator через ctr + r r для list1 list2 list3
	{
		//Element* Temp;
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}
		//    Incremento/Decremento:
		ConstReverseIterator& operator++() // ++X
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int) // X++
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--() // --X
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int) // x--
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		//// Comperison operators:
		//bool operator== (const ConstReverseIterator& other)const
		//{
		//	return this->Temp == other.Temp;
		//}
		//bool operator!=(const ConstReverseIterator& other)const
		//{
		//	return this->Temp != other.Temp;
		//}
		//    // Dereference operators:
		//const int& operator*()const
		//{
		//	return Temp->Data;
		//}
		/*int& operator*() // убираем не константные разыменования 
		{
			return Temp->Data;
		}*/

	};
	 ConstIterator begin() const //делаем константными методами из за оператора + за классом
	{
		return Head;
	}
	 ConstIterator end() const //делаем константными методами из за оператора + за классом
	{
		return nullptr;
	}

	ConstReverseIterator rbegin()
	{
		return Tail;
	}
	ConstReverseIterator rend()
	{
		return nullptr;
	}
	 
	//       Constructors:
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
	List(const List& other) :List() // Конструктор копирования а в нем можно использовать повторно ConyAssignment
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl; 
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//          Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "ConyAssignment:\t" << this << endl;
		return *this;	
	   }



	//                Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{

			Element* New = new Element(Data);  //1
			New->pNext = Head; // 2 новый элемент указывает на головной элемент
			Head->pPrev = New; // 3 предыдущий элемент указывает на новый элемент
			Head = New;        // 4 Голова указывает на новый элемент
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//Element* New = new Element(Data); //1
			//New->pPrev = Tail;                //2
			//Tail->pNext = New;                //3
			//Tail = New;                       //4
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}

	void insert(int Data,int index)
	{
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = index; i < size - 1; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data); // 1 
		New -> pNext = Temp; //2 новый элемент соединяем с элементом который будет правее его т.е с элементом на котором установлен итератор Temp
		New->pPrev = Temp->pPrev; //3 новый элемент направляем на pPrev предыдущего элемента ченез напревление элемента итератора
		Temp->pPrev->pNext = New; //4 через Temp заходим в предыдущий элемент через pPrev и напревляем его pNext в новый элемент
		Temp->pPrev = New; // 5 pPrew у Temp напревляем на New element

	}

	//       Removing elements:
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
			Head = Head->pNext; //1
			delete Head->pPrev;//2
			Head->pPrev = nullptr;//3
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
			Tail = Tail->pPrev; //1
			delete Tail->pNext; //2
			Tail->pNext = nullptr; //3
		}
		size--;
	}


	//            Methods:
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
		cout << "Tail:\t" << Tail << endl;
		cout << "Количесетво элементов списка: " << size << endl;
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
		cout << "Количесетво элементов списка: " << size << endl;
		cout << delimiter << endl;
	}


};
List operator+(const List& left, const List& right)
{
	List buffer = left;//CopyConstructor
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}


//#define BASE_CHECK
//#define ITERATOR_CHECK
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите колличество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	//for (int i = 0; i < 100; i++)list.pop_back();
	//list.reverse_print();  
	int index;
	int value;
	cout << "Введите итдекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

#endif // BASE_CHECK

#ifdef ITERATOR_CHECK

	List list = { 3,5,8,13,21 };
	//list.print();
	//list.reverse_print();
	for (int i : list) cout << i << tab;cout << endl;
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;





#endif // ITERATOR_CHECK

	List list1 = { 3,5,8,13,21 }; //Operators "ConyAssignment:\t"
	//List list2 = list1;            //CopyConstructor:
	//List list2;                   //Operators "ConyAssignment:\t"
	//list2 = list1;                //Operators "ConyAssignment:\t"
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	//list3.print();                  // operator+
	//list3.reverse_print();          // operator+
	//list2.print();                //Operators "ConyAssignment:\t"
	//list2.reverse_print();        //Operators "ConyAssignment:\t"
	for (int i : list1)cout << i << tab; cout << endl; // operator+
	for (int i : list2)cout << i << tab; cout << endl; // operator+
	for (int i : list3)cout << i << tab; cout << endl; // operator+

}
//37 initializer   2:29:47