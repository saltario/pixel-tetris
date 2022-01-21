/*

SFML 2.5.1
VISUAL STUDIO 2015 v14.025420.1

*/
#include "Utils.h"
#include "ScreenTetris.h";

using namespace sf;
using namespace std;

char *iconAddress = "Resources/image/icon.png";
char *musicAddress = "Resources/sound/deep_sound.ogg";

int main(void)
{
	Image icon;
	if (!icon.loadFromFile(iconAddress)) return EXIT_FAILURE;

	Music music;
	if (!music.openFromFile(musicAddress)) return EXIT_FAILURE;
	music.setVolume(30);
	music.play();

	RenderWindow window(VideoMode(500, 480), "Tetris Beta", Style::Close);
	window.setIcon(48, 48, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	ScreenTetris ScreenTetris;
	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				break;
			}
		}

		ScreenTetris.MenuScreen(window);
	}

	return EXIT_SUCCESS;
}