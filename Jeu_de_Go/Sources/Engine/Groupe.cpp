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

std::ostream & operator<<(std::ostream & stream, const Groupe & grp)
{
	for (size_t i = 0; i < grp.size() - 1; i++)
	{
		std::cout << grp[i] << ", ";
	}
	std::cout << grp[grp.size() - 1] << std::endl;

	return stream;
}
