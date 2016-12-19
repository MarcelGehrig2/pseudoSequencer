#include "MoveToSafety.hpp"

MoveToSafety::MoveToSafety(Sequencer& S, SequenceBase* caller, std::string name = "")
: SequenceBase(S, caller, name)
{
// create sequences
// ////////////////////////////////////////////////////////////////////////////
	
	moveTo = new MoveTo(S, this, "moveSequence");	//TODO is created at leas twice. is that ok?

}


int MoveToSafety::operator()(int safetyPos)
{
	setParameter(safetyPos);
	return SequenceBase::start();		//Has to be implemented by the control developer !!
}


void MoveToSafety::setParameter(int safetyPos)
{
	this->safetyPos=safetyPos;
	
	SequenceBase::setIsBlocking();		//TODO necessary?
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
