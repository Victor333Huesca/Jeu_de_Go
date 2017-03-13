#include <iostream>
#include "Etat.h"

//CONSTRUCTORS

Etat::Etat(){//default constructor
  x=-1;
  y=-1;
  val=VIDE;
}

Etat::Etat(size_t X, size_t Y, VAL V){//parametric constructor
  x= X;
  y= Y;
  val= V;
}

Etat::Etat(const Etat& E){//copy constructor
  if (this != &E)
  {
    x= E.x;
    y= E.y;
    val= E.val;
  }
}

//GETTERS

size_t Etat::getX() const{
  return x;
}

size_t Etat::getY() const{
  return y;
}

Etat::VAL Etat::getVal() const{
  return val;
}

//SETTERS

void Etat::setX(size_t X){
  x=X;
}

void Etat::setY(size_t Y){
  y=Y;
}

void Etat::setVal(VAL V){
  val=V;
}

//OVERLOADINGS METHODES

bool Etat::operator==(const Etat& E)const{
  return (x==E.x && y==E.y && val==E.val);
}

bool Etat::operator!=(const Etat& E) const{
  return !(*this==(E));
}

Etat Etat::operator=(const Etat& E){
  if (this != &E){
    x=E.x;
    y=E.y;
    val=E.val;
  }
  return *this;
}

bool Etat::estVoisine(const Etat & piece) const
{
	/*
	if (piece.x == (x - 1) || piece.x == (x + 1) || piece.x == x) {
		if (piece.y == (y - 1) || piece.y == (y + 1) || piece.y == y) {
			if (piece.x != x || piece.y != y) {
				return true;
			}
		}
	}
	*/

	if (x == piece.x &&
		(y == piece.y - 1 || y == piece.y + 1))
		return true;
	else if (y == piece.y &&
		(x == piece.x - 1 || x == piece.x + 1))
		return true;

	return false;
}

bool Etat::isPlayable(const VAL& value) const
{
  if (value == NOIR){
	 return (val == VIDE || val == KOWHITE);
 }
  else
  {
    return (val == VIDE || val == KOBLACK);
  }
}

bool Etat::isAStone() const
{
	return val != VIDE && val != KOWHITE && val != KOBLACK;
	//return val == BLANC || val == NOIR;
}

bool Etat::isAStone(const VAL & value) const
{
	return val == value;
}

std::ostream & Etat::coord(std::ostream & os) const
{
	os << "(" << x << "," << y << ")";

	return os;
}

//OVERLOADINGS functions

std::ostream& operator<<(std::ostream& os, const Etat& E){
  os <<
	  (E.getVal() == Etat::BLANC ? "Blanc " : "Noir ") <<
	  "(" << E.getX() << "," << E.getY() << ")";

  return os;
}
