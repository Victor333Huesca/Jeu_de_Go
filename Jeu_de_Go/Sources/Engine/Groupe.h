#pragma once
#include <vector>
#include "Etat.h"

class Groupe : public std::vector<Etat>
{
public:
	Groupe();
	Groupe(const Etat& state);
	~Groupe();
};

// Overload streams
std::ostream& operator<<(std::ostream&, const Groupe&);
