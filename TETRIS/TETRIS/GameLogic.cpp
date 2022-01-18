#include "GameLogic.h";

using namespace sf;
using namespace std;

char *fontAddress = "Resources/font/pixel_font.ttf";
char *tilesAddress = "Resources/image/tiles.png";
char *gameBackgroundAddress = "Resources/image/game_background.png";

char *saveScoreAddress = "Resources/save/score.txt";
char *saveBestScoreAddress = "Resources/save/best.txt";

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
	int x, y;
} a[4], b[4];

int figures[7][4] = {
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check()
{
	for (int i = 0; i < 4; i++)
	{
		// приземление на новую строку
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		// приземление на фигуру
		else if (field[a[i].y][a[i].x]) return 0;		
	}

	// едет вниз
	return 1; 
};

bool GameScreen(RenderWindow & window)
{
	ScreenTetris ScreenTetris;

	Player player;
	player.setPlayerName("ANDRE");
	player.setPlayerScore(0);
	player.setPlayerBestScore(0);

	Font font;
	short int font_size = 35;
	font.loadFromFile(fontAddress);
	if (!font.loadFromFile(fontAddress)) return EXIT_FAILURE;

	Text text_name("", font, 24);
	text_name.setStyle(sf::Text::Bold);

	Text text_score("", font, 30);
	text_score.setStyle(sf::Text::Bold);

	Text text_best_score("", font, 24);
	text_best_score.setStyle(sf::Text::Bold);

	Text text_score_str("", font, 30);
	text_score_str.setStyle(sf::Text::Bold);

	Text text_best_score_str("", font, 24);
	text_best_score_str.setStyle(sf::Text::Bold);

	Texture tilesTexture;
	tilesTexture.loadFromFile(tilesAddress);
	Sprite tiles(tilesTexture);

	Texture backgroundTexture;
	backgroundTexture.loadFromFile(gameBackgroundAddress);
	Sprite background(backgroundTexture);

	// общее
	Clock clock;
	Event event;
	bool isScreen = true;

	srand(time(0));
	float time;
	float timer = 0;

	int tetrisColor = 1 + rand() % 7;
	int tetrisRandom = rand() % 7;

	int verticalN;
	int horizontalM;

	int verticalCount;
	int horizontalCount;

	// движение
	int dx = 0;
	float delay = 0.3;

	// вращение
	Point centerOfRotation;
	int rotationX;
	int rotationY;
	bool isRotate = false;

	while (isScreen)
	{
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isScreen = 0;
				window.close();
				break;
			}

			if (event.type == Event::KeyPressed)
			{
				// для эвента происъодит обработка однократного нажатия, что позволяет корректно обработать одно нажатие
				// иначе происходит плавное смещение на несколько позиций что актуально только при движении вниз
				if (event.key.code == Keyboard::Up) isRotate = true;
				if (event.key.code == Keyboard::Left) dx = -1;
				if (event.key.code == Keyboard::Right) dx = 1;
			}	
		}

		// обработка длительного нажатия, задерживаем "вниз" и фигура летит вниз плавно и быстро
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

		// движение по горизонтали
		for (int i = 0; i < 4; i++) 
		{ 
			b[i] = a[i]; 
			a[i].x += dx; 
		}

		if (!check()) 
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
		}

		// вращение
		if (isRotate)
		{
			centerOfRotation = a[1];

			for (int i = 0; i < 4; i++)
			{
				rotationX = a[i].y - centerOfRotation.y;
				rotationY = a[i].x - centerOfRotation.x;
				a[i].x = centerOfRotation.x - rotationX;
				a[i].y = centerOfRotation.y + rotationY;
			}

			if (!check())
			{
				for (int i = 0; i < 4; i++)
				{
					a[i] = b[i];
				}
			}
		}

		// движение по времени
		if (timer > delay)
		{
			// движение по вертикали
			for (int i = 0; i < 4; i++) 
			{
				b[i] = a[i];
				a[i].y += 1; 
			}

			if (!check())
			{
				// приземлилась
				for (int i = 0; i < 4; i++)
				{
					field[b[i].y][b[i].x] = tetrisColor;
				}
					
				tetrisColor = 1 + rand() % 7;
				tetrisRandom = rand() % 7;

				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[tetrisRandom][i] % 2;
					a[i].y = figures[tetrisRandom][i] / 2;
				}
			}
			timer = 0;
		}

		// проверка горизонтальных линий
		horizontalM = M - 1;
		horizontalCount = 0;

		for (int i = M - 1; i > 0; i--)
		{
			horizontalCount = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[i][j]) 
				{ 
					horizontalCount++;
				}
				field[horizontalM][j] = field[i][j];
			}

			if (horizontalCount < N)
			{ 
				horizontalM--; 
			}

			if (horizontalCount == N)
			{
				player.setPlayerScore(player.getPlayerScore() + 1);
				text_score.setString(Convert(player.getPlayerScore()));
				SaveBestScore(saveScoreAddress, player.getPlayerScore());
			}
		}
		
		// проверка вертикальных линий
		verticalN = N - 1;
		verticalCount = 0;

		for (int i = 0; i < M; i++)
		{
			verticalCount = 0;
			for (int j = N - 1; j > 0; j--)
			{
				if (field[1][j])
				{
					verticalCount++;
					for (int h = 0; h < M; h++)
					{
						for (int g = 0; g < N; g++)
						{
							field[h][g] = 0;
						}
					}
					isScreen = 0;
				}
			}
			if (verticalCount < N) 
			{ 
				verticalN--; 
			}
		}

		// обнуление
		dx = 0; 
		isRotate = 0; 
		delay = 0.3;

		// отрисовка
		window.clear(Color::Black);
		window.draw(background);

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				tiles.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				tiles.setPosition(j * 18, i * 18);
				tiles.move(28, 31);
				window.draw(tiles);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			tiles.setTextureRect(IntRect(tetrisColor * 18, 0, 18, 18));
			tiles.setPosition(a[i].x * 18, a[i].y * 18);
			tiles.move(28, 31);
			window.draw(tiles);
		}

		text_name.setString(player.getPlayerName());
		text_name.setPosition(250, 20);
		window.draw(text_name);

		text_score_str.setPosition(250, 40);
		text_score_str.setString("YOUR SCORE: ");
		window.draw(text_score_str);

		text_score.setPosition(452, 40);
		window.draw(text_score);

		text_best_score_str.setPosition(250, 70);
		text_best_score_str.setString("BEST SCORE: ");
		window.draw(text_best_score_str);

		text_best_score.setPosition(408, 70);
		window.draw(text_best_score);

		text_score.setString(Convert(player.getPlayerScore()));
		text_best_score.setString(Convert(LoadBestScore(saveBestScoreAddress)));
		window.draw(text_score);
		window.draw(text_best_score);

		window.display();
	}

	if (player.getPlayerScore() >= LoadBestScore(saveBestScoreAddress))
	{
		player.setPlayerBestScore(player.getPlayerScore());
		SaveBestScore(saveBestScoreAddress, player.getPlayerBestScore());
	}

	return ScreenTetris.RestartScreen(window);
}
