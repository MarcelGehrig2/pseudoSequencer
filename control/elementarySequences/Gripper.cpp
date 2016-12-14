#include "Gripper.hpp"

int Gripper::operator()(int gripperID, std::__cxx11::string action)
{
	setParameter(gripperID, action);	
	return Sequence::start();		//Has to be implemented by the control developer !!
}

void Gripper::setParameter(int gripperID, std::__cxx11::string action)
{

	this->gripperID = gripperID;
	this->action = action;
	
	Sequence::setIsBlocking();		//TODO necessary?
}


bool Gripper::action()
{
	if ( (gripperID == 0) && (action.compare("open")) ) {
		S.getCS().gripperA.open();
	}
	
	if ( (gripperID == 0) && (action.compare("close")) ) {
		S.getCS().gripperA.close();
	}
	
	if ( (gripperID == 1) && (action.compare("open")) ) {
		S.getCS().gripperB.open();
	}
	
	if ( (gripperID == 1) && (action.compare("close")) ) {
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
