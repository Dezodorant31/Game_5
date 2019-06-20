#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int SIZE = 4;
const int ARRAY_SIZE = SIZE * SIZE;
const int FIELD_SIZE = 500;
const int CELL_SIZE = 120;

enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class Game:public Drawable, public Transformable
{
protected:
	int elements[ARRAY_SIZE]; //массив, содержащий целочисл. значени¤, соот. состо¤нию игрового пол¤.
	int empty_index; //индекс в массиве, соот. свободной ¤чейке
	int solved; //признак того, что головоломка решена
	Font font; //определение шрифта в выводе текста
public:
	Game();
	void Init(); //инициализаци¤ игры
	bool Check(); //проверка, решена ли головоломка
	void Move(Direction direction); //перемещение плашек в игре
public:
	virtual void draw(RenderTarget& target, RenderStates states) const; //отрисовка игрового пол¤
};

