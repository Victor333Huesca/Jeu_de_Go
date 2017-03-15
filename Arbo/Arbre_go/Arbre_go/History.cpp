#include "History.h"



History::History() :
	_current(begin())
{
}

History::~History()
{
}

const Etat& History::current() const
{
	return *_current;
}

const Etat& History::previous()
{
	if (_current == begin()) 
		return *_current;
	else 
		return *--_current;
}

const Etat& History::next()
{
	if (_current == --end())
		return *_current;
	else
		return *++_current;
}

void History::add(const Etat &new_state)
{
	if (!empty())
	{
		// erase everything past current state
		erase(++_current, end());
	}

	push_back(new_state);

	// after add(), current_state is last in the history
	_current = --end();
}

bool History::cancel()
{
	if (!empty() && _current != begin())
	{
		--_current;

		return true;
	}
	else if (_current == begin())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void History::clear()
{
	clear(); 
	_current = begin();
}

std::ostream & History::display(std::ostream &stream) const
{
	// Start
	stream << "{";

	// Display all member exepted the last
	for (auto it = begin(); it != _current; it++)
	{
		stream << *it << ", ";
	}

	// Display the last member
	stream << *_current;

	// End
	stream << "}";

	return stream;
}

std::ostream & operator<<(std::ostream & stream, const History& hist)
{
	return hist.display(stream);
}
