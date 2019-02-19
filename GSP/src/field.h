#include "tile.h"
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>
#include <string>


struct position{
	int x;
	int y;
};

struct pair {
	int b;
	int rot;
};

class Field {
public:
	int x, y;

	Tile* B01 = new Tile(Tile::exit::open, Tile::exit::closed, Tile::exit::open, Tile::exit::closed, -1, std::string("1"));
	Tile* B02 = new Tile(Tile::exit::closed, Tile::exit::closed, Tile::exit::open, Tile::exit::open, -1, std::string("2"));
	Tile* B03 = new Tile(Tile::exit::closed, Tile::exit::open, Tile::exit::open, Tile::exit::open,-1, std::string("3"));
	Tile* B04 = new Tile(Tile::exit::open, Tile::exit::open, Tile::exit::open, Tile::exit::open, -1, std::string("4"));

	std::list<Tile*> tilelist = { B01, B02, B03, B04 };
	std::list<position> worklist;
	std::vector<std::vector<Tile*>> Tiles;
	Field(int x, int y);
	//Field();

	position newPosition(position p);
	bool isFieldEmpty(position p);
	void fill();
	void replace();
	void connect(position a, position b);
	pair getPair(int x, int y);


};