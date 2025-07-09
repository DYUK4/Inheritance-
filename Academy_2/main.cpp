﻿#include<iostream>
#include<fstream>
#include<string>
#include<string.h>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-----------------------------------------------\n"
//=============================================================================
//=============================================================================
#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name,first_name,age

class Human
{
	static const int TYPE_WIDTH=12;
	static const int LAST_NAME_WIDTH=15;
	static const int FIRST_NAME_WIDTH=15;
	static const int AGE_WIDTH=5;

	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const { return last_name; }
	const std::string& get_first_name()const { return first_name; }
	int get_age()const { return age; }

	void set_last_name(const std::string& last_name) { this->last_name = last_name; }
	void set_first_name(const std::string& first_name) { this->first_name = first_name; }
	void set_age(int age) { this->age = age; }
              // Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
    }
	virtual ~Human(){cout << "HDestructor:\t" << this << endl;}
	         
	                       // Methods:
	/*void print()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}*/
	//virtual void print()const // после добавления стала выводиться вся информация не только базового класса но и дочерних классов.
	//{
	//	cout << last_name << " " << first_name << " " << age << endl;
	//}
	virtual std::ostream& print(std::ostream& os)const //потоки всегда принимаются и возвращаются по ссылке
	{
		//os << strchr(typeid(*this).name(),' ')+1 << ":\t";// оператор typeid(type|value) определяет тип значения на этапе выполнения программы
		//  метод name() возвращает c_str()содержащую имя типа. 
		return os << last_name << " " << first_name << " " << age; 
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		ofs.width(TYPE_WIDTH); // метод width() задает ширину вывода.
		ofs << std::left;// возвращаем выравнивание по левому краю
		ofs << std::string(strchr(typeid(*this).name(), ' ') + 1)+ ":";
		ofs.width(LAST_NAME_WIDTH);
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << first_name;
		ofs.width(AGE_WIDTH);
		ofs << age;
		return ofs;
	}
	virtual std::ifstream& read(std::ifstream& ifs)// читаем из файлика
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};
std::ostream& operator<<(std::ostream& ost, const Human& obj)
{
	return obj.print(ost);
}
std::ofstream& operator<< (std::ofstream& ofs, const Human& obj)
{
	return obj.print(ofs);
}
std::ifstream& operator>>(std::ifstream& ifs,Human& obj)
{
	return obj.read(ifs);
}
//==========================================================================
//============================================================================
#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendence
#define STUDENT_GIVE_PARAMETERS speciality,group,rating,attendence
class Student :public Human
{
	const static int SPECIALITY_WIDTH   = 25;
	const static int GROUP_WIDTH        = 8;
	const static int RATING_WIDTH       = 8;
	const static int ATTENDANCE_WIDTH   = 8;

	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality() { return speciality; }
	const std::string& get_group() { return group; }
	double get_rating()const { return rating; }
	double get_attendance()const { return attendance; }

	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_group(const std::string& group) { this->group = group; }
	void set_rating(double rating) { this->rating = rating; }
	void set_attendance(double attendance) { this->attendance = attendance; }

	//     Constructors:
	Student(HUMAN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendence);
		cout << "StConstructor:\t"<<this << endl;

    }

	Student(const Human& human,STUDENT_TAKE_PARAMETERS) :Human(human)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendence);
		cout << "S2Constructor:\t" <<this<< endl;
	}

	~Student() { cout << "StDestructor:\t" << this << endl; }

	   // Methods
	std::ostream& print(std::ostream& ost)const override
	{
		return Human::print(ost)<<" " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(RATING_WIDTH);
		ofs << rating;
		ofs.width(ATTENDANCE_WIDTH);
		ofs<< attendance;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		ifs >> speciality >> group >> rating >> attendance;
		return ifs;
	}
};


//==============================================================================
//==============================================================================
#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality,experience

