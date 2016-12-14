#include "MoveToSafety.hpp"

MoveToSafety::MoveToSafety(Sequencer& S, int callerID, std::__cxx11::string name)
: Sequence(S, callerID, name)
{
// create sequences
// ////////////////////////////////////////////////////////////////////////////
	
	moveTo = new MoveTo(S, sequenceID, "moveSequence");	//TODO is created at leas twice. is that ok?

}


int MoveToSafety::operator()(int safetyPos)
{
	setParameter(safetyPos);
	return Sequence::start();		//Has to be implemented by the control developer !!
}


void MoveToSafety::setParameter(int safetyPos)
{
	this->safetyPos=safetyPos;
	
	Sequence::setIsBlocking();		//TODO necessary?
// 	Sequence::setIsNonBlocking();
}


bool MoveToSafety::action()
{
	moveTo(10, 10);
	
	switch ( safetyPos ) {
		case 0 :
			moveTo(10, 15);
			break;
		case 1 :
			moveTo(10, 17);
			break;
		default :
			moveTo(10, 12);
			break;
	}
}

bool MoveToSafety::checkExitCondition()
{
	return true;
}
