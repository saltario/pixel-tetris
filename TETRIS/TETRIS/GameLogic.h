#pragma once
#include "ScreenTetris.h";
#include "Utils.h"

// Функция для проверки: приземлилась фигура или нет
bool check();

// Функция для отрисовки игрового процесса + основная логика движения фигур по плоскости.
bool GameScreen(RenderWindow & window);
