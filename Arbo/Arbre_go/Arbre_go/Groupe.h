#pragma once
#include <vector>
#include "Etat.h"

class Groupe : public std::vector<Etat>
{
public:
	Groupe();
	Groupe(const Etat& state);
	~Groupe();

	bool shouldContain(const Etat& stone) const;
	bool contain(const Etat& stone) const;

	bool voisin(const Groupe& group) const;
	void fusion(const Groupe& group);
};

// Overload streams
std::ostream& operator<<(std::ostream&, const Groupe&);
