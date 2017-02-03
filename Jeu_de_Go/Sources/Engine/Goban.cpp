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

bool Goban::isMoveLegal() const
{
	return true;
}

void Goban::afficheGroupes(const Etat::VAL & val, const int & n) const
{
	if (val == Etat::BLANC)
	{
		if (n < groups_white.size())
		{
			std::cout << groups_white[n];
		}
	}
	else if (val == Etat::NOIR)
	{
		if (n < groups_black.size())
		{
			std::cout << groups_black[n];
		}
	}
	else
	{
		std::cerr << "Error : mauvais groupe demmandé !\n";
	}
}

void Goban::afficheGroupes(const Etat::VAL & val) const
{
	if (val == Etat::BLANC)
	{
		std::cout << "Groupes blancs : \n";
		for (size_t i = 0; i < groups_white.size(); i++)
		{
			std::cout << groups_white[i];
		}
	}
	else if (val == Etat::NOIR)
	{
		std::cout << "Groupes noirs : \n";
		for (size_t i = 0; i < groups_black.size(); i++)
		{
			std::cout << groups_black[i];
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
	afficheGroupes(Etat::NOIR);
}

void Goban::rechercheGroupes()
{
	//DEFINE GROUPS IN THE CURRENT GOBAN
	Groupe tmpGroupe;

	//groups counter
	size_t k = 0;

	//stones counter
	size_t j = 0;

	//exit the loop if group found
	bool findGroup = false;

	// Browe every goban's intersection
	for (size_t i = 0; i < (TGOBAN * TGOBAN); i++)
	{
		// Look for a group
		findGroup = false;

		// If the current intersection is a stone
		if (array[i].getVal() != Etat::VIDE && array[i].getVal() != Etat::KO)
		{
			// If it's a black stone
			if (array[i].getVal() == Etat::NOIR)
			{
				// If there wasn't black groups
				if (groups_black.size() == 0)
				{
					// There's no black groups
					std::cout << "Le premier " << array[i] << std::endl;

					// Create a first group which contain only the current stone
					groups_black.push_back(Groupe(array[i]));
				}
				else
				{
					// There's black groups so start searching a neighboor-group
					while (k < groups_black.size() && !findGroup)
					{
						while (j < groups_black[k].size() && 
							!array[i].estVoisine(groups_black[k][j]))
						{
							j++;
						}
						if (j < groups_black[k].size())
						{
							// Insert stone in group
							groups_black[k].push_back(array[i]);
							findGroup = true;
						}
						j = 0;
						k++;
					}
					k = 0;
					if (!findGroup)
					{
						// Create new black group
						groups_black.push_back(array[i]);
					}
				}
			}
			else
			{
				// MEME CHOSE QUE POUR LES GROUPES NOIR

				// If there wasn't white groups
				if (groups_white.size() == 0)
				{
					// There's no white groups
					std::cout << "Le premier " << array[i] << std::endl;

					// Create a first group which contain only the current stone
					groups_white.push_back(Groupe(array[i]));
				}
				else
				{
					// There's white groups so start searching a neighboor-group
					while (k < groups_white.size() && !findGroup)
					{
						while (j < groups_white[k].size() &&
							!array[i].estVoisine(groups_white[k][j]))
						{
							j++;
						}
						if (j < groups_white[k].size())
						{
							// Insert stone in group
							groups_white[k].push_back(array[i]);
							findGroup = true;
						}
						j = 0;
						k++;
					}
					k = 0;
					if (!findGroup)
					{
						// Create new white group
						groups_white.push_back(array[i]);
					}
				}
			}
		}
	}
}

bool Goban::move(const Etat::VAL & value, const int & x, const int & y)
{
	if (isMoveLegal())
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
