/*SFML 2.5.1
  VISUAL STUDIO 2015 v14.025420.1*/
#include "Utils.h"
#include "ScreenTetris.h";

using namespace sf;
using namespace std;

int main(void)
{
	/////////RENDER SCREEN/////////
	RenderWindow window(VideoMode(500, 480), "Tetris v1.9 Beta", Style::Close); //инициализация окна

	window.setVerticalSyncEnabled(true); //вертикальная синхронизация
	window.setFramerateLimit(30); //ограничитель кадров в секунду до 30
	
	ScreenTetris ScreenTetris;
	
	Music music;
	if (!music.openFromFile("IMAGE/Deep_Horrors.ogg")) return EXIT_FAILURE;
	music.setVolume(30);
	music.play();


	Image icon;
	if (!icon.loadFromFile("IMAGE/icon1.png"))
	{
		return EXIT_FAILURE;
	}
	window.setIcon(48, 48, icon.getPixelsPtr());
	
		
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			ScreenTetris.MenuScreen(window);
		}
	
	return EXIT_SUCCESS;
}