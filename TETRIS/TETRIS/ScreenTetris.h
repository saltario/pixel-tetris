#pragma once
#include "Utils.h";
#include "GameLogic.h";

/*
����� ��� ����������� ������� ���� (�� ������ ����� �������� ��������, ��. GameLogic, �������).
	-MenuScreen - ������� ����;
	-RestartScreen - ����� ����� ���������;
	-AboutScreen - ����� "�� ����";
*/
class ScreenTetris {
public:
	void MenuScreen(RenderWindow & window);
	bool RestartScreen(RenderWindow & window);
	void AboutScreen(RenderWindow & window, int about);
};
