#include "Gripper.hpp"

int Gripper::operator()(int gripperID, gripperStateEnum action)
{
	setParameter(gripperID, action);	
	return Step::start();		//Has to be implemented by the control developer !!
}

void Gripper::setParameter(int gripperID, gripperStateEnum action)
{

	this->gripperID = gripperID;
	this->action = action;
	
	Step::setIsBlocking();		//TODO necessary?
}


bool Gripper::action()
{
	if ( (gripperID == 0) && (action = open) ) {
		S.getCS().gripperA.open();
	}
	
	if ( (gripperID == 0) && (action = close) ) {
		S.getCS().gripperA.close();
	}
	
	if ( (gripperID == 1) && (action = open) ) {
		S.getCS().gripperB.open();
	}
	
	if ( (gripperID == 1) && (action = close) ) {
		S.getCS().gripperB.close();
	}

}


bool Gripper::stopCondition()
{
	if (gripperID == 0) {
		return S.getCS().gripperA.isOpen();
	} 
	else if (gripperID == 1) {
		return S.getCS().gripperA.isOpen();
	}
	else {
		//TODO ERROR -> Stop App
	}
}
