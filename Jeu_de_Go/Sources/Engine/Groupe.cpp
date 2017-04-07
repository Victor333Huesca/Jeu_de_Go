#include "Groupe.h"

Groupe::Groupe()
{
}

Groupe::Groupe(const Etat & state)
{
	push_back(state);
}

Groupe::~Groupe()
{
}

bool Groupe::shouldContain(const Etat & stone) const
{
	size_t i = 0;
	while (i < size() && !stone.estVoisine(at(i)))
	{
		i++;
	}

	return i != size();
}

bool Groupe::contain(const Etat & stone) const
{
	// For each stone in the group
	for (size_t i = 0; i < size(); i++)
	{
		// If it is include
		if (at(i) == stone)
		{
			return true;
		}
	}

	// So it's not include
	return false;
}

bool Groupe::voisin(const Groupe& group) const{
	size_t i=0;
	while (i< group.size())
	{
		if(this->shouldContain(group[i]) )
			return true;

		i++;
	}
	return false;
}

void Groupe::fusion(const Groupe& group){
	Etat tmp;
	for(size_t i=0; i<group.size();i++){
		tmp=group[i];
		this->push_back(tmp);
	}
}

std::ostream & operator<<(std::ostream & stream, const Groupe & grp)
{
	// Start group
	stream << "{";

	// Display all member exepted the last
	for (size_t i = 0; i < grp.size() - 1; i++)
	{
		grp[i].coord(stream) << ", ";
	}

	// Display the last member if there is one
	if (grp.size() != 0)
		grp[grp.size() - 1].coord(stream);

	// End group
	stream << "}";

	return stream;
}
