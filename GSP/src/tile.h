#include <string>

class Tile {
	

public:
	enum exit { open, closed, dc };
	std::string name;
	Tile* actualTile;
	int rotation;
	Tile();
	Tile(exit t, exit r, exit b, exit l, int rot = -1, std::string = "");
	int similiar(Tile* t);

	exit t;
	exit r;
	exit b;
	exit l;	
};