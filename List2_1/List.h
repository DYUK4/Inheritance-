#pragma once
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
	}*Head, * Tail;

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
	class ConstIterator :public ConstBaseIterator // прямой итератор в одну сторону ->
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
	class ConstReverseIterator :public ConstBaseIterator // обратный итератор <-
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
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}

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