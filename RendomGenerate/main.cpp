#include<iostream>
#include<random>
using namespace std;

bool isCorrect(int guess, int answer);

int main()
{
	setlocale(LC_ALL, "");

	default_random_engine engine{ random_device{}() };
	uniform_int_distribution<int>randomInt{ 1,1000 };

	char response = 'n';

	do 
	{
		const int answer{ randomInt(engine) };

		cout << "I have a number between 1 and 1000.\n "
			<< "Can you guess my number?\n"
			<< "Please type your first guess." << endl << "? ";
		int guess;
		cin >> guess;

		while (!isCorrect(guess, answer)) 
		{ cin >> guess; } 

		cout << "\nExcellent! You guessed the number!\n"
			<< "Would you like to play again (y or n) ?";
		cin >> response;

		cout << endl;
	} while (response == 'y');
	return 0;
}

bool isCorrect(int guess, int answer)
{
	if (guess == answer)
	{
		return true;
	}
	if (guess < answer)
	{
		cout << "Too low. Try again.\n? ";
	}
	else {
		cout << "Too high. Try again.\n? ";
	}
	return false;
}
// 11 10 10 10