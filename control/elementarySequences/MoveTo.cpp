#include "MoveTo.hpp"

MoveTo::MoveTo(Sequencer &S, int callerID, std::string name = "") : Sequence(S, callerID, name) {
	
}


int MoveTo::operator()(int posX, int posY)
{
	nextWaypoint << posX, posY;		//TODO check syntax
	Sequence.run();
}


MoveTo::action() {
	auto cs = s.getCS();
	cs.nextWaypointBlock.setValue(nextWaypoint);		//Sequencer block (similar to constant)
}

void MoveTo::setStopCondition()
{
	//TODO
}
