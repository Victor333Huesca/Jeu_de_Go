#ifndef Etat_H
#define Etat_H
#include <iostream>

using namespace std;

enum VAL {
 VIDE,
 NOIR,
 BLANC,
 KO
};

class Etat{
private:
  size_t x;
  size_t y;
  VAL val;

public:
  //CONSTRUCTORS
  Etat();//default constructor
  Etat(size_t,size_t,VAL);//parametric constructor
  Etat(const Etat&);//copy constructor

  //GETTERS
  size_t getX() const;
  size_t getY() const;
  VAL getVal() const;

  //SETTERS
  void setX(size_t);
  void setY(size_t);
  void setVal(VAL);

  //OVERLOADINGS METHODES
  bool operator==(const Etat&) const;
  bool operator!=(const Etat&) const;
  Etat operator=(const Etat&);
};

  //overloadings functions
ostream& operator<<(ostream&, const Etat&);
#endif
