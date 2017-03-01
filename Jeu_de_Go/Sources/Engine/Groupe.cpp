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
	int i = 0;
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

	// So it's obviously not include
	return false;
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
