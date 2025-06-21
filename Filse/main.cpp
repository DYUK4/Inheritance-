//Files
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
	cout << "Hello Filse" << endl;
	std::ofstream fout;     //1 создаем поток
	fout.open("File.txt", std::ios::app); //2 открывает поток. При открытии потока, мы указываем в каой именно файл мы будем писать
	//std::ios::app (append) - дописывать в конец файла
	fout << "Hello Files" << endl;//3 Пишем в поток
	fout << "Привет" << endl;
	fout.close(); // 4 Закрываем поток. Потоки обязательно нужно закрывать, если не закрывать потоки это может привести к непредвиденным последствиям.
	//(Behaviour is undefined) 

	system("notepad File.txt");
#endif // WRITE_TO_FILE
	// 1) создание и открвтие потока можно совместить
	std::ifstream fin("File.txt");
	
	//2) при чтении обязательно нужно проверять открылся поток или нет.
	if (fin.is_open())
	{
		// 3) чтение из файла:
		while (!fin.eof()) // Пока не конец файла - eof(End of File) читаем поток 
		{
			const int SIZE = 102400;
			char buffer[SIZE]{};
			//fin >> buffer; // fin так же как и cin читает до ближайшего пробела, все что после пробела читается в другую переменную до следующего пробела и т.д
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close(); // 4) поток есть смысл закрывать если он был открыть
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

}