class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int EXPERIENCE_WIDTH = 5;
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality() { return speciality; }
	int get_experience()const { return experience; }

	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_experience(int experience) { this->experience = experience; }
        // Constructor
Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
{
	set_speciality(speciality);
	set_experience(experience);
	cout << "TeConstructor:\t" <<this<< endl;
}
~Teacher() { cout << "TeDestructor:\t" << endl; }
          // Methods
std::ostream& print(std::ostream& ost)const override
{
	return Human::print(ost)<<" " << speciality << " " << experience;
}
std::ofstream& print(std::ofstream& ofs)const override
{
	Human::print(ofs);
	ofs.width(SPECIALITY_WIDTH);
	ofs << speciality;
	ofs.width(EXPERIENCE_WIDTH);
	ofs<< experience;
	return ofs;
}
std::ifstream& read(std::ifstream& ifs) override
{
	Human::read(ifs);
	char sz_speciality[SPECIALITY_WIDTH + 1]{}; //sz_String Ziro - строка заканчивающаяся нулем)
	ifs.read(sz_speciality, SPECIALITY_WIDTH);
	for (int i = SPECIALITY_WIDTH - 2; sz_speciality[i] == ' '; i--)sz_speciality[i] = 0;// убираем пробелы в конце 
	while (sz_speciality[0] == ' ')
		for (int i = 0; sz_speciality[i]; i++)sz_speciality[i] = sz_speciality[i + 1];//убтваем пробелы с переди забивая нулями.
	speciality = sz_speciality;
	ifs >> experience;
	return ifs;
}

};

//==============================================================================
//==============================================================================

class Graduate :public Student
{
	static const int SUBJECT_WIDTH = 20;
	std::string subject;
public:
	const std::string& get_subject() { return subject; }

	void set_subject(const std::string& subject) { this->subject = subject; }

	// Constructor
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject) :Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		cout << "GrConstructor:\t" <<this<< endl;
	}

	Graduate(const Student& student,const std::string subject) :Student(student)
	{
		set_subject(subject);
		cout << "G2Constructor:\t" <<this<< endl;
	}

	~Graduate() { cout << "GrDestructor:\t" << endl; }

	 // Methods
	std::ostream& print(std::ostream& ost)const override
	{
		return Student::print(ost)<<" " << subject;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs);
		ofs.width(SUBJECT_WIDTH);
		ofs<< subject;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		std::getline(ifs, subject); // читает строку с пробелами
		return ifs;
	}

};
//====================================================================
//=======================  Функции  =================================

void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		//group[i]->print();
		if (group[i])
		{
			cout << *group[i] << endl;
			cout << delimiter << endl;
		}
	}
	cout << "Количество человек в группе:" << n << endl;
}
//=============== Save ============================================
void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
		//fout << delimiter << endl;
	}
	fout.close();
	std::string cmd = "notepad " + filename;
	//std::string cmd = "start word " + filename;
	system(cmd.c_str()); // функция system(const char*) выполняет любую доступнкю команду операционной системой.
// метод c_str() возвращает C-string(NULL Terminated Line), обвернутый в объект класс std::string. 
}

