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
	cout << "������" << endl;
	std::ofstream fout; // ������� �����
	fout.open("File.txt", std::ios_base::app); //append - ���������� � ����� ����� 
	fout << "Hello Filse" << endl;
	fout << "������" << endl;
	fout.close();
	system("notepad File.txt");
#endif // WRITE_TO_FILE

	//��������� ���������� �� �����!
	std::ifstream fin("File.txt"); // 1 �������� � �������� ������ ����� ����������
	if (fin.is_open())// 2 ��� ������ ����������� ����� ���������, �������� �����, ��� ���.
	{
	    // 3 ������ �� ����� //TODO: read from file
		while (!fin.eof())// ���� �� ����� ����� - eof(End of File) ������ �����
		{
			const int SIZE = 1024000;
			char buffer[SIZE]{};
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close(); // 4 ����� ���� ����� ��������� ������ � ��� ������, ���� �� ��� ������.
	}
	else 
	{
		std::cerr << "Error: File not found" << endl;
	}


}

//22 video//16 min