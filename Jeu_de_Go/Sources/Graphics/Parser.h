#pragma once
#include "Globals.h"
#include <fstream>


class Parser
{
public:
	Parser();
	~Parser();


private:
	// Return 0 if worked, 1 if file cannot be open, 2 for other errors
	int goIntoSgf(const std::string& src_name, const std::string& out_name) const;
};
