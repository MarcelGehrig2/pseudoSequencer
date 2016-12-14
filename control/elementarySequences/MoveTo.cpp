#include "MoveTo.hpp"

MoveTo::MoveTo(Sequencer &S, int callerID, std::string name = "") : Sequence(S, callerID, name)
{
	
}


int MoveTo::operator()(int posX, int posY)
{
	setParameter(posX, posY);
	return Sequence::start();		//Has to be implemented by the control developer !!
}

void MoveTo::setParameter(int posX, int posY)
{
	nextWaypoint << posX, posY;		//TODO check syntax
	
	Sequence::setIsBlocking();		//TODO necessary?
// 	Sequence::setIsNonBlocking();
}



bool MoveTo::action() {
	auto cs = S.getCS();
	cs.nextWaypointBlock.setValue(nextWaypoint);		//Sequencer block (similar to constant)
}

bool MoveTo::checkExitCondition()
{
	auto cs = S.getCS();
	return cs.waypointReached();		//Sequencer block (similar to constant)
}
