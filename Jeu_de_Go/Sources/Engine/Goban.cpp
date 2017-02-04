#include "Goban.h"


//CONSTRUCTORS
Goban::Goban(){
  array= new Etat[TGOBAN*TGOBAN];
  size_t i=0;
  for (size_t y=0;y<TGOBAN; y++){
    for (size_t x=0;x<TGOBAN; x++){
      array[i].setX(x);
      array[i].setY(y);
      array[i].setVal(Etat::VIDE);
      i++;
    }
  }
}

//overloadings methodes

Etat& Goban::operator[](const size_t i)const{
  return array[i];
}

//METHODES

Etat& Goban::coord(const int X,const int Y){//access to element of array with (x,y)
  size_t i = TGOBAN * Y + X;
  return array[i];
}

const Etat & Goban::coord(const int x, const int y) const
{
	return array[TGOBAN * y + x];
}

bool Goban::isMoveLegal(const int& x, const int& y) const
{
	return coord(x, y).isPlayable();
}

void Goban::afficheGroupes(const Etat::VAL & val) const
{
	if (val == Etat::BLANC)
	{
		std::cout << "Groupes blancs : ";
		for (size_t i = 0; i < groups_white.size(); i++)
		{
			std::cout  << groups_white[i] << "   ";
		}
	}
	else if (val == Etat::NOIR)
	{
		std::cout << "Groupes noirs : ";
		for (size_t i = 0; i < groups_black.size(); i++)
		{
			std::cout << groups_black[i] << "   ";
		}
	}
	else
	{
		std::cerr << "Error : mauvais groupe demmandé !\n";
	}
}

void Goban::afficheGroupes() const
{
	afficheGroupes(Etat::BLANC);
	std::cout << std::endl;
	afficheGroupes(Etat::NOIR);
	std::cout << std::endl;
}

void Goban::rechercheGroupes(const bool& verbose)
{
	// Browse every goban's intersection
	for (size_t i = 0; i < (TGOBAN * TGOBAN); i++)
	{
		// If the current intersection is a stone
		if (array[i].isAStone())
		{
			if (verbose)	std::cout << "Square " << i << " : stone ";

			// If it's a black stone
			if (array[i].isAStone(Etat::NOIR))
			{
				if (verbose)	std::cout << "black found.\n";

				// There is at least one black groups so start searching a neighboor-group
				size_t j = 0;
				while (j < groups_black.size())
				{
					if (verbose)	std::cout << "   Looking in the group " << j;
					// Look if the stone isn't already inside the group
					if (!groups_black[j].contain(array[i]))
					{
						if (verbose)	std::cout << " which not contain already that stone ";
						// So look if it should
						if (groups_black[j].shouldContain(array[i]))
						{
							if (verbose)	std::cout << " but which should, son include it.\n";
							groups_black[j].push_back(array[i]);
							j = groups_white.size() + 1;
						}
						else if (verbose)	std::cout << "because the stone is in an other group.\n";
					}
					else
					{
						j = groups_black.size() + 1;
						if (verbose)	std::cout << " which contain already the stone.\n";
					}
					j++;
				}
				// If no group has been found
				if (j == groups_black.size())
				{
					// Create a first group which contain only the current stone
					groups_black.push_back(Groupe(array[i]));
					if (verbose)	std::cout << "   No group found, a new black group has been created.\n";
				}
			}
			else // array[i].isAStone(Etat::BLANC)
			{
				if (verbose)	std::cout << "white found.\n";

				// There is at least one black groups so start searching a neighboor-group
				size_t j = 0;
				while (j < groups_white.size())
				{
					if (verbose)	std::cout << "   Looking in the group " << j;
					// Look if the stone isn't already inside the group
					if (!groups_white[j].contain(array[i]))
					{
						if (verbose)	std::cout << " which not contain already that stone ";
						// So look if it should
						if (groups_white[j].shouldContain(array[i]))
						{
							if (verbose)	std::cout << " but which should, son include it.\n";
							groups_white[j].push_back(array[i]);
							j = groups_white.size() + 1;
						}
						else if (verbose)	std::cout << "because the stone is in an other group.\n";
					}
					else
					{
						j = groups_white.size() + 1;
						if (verbose)	std::cout << " which contain already the stone.\n";
					}
					j++;
				}
				// If no group has been found
				if (j == groups_white.size())
				{
					// Create a first group which contain only the current stone
					groups_white.push_back(Groupe(array[i]));
					if (verbose)	std::cout << "   No group found, a new white group has been created.\n";
				}
			}
			if (verbose)	std::cout << "\n";
		}
	}
}

bool Goban::move(const Etat::VAL& value, const int& x, const int& y)
{
	if (isMoveLegal(x, y))
	{
		coord(x, y).setVal(value);
		return true;
	}

	return false;
}

//overloadings functions
std::ostream& operator<<(std::ostream& os, const Goban& goban)
{
	size_t i=0;
	for (size_t y=0;y<TGOBAN; y++){
		for (size_t x=0;x<TGOBAN; x++){
			os << goban[i].getVal() << " ";
			i++;
		}
		os << std::endl;
	}

	return os;
}
