#pragma once
#include "Utils.h";
#include "GameLogic.h";

/*
Класс для определения экранов игры (не входит экран игрового процесса, см. GameLogic, функция).
	-MenuScreen - главное меню;
	-RestartScreen - экран после проигрыша;
	-AboutScreen - экран "об игре";
*/
class ScreenTetris {
public:
	void MenuScreen(RenderWindow & window);
	bool RestartScreen(RenderWindow & window);
	void AboutScreen(RenderWindow & window, int about);
};
