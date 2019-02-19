#include "field.h"

Field::Field(int a, int b) {
	x = a;
	y = b;

	Tiles.resize(a, std::vector<Tile*>(b, new Tile()));
	for (int i = 1; i < a - 1; i++) {
		for (int j = 1; j < b - 1; j++) {
			Tiles[i][j] = new Tile();
		}
	}
	//Fill most left and most right column with 
	for (int i = 0; i < a; i++) {
		Tiles[i][0] = new Tile(Tile::exit::open, Tile::exit::closed, Tile::exit::open, Tile::exit::closed);
		Tiles[i][b-1] = new Tile(Tile::exit::open, Tile::exit::closed, Tile::exit::open, Tile::exit::closed);
	}
	//Fill top and bottom row with blocks
	for (int i = 0; i < b; i++) {
		Tiles[0][i] = new Tile(Tile::exit::closed, Tile::exit::open, Tile::exit::closed, Tile::exit::open);
		Tiles[a-1][i] = new Tile(Tile::exit::closed, Tile::exit::open, Tile::exit::closed, Tile::exit::open);
	}
	Tiles[1][1] = new Tile(Tile::exit::closed, Tile::exit::open, Tile::exit::open, Tile::exit::closed);
	Tiles[1][1]->name = "Start";
	Tiles[a-2][b-2] = new Tile(Tile::exit::open, Tile::exit::closed, Tile::exit::closed, Tile::exit::open);
	Tiles[a - 2][b - 2]->name = "End";

	this->fill();
	this->replace();
};

void Field::fill() {
	position pos;
	pos.x = 1;
	pos.y = 1;
	//std::cout << "11" << std::endl;

	while (Tiles[pos.x + 1][pos.y]->name != "End" && Tiles[pos.x - 1][pos.y]->name != "End" && Tiles[pos.x][pos.y + 1]->name != "End" && Tiles[pos.x][pos.y - 1]->name != "End") {
		pos = newPosition(pos);
		//std::cout << pos.x;
		//std::cout << pos.y << std::endl;
	}
	connect(pos, position{(int) Tiles.size() - 1, (int) Tiles.at(1).size() - 1 });
}

position Field::newPosition(position p) {
	std::vector<position> available;
	//top free test
	if (p.x > 0) {
		if ((Tiles[p.x][p.y]->t == Tile::exit::open || Tiles[p.x][p.y]->t == Tile::exit::dc) && isFieldEmpty(position{ p.x - 1, p.y })) {
			available.push_back(position{ p.x - 1, p.y });
		}
	}

	//right free test
	if (p.y < Tiles.at(1).size()) {
		if ((Tiles[p.x][p.y]->r == Tile::exit::open || Tiles[p.x][p.y]->r == Tile::exit::dc) && isFieldEmpty(position{ p.x, p.y + 1 })) {
			available.push_back(position{ p.x, p.y + 1 });
		}
	}		
	
	
	//left free test
	if (p.y > 0) {
		if ((Tiles[p.x][p.y]->l == Tile::exit::open || Tiles[p.x][p.y]->l == Tile::exit::dc) && isFieldEmpty(position{ p.x, p.y - 1 })) {
			available.push_back(position{ p.x, p.y - 1 });
		}
	}

	//bottom free test
	if (p.x < Tiles.size()) {
		if ((Tiles[p.x][p.y]->b == Tile::exit::open || Tiles[p.x][p.y]->b == Tile::exit::dc) && isFieldEmpty(position{ p.x + 1, p.y })) {
			available.push_back(position{ p.x + 1, p.y });
		}
	}

	//if empty go to position before
	if (available.empty()) {
		if (worklist.empty()) {
			//std::cout << "Worklist empty";
		}
		position pos = worklist.front();
		worklist.pop_front();
		return pos;
	}

	std::random_shuffle(std::begin(available), std::end(available));
	worklist.push_front(p);
	position q = available.front();
	connect(p, q);
	return q;
}

bool Field::isFieldEmpty(position p) {
	if (p.x < 0 || p.y < 0 || p.x > Tiles.size() || p.y > Tiles.at(1).size()) {
		return false;
	}
	if (Tiles[p.x][p.y]->t == Tile::exit::dc && Tiles[p.x][p.y]->r == Tile::exit::dc && Tiles[p.x][p.y]->b == Tile::exit::dc && Tiles[p.x][p.y]->l == Tile::exit::dc) {
		return true;
	}
	return false;
}

void Field::connect(position a, position b) {
	switch (a.x - b.x) {
	case 0: break; //gleiche Zeile
	case 1: {  //a unter b
		Tiles[a.x][a.y]->t = Tile::exit::open;
		Tiles[b.x][b.y]->b = Tile::exit::open;
		return;
	}
	case -1: { //a über b
		Tiles[a.x][a.y]->b = Tile::exit::open;
		Tiles[b.x][b.y]->t = Tile::exit::open;
		return;
	}
	}

	switch (a.y - b.y) {
	case 0: break; //gleiche Spalte
	case 1: {  //a rechts von b
		Tiles[a.x][a.y]->l = Tile::exit::open;
		Tiles[b.x][b.y]->r = Tile::exit::open;
		return;
	}
	case -1: { //a links von b
		Tiles[a.x][a.y]->r = Tile::exit::open;
		Tiles[b.x][b.y]->l = Tile::exit::open;
		return;
	}
	}

}

void Field::replace() {
	for (int i = 0; i < Tiles.size(); i++) {
		for (int j = 0; j < Tiles.at(1).size(); j++) {
			//std::random_shuffle(std::begin(tilelist), std::end(tilelist));
			while (Tiles[i][j]->rotation == -1) {
				Tile* tester = tilelist.front();
				tilelist.pop_front();
				tilelist.push_back(tester);
				Tiles[i][j]->similiar(tester);
			}
		}
	}
	int i = 1;
	i++;
}

pair Field::getPair(int x, int y) {
	return pair{  std::stoi(Tiles[x][y]->actualTile->name), Tiles[x][y]->rotation };
}