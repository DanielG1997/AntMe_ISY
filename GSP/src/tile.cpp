#include "tile.h";

Tile::Tile(exit top, exit right, exit bottom, exit left, int rot, std::string n) {
	t = top;
	r = right;
	b = bottom;
	l = left;
	rotation = rot;
	name = n;
}

Tile::Tile() {
	t = dc;
	r = dc;
	b = dc;
	l = dc;
	rotation = -1;
}

int Tile::similiar(Tile* o) {
	// keine drehung
	if ((this->t == dc || (this->t == open && o->t == open) || (this->t == closed && o->t == closed))
		&& (this->r == dc || (this->r == open && o->r == open) || (this->r == closed && o->r == closed))
		&& (this->b == dc || (this->b == open && o->b == open) || (this->b == closed && o->b == closed))
		&& (this->l == dc || (this->l == open && o->l == open) || (this->l == closed && o->l == closed))) {
		actualTile = o;
		rotation = 0;
		return 0;
	}

	//90° Drehung i.U. von o
	if ((this->t == dc || (this->t == open && o->l == open) || (this->t == closed && o->l == closed))
		&& (this->r == dc || (this->r == open && o->t == open) || (this->r == closed && o->t == closed))
		&& (this->b == dc || (this->b == open && o->r == open) || (this->b == closed && o->r == closed))
		&& (this->l == dc || (this->l == open && o->b == open) || (this->l == closed && o->b == closed))) {
		actualTile = o;
		rotation = 270;
		return 90;
	}

	//180° Drehung i.U. von o
	if ((this->t == dc || (this->t == open && o->b == open) || (this->t == closed && o->b == closed))
		&& (this->r == dc || (this->r == open && o->l == open) || (this->r == closed && o->l == closed))
		&& (this->b == dc || (this->b == open && o->t == open) || (this->b == closed && o->t == closed))
		&& (this->l == dc || (this->l == open && o->r == open) || (this->l == closed && o->r == closed))) {
		actualTile = o;
		rotation = 180;
		return 180;
	}

	//270° Drehung i.U. von o
	if ((this->t == dc || (this->t == open && o->r == open) || (this->t == closed && o->r == closed))
		&& (this->r == dc || (this->r == open && o->b == open) || (this->r == closed && o->b == closed))
		&& (this->b == dc || (this->b == open && o->l == open) || (this->b == closed && o->l == closed))
		&& (this->l == dc || (this->l == open && o->t == open) || (this->l == closed && o->t == closed))) {
		actualTile = o;
		rotation = 90;
		return 270;
	}
	return -1;
}