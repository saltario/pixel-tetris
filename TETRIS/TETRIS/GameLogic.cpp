#include "GameLogic.h";

using namespace sf;
using namespace std;

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
	
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0; //приземление на новую строку
		else if (field[a[i].y][a[i].x]) return 0;//приземление на фигуру
		 return 1; //едет вниз
	
};

bool game(RenderWindow & window)
{

		Player player;
		player.setPlayerName("ANDRE");

		ScreenTetris InterfaceTetris;
		player.setPlayerScore(0);
		player.setPlayerBestScore(0);

		short int font_size = 35;

		Font font;
		font.loadFromFile("IMAGE/04B_03__.ttf");

		if (!font.loadFromFile("IMAGE/04B_03__.ttf"))
		{
		return EXIT_FAILURE;
		}

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

		srand(time(0));

		Texture tilesTexture;
		tilesTexture.loadFromFile("IMAGE/tiles2.png");
		Sprite tiles(tilesTexture);

		Texture backgroundTexture;
		backgroundTexture.loadFromFile("IMAGE/background6.png");
		Sprite background(backgroundTexture);

		Texture frameTexture;
		//frameTexture.loadFromFile("IMAGE/frame.png");
		Sprite frame(frameTexture);
		frame.setPosition(0, 0);

		int dx = 0;
		bool rotate = 0;
		bool w = 1;
		bool active = 1;
		int colorNum = 1;
		float timer = 0;
		float delay = 0.3;
		Clock clock;
		float time;

		while (w == 1)
		{
			time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed)
					window.close();

				if (e.type == Event::KeyPressed)
					if (e.key.code == Keyboard::Up) rotate = true;
					else if (e.key.code == Keyboard::Left) dx = -1;
					else if (e.key.code == Keyboard::Right) dx = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
			//// <- Move -> ///
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

			//////Rotate//////
			if (rotate)
			{
				Point p = a[1]; //center of rotation
				for (int i = 0; i < 4; i++)
				{
					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					a[i].x = p.x - x;
					a[i].y = p.y + y;
				}
				if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			}

			///////Tick//////
			if (timer > delay)
			{
				for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
				if (check() == 0)
				{
						//приземлилась
					for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
					colorNum = 1 + rand() % 7;
					int n = rand() % 7;
					for (int i = 0; i < 4; i++)
					{
						a[i].x = figures[n][i] % 2;
						a[i].y = figures[n][i] / 2;
					}
				}
				if (check() == 1)
				{
					//едет вниз
				}
				timer = 0;
			}

			///////check lines//////////
			int k = M - 1;
			int count = 0;
			for (int i = M - 1; i > 0; i--)
			{
				count = 0;
				for (int j = 0; j < N; j++)
				{
					if (field[i][j]) { count++; }
					field[k][j] = field[i][j];
				}
				if (count < N) { k--; }
				if (count == N)
				{
					player.setPlayerScore(player.getPlayerScore() + 1);
					text_score.setString(Convert(player.getPlayerScore()));
					SaveBestScore("SAVE/score.txt", player.getPlayerScore());
				}
			}
			///////check lines vert//////////
			int k1 = N - 1;
			for (int i = 0; i < M; i++)
			{
				int count1 = 0;
				for (int j = N - 1; j > 0; j--)
				{
					if (field[1][j])
					{									
						count1++;
						for (int h = 0; h < M; h++)
						{
							for (int g = 0; g < N; g++)
							{
								field[h][g] = 0;
							}
						}
						w = 0;
					}
				}
				if (count1 < N) { k1--; }
			}

			dx = 0; rotate = 0; delay = 0.3;

			/////////draw//////////
			window.clear(Color::Black);
			window.draw(background);

			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (field[i][j] == 0) continue;
					tiles.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
					tiles.setPosition(j * 18, i * 18);
					tiles.move(28, 31); //offset
					window.draw(tiles);
				}
			}

			for (int i = 0; i < 4; i++)
			{
				tiles.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
				tiles.setPosition(a[i].x * 18, a[i].y * 18);
				tiles.move(28, 31); //offset
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

			if (active)
			{
				text_score.setString(Convert(player.getPlayerScore()));
				text_best_score.setString(Convert(LoadBestScore("SAVE/save.txt")));
				window.draw(text_score);
				window.draw(text_best_score);
				active = 0;
			}

			window.draw(frame);

			window.display();
			
			if (w == 0) 
			{
				break;
			}		
		}
		if (player.getPlayerScore() >= LoadBestScore("SAVE/save.txt"))
		{
			player.setPlayerBestScore(player.getPlayerScore());
			SaveBestScore("SAVE/save.txt", player.getPlayerBestScore());
		}
		
		return InterfaceTetris.RestartScreen(window);
}