Human* HumanFactory(const std::string& type)
{
	Human* human = nullptr;
	if (type == "Human:")human = new Human("", "", 0);
	if (type == "Teacher:")human = new Teacher("","",0,"",0);
	if (type == "Student:")human = new Student("", "", 0, "", "", 0, 0);
	if (type == "Graduate:")human = new Graduate("", "", 0, "", "", 0, 0, "");
	return human;
}
//=================== LOAD ___________======================
bool NotAppropriateType(const std::string& buffer)
{
	// несоответствующий тип: 
	return buffer.find("Human") == std::string::npos &&
		buffer.find("Student") == std::string::npos &&
		buffer.find("Teacher") == std::string::npos &&
		buffer.find("Graduate") == std::string::npos;
}
Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		// 1 вычисляем количество записей в файле. пока мы не начали читать файл размер файла равн НУЛЮ
		n = 0;
		while (!fin.eof())
		{
			std::string buffer;
			//fin.getline(); // не перегружен для объкетов класса std::string
			std::getline(fin, buffer); // читает все до конца строки
			//if (buffer.size() == 0)continue; // проверяем стороку на наличие символов
			if (NotAppropriateType(buffer)) continue;
				/*buffer.find("Human") == std::string::npos &&
				buffer.find("Student") == std::string::npos &&
				buffer.find("Teacher") == std::string::npos &&
				buffer.find("Graduate") == std::string::npos
				) continue;*/
			n++;

		}
		cout << "Количество записей в файле: " << n << endl;
		//2  выделяем память для группы
		group = new Human * [n] {};
		//3 возвращаемся в начало файла для того что бы прочитать содержимое этого файла
		cout << " Позиция курсора на чтение: " << fin.tellg() << endl;
		fin.clear();// очистить поток
		fin.seekg(0);// найти нулевую позицию
		cout << " Позиция курсора на чтение: " << fin.tellg() << endl;
		
		// 4 читаем файл 
		for (int i = 0;i<n; i++)
		{
			std::string type;
			fin >> type;
			if (NotAppropriateType(type))continue;
			group[i] = HumanFactory(type);
			if (group[i])fin >> *group[i];

			/*std::string buffer;
			std::getline(fin, buffer);*/

		}
		fin.close(); //  закрываем файл если он был открыт
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	return group;
}


void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}



//==============================================================================
//==============================================================================

//#define INHERITANCE_1
//#define INHERITANCE_2 // второй способ создание объектов при наследовании
//#define SAVE_CHECK
#define LOAD_CHECK

void main()
{
	setlocale(LC_ALL, "");
	cout << "HelloAcademy" << endl;
	
#ifdef INHERITANCE_1
	cout << delimiter << endl;
	Human human("Richter", "Jeffrey", 40);
	human.print();
	cout << delimiter << endl;

	Student student("Pinkman", "Jassie", 20, "Chinestry", "WW_220", 95, 90);
	student.print();
	cout << delimiter << endl;

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();
	cout << delimiter << endl;

	Graduate graduate("Schrader", "Hank", 40, "Criminalistic", "OBN", 50, 70, "How to catch Heisenberg");
	graduate.print();
	cout << delimiter << endl;

#endif // INHERITANCE_1

#ifdef INHERITANCE_2
	Human human("Vercetty", "Tomy", 30);
	human.print();
	cout << delimiter << endl;

	Student student(human, "Theft", "Vice", 95, 98);
	student.print();
	cout << delimiter << endl;

	Graduate graduate(student, "How to make money");
	graduate.print();
	cout << delimiter << endl;
#endif // INHERITANCE_2
#ifdef SAVE_CHECK

	/*cout << &Student::print << endl;
	cout << &Teacher::print << endl;
	cout << &Graduate::print << endl;*/


	Human* group[] =  //Указатель на базовый класс (Base-Class Pointer)
	{
		new Student("Pinkman","Jessie",20,"Chenistry","WW_220",95,90),
		new Teacher("White","Walter",50,"Chemistry",25),
		new Graduate("Schrader","Hank",40,"Criminalistic","OBN",50,70,"How to catch Heisenderg"),
		new Student("Vercetti","Tommy",30,"Theft","Vice",95,98),
		new Teacher("Diaz","Ricardo",50,"Weapons distributin",20)
	};
	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Clear(group, sizeof(group) / sizeof(group[0]));

	//Выводим массив на экран
	//cout << delimiter << endl;
	//for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	//{
	//	//group[i]->print();
	//	cout << *group[i] << endl;
	//	cout << delimiter << endl;
	//}

	//// удаление объектов new
	//for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	//{
	//	delete group[i];
	//}  
#endif // SAVE_CHECK

#ifdef LOAD_CHECK
	int n = 0;
	Human** group = Load("group.txt", n);
	Print(group, n);
	Clear(group, n);


#endif // LOAD_CHECK


}
// 23 1:24min