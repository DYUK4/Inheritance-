#include <iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n--------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name,first_name,age

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const { return last_name; }
	const std::string& get_first_name()const { return first_name; }
	int get_age()const { return age; }

	void set_last_name(const std::string& last_name) { this->last_name = last_name; }
	void set_first_name(const std::string& first_name) { this->first_name = first_name; }
	void set_age(int age) {this->age = age;}
	
	// Constructors:

	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human() { cout << "HDestructor:\t" << this << endl; }
	
	 // Methods:
	virtual  std::ostream& print(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
		//cout << last_name << " " << first_name << " " << age << endl;
	}
	
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);// .get_last_name();
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality,group,rating,attendance

class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const { return speciality; }
	const std::string& get_group()const { return group; }
	double get_rating()const { return rating; }
	double get_attendance()const { return attendance; }

	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_group(const std::string& group) { this->group = group; }
	void set_rating(double rating) { this->rating = rating; }
	void set_attendance(double attendence) { this->attendance = attendence; }

	// Constructor:

	Student
	(HUMAN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);

	}
	Student(const Human& human, STUDENT_TAKE_PARAMETERS) :Human(human)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;

	}
	~Student() { cout << "SDestructor:\t" << this << endl; }

	//   Methods:
	 std::ostream& print(std::ostream& os)const override
	{
		
		 return Human::print(os)<<" " << speciality << " " << group << " " << rating << " " << attendance;
		 
		 /*Human::print();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;*/
	}
};

#define TECHER_TAKE_PARAMETERS const std::string& speciality,int experience
#define TECHER_GIVE_PARAMETERS speciality,ecperientce

class Teacher :public Human
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const { return speciality; }
	int get_experience()const { return experience; }

	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_experience(int experientce) { this->experience = experientce; }

	// Constructors:
	Teacher(HUMAN_TAKE_PARAMETERS,TECHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout<< "TConstructor:\t" <<this<< endl;
    }
	~Teacher() { cout << "TDestructor:\t" <<this<< endl; }

	//  Methods:
	std::ostream&  print(std::ostream& os)const override
	{
		return Human::print(os)<<" " << speciality << " " << experience << " years";
		/*Human::print();
		cout << speciality << " " << experience << " years" << endl;*/
	}

};

#define GRADUATE_TAKE_PARAMETERS const std::string& subject
#define GRADUATE_GIVE_PARAMETERS subject

class Graduate :public Student
{
	std::string subject;
	//std::string theme;
	//int course;
public:
	const std::string& get_subject()const { return subject; }
	//const std::string& get_theme()const { return theme; }
	//int get_course()const { return course; }

	void set_subject(const std::string& subject) { this->subject = subject; }
	//void set_theme(const std::string& theme) { this->theme = theme; }	
	//void set_course(int course) { this->course = course; }

	 // Constructor
	Graduate(HUMAN_TAKE_PARAMETERS,STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS):
		Student(HUMAN_GIVE_PARAMETERS,STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		//set_theme(theme);
		//set_course(course);
		cout << "GConstructor:\t" << this << endl;
	}
	Graduate(const Student& student, GRADUATE_TAKE_PARAMETERS) :Student(student)
	{
		set_subject(subject);
		cout << "G2Constructor:\t" << this << endl;
	}

	~Graduate() { cout << "GDestructor:\t" << this << endl; }

	// Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Student::print(os)<<" " << subject;
		/*Student::print();
		cout << subject <<endl;*/
	}

};

void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		//group[i]->print();
		cout << *group[i] << endl;
		cout << delimiter << endl;
	}
}
void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}

//#define INHERITANCE_1
//#define INHERITANCE_2

void main()
{
	setlocale(LC_ALL, "");
	cout << "HelloAcademy" << endl;
#ifdef INHERITANCE_1
	cout << delimeter;
	Human human("Richter", "Jeffrey", 40);
	human.print();
	cout << delimiter;
	Student student("Pinkman", "Jessie", 20, "Chenistry", "WW_220", 95, 90);
	student.print();
	cout << delimiter;
	Teacher teacher("White", "Walter", 50, "Chimetry", 25);
	teacher.print();
	cout << delimiter;
	Graduate graduate("Ivanov", "Petr", 20, "Chenistry", "WW_220", 95, 90, "Matem");
	graduate.print();
	cout << delimiter;
#endif // INHERITANCE_1
#ifdef INHERITANCE_2
	Human human("Vercetty", "Tomy", 30);
	human.print();
	cout << delimiter;
	Student student(human, "Theft", "Vice", 95, 98);
	student.print();
	cout << delimiter;
	Graduate graduate(student, "How to make mony");
	graduate.print();
	cout << delimiter;
#endif // INHERITANCE_2

	
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chenistry", "WW_220", 95, 90),
		new Teacher("White", "Walter", 50, "Chimetry", 25),
		new Graduate("Ivanov", "Petr", 20, "Chenistry", "WW_220", 95, 90, "Matem"),
		new Student("Varcetti","Tommy",30,"Theft","Vice",95,98),
		new Teacher("Diaz","Ricardo",50,"Weapons distribution",20)
	};
	
	Print(group, sizeof(group) / sizeof(group[0]));
	Clear(group, sizeof(group) / sizeof(group[0]));
	//cout << delimiter << endl;
	//for (int i = 0; i <sizeof(group)/sizeof(group[0]); i++)
	//{
	//	//group[i]->print();
	//	cout << *group[i] << endl;
	//	cout << delimiter << endl;
	//}
	
	
}