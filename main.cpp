#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace sf;

int main()
{
	//Создаём окно 600х600 60 FPS
	RenderWindow window(VideoMode(600, 600), "15");
	window.setFramerateLimit(60);

	Font font;
	font.loadFromFile("calibri.ttf");

	//текст с обозначением клавиш
	Text text("F2 - New Game / Esc - Exit / Arrow Keys - Move Tile", font, 20);
	text.setFillColor(Color::Cyan);
	text.setPosition(5.f, 5.f);

	//создаём объект игры
	Game game;
	game.setPosition(50.f, 50.f);

	Event event;
	int move_counter = 0; //счётчик случайных ходов для перемешивания головоломки

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed)
			{
				//получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == Keyboard::Escape) window.close();
				if (event.key.code == Keyboard::Left) game.Move(Direction::Left);
				if (event.key.code == Keyboard::Right) game.Move(Direction::Right);
				if (event.key.code == Keyboard::Up) game.Move(Direction::Up);
				if (event.key.code == Keyboard::Down) game.Move(Direction::Down);
				//новая игра
				if (event.key.code == Keyboard::F2)
				{
					game.Init();
					move_counter = 100;
				}
			}
		}
		//если счётчик ходов больше нуля, продолжаем перемешивать головоломку
		if (move_counter-- > 0) game.Move((Direction)(rand() % 4));

		//выполняем необходимые действия по отрисовке
		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}

	return 0;
}