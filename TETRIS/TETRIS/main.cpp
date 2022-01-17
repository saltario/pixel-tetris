/*
SFML 2.5.1
VISUAL STUDIO 2015 v14.025420.1
*/
#include "Utils.h"
#include "ScreenTetris.h";

using namespace sf;
using namespace std;

int main(void)
{
	Image icon;
	if (!icon.loadFromFile("IMAGE/icon1.png")) return EXIT_FAILURE;

	Music music;
	if (!music.openFromFile("IMAGE/Deep_Horrors.ogg")) return EXIT_FAILURE;
	music.setVolume(30);
	music.play();

	RenderWindow window(VideoMode(500, 480), "Tetris v1.9 Beta", Style::Close);
	window.setIcon(48, 48, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	ScreenTetris ScreenTetris;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		ScreenTetris.MenuScreen(window);
	}

	return EXIT_SUCCESS;
}