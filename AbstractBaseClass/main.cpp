#include<iostream>
using namespace std;



class Vehicle
{
public:
	virtual void move() = 0;
	
};
//======================================================
class GroundVehicle: public Vehicle{};// јбстрактный класс
class AirVehicle:public Vehicle// добавл€ет абстрактности в своей ветке иеархий
{
public:
	virtual void take_off() = 0;//взлет
	virtual void land() = 0;// посадка
};
//===========================================
class Bike :public GroundVehicle// конкретный пацан :) 
{
public:
	void move()override
	{
		cout << "Harlay Davison едет на двух колесах" << endl;
	}
};

class Car :public GroundVehicle // конкретный класс
{
public:
	void move()override
	{
		cout << "BMW едет на четырех колесах" << endl;
	}

};

class AirPlane : public AirVehicle
{
public:
	void move()override
	{
		take_off();
		cout << "ѕолет нормальный" << endl;
		land();
	}
	void take_off()override
	{
		cout << "Ќужна взлетна€ полоса" << endl;
	}
	void land()override
	{
		cout << "—адимс€ на взлетку" << endl;
	}
};
class Helicopter : public AirVehicle
{
public:
	void move()override
	{
		take_off();
		cout << "Ћетим потихоньку" << endl;
		land();
	}
	void take_off()override
	{
		cout << "ћогу взлететь с любого огорода" << endl;
	}
	void land()override
	{
		cout << "где захочу, там и с€ду " << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Vehicle vehicle;
	//GroundVehicle gv;
	Bike harley_dayidson;
	harley_dayidson.move();
	Car bmw;
	bmw.move();
	AirPlane boeing;
	boeing.move();
	Helicopter blackHawk;
	blackHawk.move();
}



///vid 23    2:20