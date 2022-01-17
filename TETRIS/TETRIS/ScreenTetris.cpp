#include "ScreenTetris.h";

void ScreenTetris::MenuScreen(RenderWindow & window)
{
	bool exit;
	int about = 1;
	bool isButton = 1;
	int Number = 0;

	Texture t_start_btn, t_exit_btn, t_about_btn;

	t_start_btn.loadFromFile("IMAGE/start.png");
	t_exit_btn.loadFromFile("IMAGE/exit.png");
	t_about_btn.loadFromFile("IMAGE/about.png");

	Texture backgroundTexture;
	backgroundTexture.loadFromFile("IMAGE/background8.png");

	Sprite start_btn(t_start_btn);
	Sprite exit_btn(t_exit_btn);
	Sprite about_btn(t_about_btn);
	Sprite background(backgroundTexture);

	start_btn.setPosition(190, 160);
	exit_btn.setPosition(190, 220);
	about_btn.setPosition(190, 280);
	background.setPosition(0, 0);

	Font font;
	font.loadFromFile("IMAGE/04B_03__.ttf");

	Text text_name("", font, 160);
	text_name.setStyle(sf::Text::Bold);
	text_name.setPosition(0, -40);
	text_name.setString("TETRIS");


	while (isButton)
	{
		sleep(milliseconds(100));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		start_btn.setColor(Color::Cyan);
		exit_btn.setColor(Color::Cyan);
		about_btn.setColor(Color::Cyan);

		Number = 0;

		window.clear(Color::Black);

		if (IntRect(190, 160, 110, 40).contains(Mouse::getPosition(window))) { start_btn.setColor(Color::Blue);    Number = 1; }
		if (IntRect(190, 220, 110, 40).contains(Mouse::getPosition(window))) { exit_btn.setColor(Color::Blue);     Number = 2; }
		if (IntRect(190, 280, 110, 40).contains(Mouse::getPosition(window))) { about_btn.setColor(Color::Blue);    Number = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Number == 1)
			{
				exit = game(window);
				if (exit == 0) { window.close(); }
				if (exit == 1) { MenuScreen(window); }
			}
			if (Number == 2) { window.close(); }
			if (Number == 3) { AboutScreen(window, about); }
		}
		//DRAW
		window.draw(background);

		window.draw(text_name);
		window.draw(text_name);

		window.draw(start_btn);
		window.draw(exit_btn);
		window.draw(about_btn);

		window.display();
	}
}

bool ScreenTetris::RestartScreen(RenderWindow & window)
{
	bool isButton = 1;
	int Number = 0;

	Texture t_again_btn, t_exit_btn;
	t_again_btn.loadFromFile("IMAGE/again.png");
	t_exit_btn.loadFromFile("IMAGE/exit.png");

	Texture backgroundTexture;
	backgroundTexture.loadFromFile("IMAGE/background1.png");

	Sprite again_btn(t_again_btn);
	Sprite exit_btn(t_exit_btn);
	Sprite background(backgroundTexture);

	again_btn.setPosition(190, 270);
	exit_btn.setPosition(190, 320);
	background.setPosition(0, 0);

	Font font;
	font.loadFromFile("IMAGE/04B_03__.ttf");

	Text text_name("", font, 90);
	text_name.setStyle(sf::Text::Bold);
	text_name.setPosition(8, 0);
	text_name.setString("GAME OVER");

	Text text_best("", font, 50);
	text_best.setStyle(sf::Text::Bold);

	while (isButton)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		again_btn.setColor(Color::Cyan);
		exit_btn.setColor(Color::Cyan);

		Number = 0;

		window.clear(Color::Black);

		if (IntRect(190, 270, 110, 40).contains(Mouse::getPosition(window))) { again_btn.setColor(Color::Blue);    Number = 1; }
		if (IntRect(190, 320, 110, 40).contains(Mouse::getPosition(window))) { exit_btn.setColor(Color::Blue);     Number = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Number == 1) { return 1; }

			if (Number == 2) { window.close(); }
		}
		//DRAW

		window.draw(background);

		window.draw(again_btn);
		window.draw(exit_btn);
		window.draw(text_name);

		text_best.setPosition(75, 100);
		text_best.setString("YOUR SCORE: ");
		window.draw(text_best);

		text_best.setPosition(390, 100);
		text_best.setString(Convert(LoadBestScore("SAVE/score.txt")));
		window.draw(text_best);

		window.draw(text_name);

		window.display();
	}
}

void ScreenTetris::AboutScreen(RenderWindow & window, int about)
{
	int exit = about;
	bool isButton = 1;
	int Number = 0;

	Texture t_exit_btn;
	t_exit_btn.loadFromFile("IMAGE/exit.png");

	Texture backgroundTexture, sfmlTexture;
	backgroundTexture.loadFromFile("IMAGE/background1.png");
	sfmlTexture.loadFromFile("IMAGE/sfml.png");

	Sprite exit_btn(t_exit_btn);
	Sprite background(backgroundTexture);
	Sprite sfmlLogo(sfmlTexture);

	exit_btn.setPosition(190, 300);
	background.setPosition(0, 0);
	sfmlLogo.setPosition(450, 430);

	Font font;
	font.loadFromFile("IMAGE/04B_03__.ttf");

	Text text_name("", font, 60);
	text_name.setStyle(sf::Text::Bold);
	text_name.setPosition(30, 25);
	text_name.setString("THIS GAME BY");

	Text text_andre("", font, 20);
	text_andre.setStyle(sf::Text::Bold);
	text_andre.setPosition(63, 105);
	text_andre.setString("ANDRE: PICTURE AND UI DESIGNER");

	Text text_coder("", font, 20);
	text_coder.setStyle(sf::Text::Bold);
	text_coder.setPosition(115, 130);
	text_coder.setString("ANARANT: PROGRAMMER");


	while (isButton)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		exit_btn.setColor(Color::Cyan);

		Number = 0;

		window.clear(Color::Black);

		if (IntRect(190, 300, 110, 40).contains(Mouse::getPosition(window))) { exit_btn.setColor(Color::Blue);     Number = 1; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Number == 1)
			{

				MenuScreen(window);
			}

		}
		//DRAW
		window.draw(background);
		window.draw(sfmlLogo);

		window.draw(text_name);
		window.draw(text_andre);
		window.draw(text_coder);

		window.draw(exit_btn);

		window.display();
	}
}
