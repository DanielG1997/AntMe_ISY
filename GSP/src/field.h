#include "tile.h"
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>
#include <string>


struct Position{
	int x;
	int y;
};

struct Pair {
	int b;
	int rot;
};

class Field {
public:
	int x, y;

	Tile* B01 = new Tile(Tile::exit::closed, Tile::exit::open, Tile::exit::closed, Tile::exit::open, -1, std::string("1"));
	Tile* B02 = new Tile(Tile::exit::closed, Tile::exit::open, Tile::exit::open, Tile::exit::closed, -1, std::string("2"));
	Tile* B03 = new Tile(Tile::exit::open, Tile::exit::closed, Tile::exit::open, Tile::exit::open,-1, std::string("3"));
	Tile* B04 = new Tile(Tile::exit::open, Tile::exit::open, Tile::exit::open, Tile::exit::open, -1, std::string("4"));

	std::list<Tile*> tilelist = { B01, B02, B03, B04 };
	std::list<Position> worklist;
	std::vector<std::vector<Tile*>> Tiles;
	Field(int x, int y);

	Position newPosition(Position p);
	bool isFieldEmpty(Position p);
	void fill();
	void replace();
	void connect(Position a, Position b);
	Pair getPair(int x, int y);


};