#include<iostream>
using namespace std;

#define tab "\t"

//======================1==================================

class Element
{
	int Data;
	Element* pNext;
	static int count; 
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) 
	{
		count++;
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		//cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;

};
int Element::count = 0;

//============================================================

class Iterator
{
	Element* Temp;
public:
	    //constructor
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
    }
	      // перегрузка операторов
	            // ++ инкримент 
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	      // !=
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	     //  * 
	int operator*()
	{
		return Temp->Data;
	}
};

//=======================2===================================


class ForwardList // объединяет элементы в список
  {
	 
	Element* Head;
	unsigned int size;
public:
	Iterator begin() // метод begin для for
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	//                        Constructors:

	ForwardList() // конструктор по умолчанию создает пустой список
	{
		Head = nullptr;// когда список пуст, его Голова указывает на НОЛЬ!
		size = 0;
		cout << "LConstructor: конструктор списка \t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>il) :ForwardList()// преобразует initializerList в ForwardList
	{
		//initializer_list - это контейнер
		//Контейнер - это обьект, который организует хранение других обьектов в памяти.
		// У любого контейнера в обязательном порядке есть как минимум два мутода: begin() - возвращает итератор на начало контейнера.
		// end() - возвращает итератор на конец контейнера.
		cout << typeid(il.begin()).name() << endl;

		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		//initializer_list - всякий раз неявно создается, когда мы перечисляем значения в фигурных скобках черех запятую {, ,}; 
		// ForwardList list = {3,5,8,13,21}; - неявно создается обьект класса initializer_list 

	}
	ForwardList(const ForwardList& other):ForwardList() //конструктор копирования всегда принимает константную ссылку на объект.!!!
	{
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		//	push_back(Temp->Data);
		*this = other; // после создания оператора присваивания = 
		cout << "LCopyCpnstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept :ForwardList()
	{
		//this->Head = other.Head;
		//this->size = other.size;
		//other.Head = nullptr;
		//other.size = 0;
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		//while (Head)pop_back();
		while (Head)pop_front();
		cout << "LDestructor: \t" <<this<< endl;
	}
	//========== Operators ==========================
	ForwardList& operator=(const ForwardList& other)
	{
		if(this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment: " << this << endl;
		return *this;
	}

	
	//метод добавляет значения в начало списка
	// Adding elements:
	void push_front(int Data)
	{
		Head = new Element(Data, Head); // сократилость в 1 строку
		
		//1 создаем новый элемент
		//Element* New = new Element(Data);
		//2 включаем новый элемент в список
		//New->pNext = Head;
		//3 переводим голову на новый элемент
		//Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		
		//1) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data); // сократили до одной строки
		
		//2 создаем новый элемент:
		//Element* New = new Element(Data);
		// 3 Включаем новый элемент в список:
		//Temp->pNext = New;
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0)return push_front(Data);
		//доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		
		Temp->pNext = new Element(Data, Temp->pNext); // сокротили до строки

		// 1 создаем новый элемент
		//Element* New = new Element(Data);
		//2 включаем элемент в список;
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		size++;
	}
	void erase(int Index)
	{	
		if (Index >= size)return;
		if (Index == 0)return pop_front(); 
		// доходим до элемента перед удаляем
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		
		//Запоминаем адрес удаляемого элемента 
		Element* erased = Temp->pNext;
		//исключаем удаляемый элемент из списка
		Temp->pNext = Temp->pNext->pNext;
		//Удаляем элкмент из памяти
		delete erased;
		size--;
	}

	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head; // запоминаем удаляемого элемента
		Head = Head->pNext; //смещаем на голову вперед, исключаем элемент из списка
		delete erased; // удаляем элемент из памяти
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr)return pop_front();
		//if (Head == nullptr)return;
		//if (Head->pNext == nullptr)return pop_front();
		// 1  доходим до предпоследнего элемента списка
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		// удаляем последний элемент
		delete Temp->pNext;
		// 3 зануляем указатель на последний элемент:
		Temp->pNext = nullptr;
		size--;
	}
	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}

	//                 Methods:
	void print()const
	{
		//cout << "Head:\t" << Head << endl;
		//Element* Temp = Head; // Temp - это итератор
		// Итератор - это указатель, при помощи корого можно перебирать элементы сруктуры данных
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;//Переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
		//cout << "Общее количество элементов списка: " << Head->count << endl;
	}
};
void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}


//==================================================================
//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
	void main()
	{
		setlocale(LC_ALL, "");

#ifdef BASE_CHECK
		//Element element(5);
		int n;
		cout << "Введите количество элементов: "; cin >> n;
		ForwardList list;

		for (int i = 0; i < n; i++)
		{
			list.push_back(rand() % 100);
			//list.push_front(rand() % 100);
		}

		list.print();
		/*list.push_back(123);
		list.print();*/
		//list.pop_front();
		//list.print();
		//list.pop_back();
		//list.print();
		int index;
		int value;
		cout << "Введите итдукс нового элемента: "; cin >> index;
		cout << "Введите значение нового элемента: "; cin >> value;
		list.insert(value, index);
		list.print();

		cout << "Введите индекс удаляемого элемента: "; cin >> index;
		list.erase(index);
		list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
		ForwardList list1;
		list1.push_back(3);
		list1.push_back(5);
		list1.push_back(8);
		list1.push_back(13);
		list1.push_back(21);
		list1.print();

		ForwardList list2;
		list2.push_back(34);
		list2.push_back(55);
		list2.push_back(80);
		list2.print();
#endif // COUNT_CHECK


#ifdef PERFORMANCE_CHECK
		int n;
		cout << "Введите количество элементов: "; cin >> n;
		ForwardList list;

		for (int i = 0; i < n; i++)
		{
			//list.push_back(rand() % 100);
			list.push_front(rand() % 100);
		}

		cout << "List filled" << endl;
		list.print();
		cout << "Making Copy" << endl;
		ForwardList list2 = list; // CopyConstructor
		//ForwardList list2;
		//list2 = list;
		list2.print();
		cout << "Copy Done" << endl;

#endif // PERFORMANCE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
		int arr[] = { 3,5,8,13,21 };
		for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		{
			cout << arr[i] << tab;
		}
		cout << endl;

		/// https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
			// Range-based for:
			// Range(диапазон - промежуточных значений) в данном контексте понимется как контейнер.
		for (int i : arr)
		{
			cout << i << tab;
		}
		cout << endl;
		Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
		ForwardList list = { 3,5,8,13,21 };
		//list.print();
		for (int i : list)
		{
			cout << i << tab;
		}
		cout << endl;
#endif // RANGE_BASED_FOR_LIST

	}
	