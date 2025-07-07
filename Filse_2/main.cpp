//Filse_2
#include<iostream>
#include<fstream>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;


//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE
	cout << "Hello Filse_2" << endl;
	cout << "Привет" << endl;
	std::ofstream fout; // создаем поток
	fout.open("File.txt", std::ios_base::app); //append - дописывать в конец файла 
	fout << "Hello Filse" << endl;
	fout << "Привет" << endl;
	fout.close();
	system("notepad File.txt");
#endif // WRITE_TO_FILE

	//Прочитать информацию из файла!
	std::ifstream fin("File.txt"); // 1 Создание и открытие потока можно совместить
	if (fin.is_open())// 2 при чтении обязательно нужно проверять, открылся поток, или нет.
	{
	    // 3 чтение из файла //TODO: read from file
		while (!fin.eof())// пока не конец файла - eof(End of File) читаем поток
		{
			const int SIZE = 1024000;
			char buffer[SIZE]{};
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close(); // 4 поток есть смысл закрывать только в том случае, если он был открыт.
	}
	else 
	{
		std::cerr << "Error: File not found" << endl;
	}


}

//22 video//16 min