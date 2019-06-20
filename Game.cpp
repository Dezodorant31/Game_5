#include "Game.h"

Game::Game()
{
	//Подгружаем шрифт для отрисовки элементов
	font.loadFromFile("calibri.ttf");
	Init();
}

void Game::Init()
{
	//Заполняем массив плашек
	for (int i = 0; i < ARRAY_SIZE - 1; i++)elements[i] = i + 1;
	//Пустая ячейка- в последнем элементе массива
	empty_index = ARRAY_SIZE - 1;
	elements[empty_index] = 0; //Пустая плашка имеет значение = 0
	solved = true;
}

bool Game::Check()
{
	//Проверка собранности головоломки
	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		if (elements[i] > 0 && elements[i] != i + 1) return false;
	}
	return true;
}

void Game::Move(Direction direction)
{
	//вычисляем строку и колонку пустой плашки
	int col = empty_index % SIZE;
	int row = empty_index / SIZE;

	//проверка на возможность перемещения и вычисления индекса перемещаемой плашки
	int move_index = -1;
	if (direction == Direction::Left && col < (SIZE - 1)) move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0) move_index = empty_index - 1;
	if (direction == Direction::Up && row < (SIZE - 1)) move_index = empty_index + SIZE;
	if (direction == Direction::Down && row > 0) move_index = empty_index - SIZE;

	//перемещение плашки на место пустой
	if (empty_index >= 0 && move_index >= 0)
	{
		int tmp = elements[empty_index];
		elements[empty_index] = elements[move_index];
		elements[move_index] = tmp;
		empty_index = move_index;
	}
	solved = Check();
}

void Game::draw(RenderTarget & target, RenderStates states) const
{
	states.transform *= getTransform();
	Color color = Color(200, 100, 200);

	//рисуем рамки игрового поля
	RectangleShape shape(Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(Color::Transparent);
	target.draw(shape, states);

	//подготовка рамок для отрисовки всех плашек
	shape.setSize(Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(Color::Transparent);

	//подготовка текстовой заготовки для отрисовки номеров плашек
	Text text(" ", font, 52);

	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(to_string(elements[i]));
		if (solved)
		{
			//решенную головоломку выделяем другим цветом
			shape.setOutlineColor(Color::Cyan);
			text.setFillColor(Color::Cyan);
		}
		else if (elements[i] == i + 1)
		{
			//номера плашек на своих местах выделяем другим цветом
			text.setFillColor(Color::Green);
		}

		//рисуем все плашки, кроме пустой
		if (elements[i] > 0)
		{
			//вычисление позиции плашки для отрисовки
			Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			//отрисовываем текст
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			//отрисовываем рамку плашки
			target.draw(shape, states);
			//отрисовываем номер плашки
			target.draw(text, states);
		}
	}
}

