#pragma once
#include "Globals.h"
#include "Etat.h"
#include <list>

class History : std::list<Etat>
{
public:
	/*!
	* @brief Default constructor
	*
	* Create empty history.
	*
	*/
	History();
	~History();


	/*!
	* @brief Access current position
	*
	* Invalid if history is empty.
	*
	* @return Current history state.
	*/
	const Etat& current() const;

	/*!
	* @brief Go backward in history
	*
	* Move one step backward in history. Do nothing if begining was reached.
	* Invalid if history is empty
	*
	* @return New history state.
	*/
	const Etat& previous();

	/*!
	* @brief Go forward in history
	*
	* Move one step forward in history. Do nothing if end was reached.
	* Invalid if history is empty
	*
	* @return New history state.
	*/
	const Etat& next();

	/*!
	* @brief Add new state in history
	*
	* Delete history past current state, add new state at the end.
	* After call, current state will be at the new end.
	*
	* @param new_state : state to add
	*/
	void add(const Etat &new_state);

	bool cancel();

	/*!
	* @brief Clear history
	*
	* Reset to the same state as after construction.
	*/
	void clear();

	/*!
	* @brief Display the history
	*
	* Display the history on a pasted stream.
	* 
	* @param stream : stream where display
	* 
	* @return The stream to chain display
	*/
	std::ostream& display(std::ostream& stream) const;


private:
	History::iterator _current;		/*!< Last move */
};

/*!
* @brief Display the history
*
* Display the history on a pasted stream.
*
* @param stream : stream where display
* @param hist : history to display
* 
* @return The stream to chain display
*/
std::ostream& operator<<(std::ostream& stream, const History& hist);