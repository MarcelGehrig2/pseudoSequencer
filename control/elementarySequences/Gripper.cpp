#include "Gripper.hpp"

int Gripper::operator()(int gripperID, std::__cxx11::string action)
{
	// always copy the code part below
	// ///////////////////////////////
	
	Sequence::setIsBlocking();
// 	Sequence::setIsNonBlocking();
	
	return Sequence::start();		//Has to be implemented by the control developer !!
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
