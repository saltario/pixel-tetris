#pragma once
#include "Utils.h";
#include "GameLogic.h";

/*
Класс для определения экранов игры (не входит экран игрового процесса, см. GameLogic, функция GameScreen).
	-MenuScreen - главное меню;
	-RestartScreen - экран после проигрыша;
	-AboutScreen - экран "об игре";
*/
class ScreenTetris {
public:

	char *fontAddress = "Resources/font/pixel_font.ttf";
	char *startButtonAddress = "Resources/image/start_button.png";
	char *exitButtonAddress = "Resources/image/exit_button.png";
	char *aboutButtonAddress = "Resources/image/about_button.png";
	char *menuButtonAddress = "Resources/image/menu_button.png";
	char *againButtonAddress = "Resources/image/again_button.png";
	char *sfmlIconAddress = "Resources/image/sfml_icon.png";
	char *menuBackgroundAddress = "Resources/image/menu_background.png";

	char *saveScoreAddress = "Resources/save/score.txt";
	char *saveBestScoreAddress = "Resources/save/best.txt";

	void MenuScreen(RenderWindow & window);
	bool RestartScreen(RenderWindow & window);
	void AboutScreen(RenderWindow & window);
};
