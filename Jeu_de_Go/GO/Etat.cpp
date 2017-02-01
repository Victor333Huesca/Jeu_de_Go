#include <iostream>
#include "Etat.h"

using namespace std;

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

VAL Etat::getVal() const{
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

//OVERLOADINGS functions

ostream& operator<<(ostream& os, const Etat& E){
  os<<"{"<<E.getX()<<","<<E.getY()<<","<<E.getVal()<<"}";
  return os;
}
