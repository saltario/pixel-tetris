#include "GameLogic.h"
#include "Utils.h";

using namespace sf;
using namespace std;

void SaveBestScore(char *fileAddress, int BestScore)
{
	ofstream fin;
	fin.open(fileAddress, ios::out);
	fin << BestScore;
	fin.close();
}

void SaveScore(char *fileAddress, int BestScore)
{
	ofstream fin;
	fin.open(fileAddress, ios::out);
	fin << BestScore;
	fin.close();
}

int LoadBestScore(char *fileAddress)
{
	int BestScore;
	ifstream fout;

	fout.open(fileAddress);
	fout >> BestScore;
	fout.close();

	return BestScore;
}

template <typename T>
string toString(T value)
{
	ostringstream oss;
	oss << value;
	return oss.str();
}

template<typename T>
T fromString(const string& string)
{
	istringstream iss(string);
	T res;
	iss >> res;
	return res;
}

String Convert(int value)
{
	String string;
	string = toString(value);
	return string;
}
