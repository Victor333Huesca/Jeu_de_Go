#include <iostream>

class Etat
{
public :
	enum VAL {
		VIDE,
		NOIR,
		BLANC,
		KOWHITE,
		KOBLACK,
		NJ
	};

	//CONSTRUCTORS
	Etat();//default constructor
	Etat(size_t, size_t, VAL);//parametric constructor
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

	// Methodes
	bool estVoisine(const Etat& piece) const;
	bool isPlayable(const VAL& value) const;
	bool isAStone() const;
	bool isAStone(const VAL& value) const;
	std::ostream& coord(std::ostream& os) const;

private:
  size_t x;
  size_t y;
  VAL val;
};

  //overloadings functions
std::ostream& operator<<(std::ostream&, const Etat&);
