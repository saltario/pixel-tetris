#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Player.h"

using namespace sf;
using namespace std;

int LoadBestScore(char *fileAddress);
void SaveBestScore(char *fileAddress, int BestScore);

template<typename T>
T fromString(const string& string);

template <typename T>
string toString(T value);

String Convert(int value);
