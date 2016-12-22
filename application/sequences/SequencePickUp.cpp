#include "SequencePickUp.hpp"
#include "../../control/steps/MoveTo.hpp"
#include "../../control/steps/Gripper.hpp"

SequencePickUp::SequencePickUp(Sequencer& S, Sequence* caller, std::string name = "")
: Sequence(S, caller, name)
{
	
	// create sequences
	// ////////////////////////////////////////////////////////////////////////
// no other sequences needed
	
	//TODO TODO TODO monitor packet lost
	
	// create conditions
	// ////////////////////////////////////////////////////////////////////////
// 	condMovementBlocked = new CondMovementBlocked(S);	inherited from caller
	
	
// add implicit conditions
// ...

};



// moveTo();
bool SequencePickUp::action()
{
// create steps
// ////////////////////////////////////////////////////////////////////////////
	MoveTo moveTo;
	moveTo.setTimeoutTime(1.5);		//Timeout set for whole sequence	
	Gripper gripper;
	//timeout is set before each step
	
	
	
// Sequence
// ////////////////////////////////////////////////////////////////////////////
	moveTo(10, 15);	//TODO waypoints
	gripper.setTimeoutTime(1.0);
	gripper(1, Gripper::open);
	moveTo(12, 12);	//abovePackage
	moveTo(10, 12);	//grippingPosition
	
	gripper.setTimeoutTime(1.5);
	gripper(1, close);
	
	if ( S.getCS().packageAvailable()==false ) {
		this->runningState="restarting";
	}
	//TODO check packet available = Condition???
	//	No 	-> restart sequence	TODO restart 
	//	Yes -> continue
	
	
	moveTo(12, 12);	//abovePackage
	
	//status = finished; TODO Status
	
	
	
	
};


