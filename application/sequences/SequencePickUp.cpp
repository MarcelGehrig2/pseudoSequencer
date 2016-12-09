#include "SequencePickUp.hpp"
SequencePickUp::SequencePickUp(Sequencer &S, int callerID, std::string name = ""): Sequence(S, callerID, name)
{
// create sequences
// ////////////////////////////////////////////////////////////////////////////
	
	moveTo = new MoveTo(S, sequenceID, "moveSequence");
	moveTo.setTimeout(1.5);		//Timeout set for whole sequence
	gripper = new Gripper(S, sequenceID, "openGripper Sequence");
	//timeout is set before each step
	
	
	
	
// create conditions
// ////////////////////////////////////////////////////////////////////////////
	condMovementBlocked = new CondMovementBlocked(S);
	
	
// add implicit conditions
// ...

};



// moveTo();
SequencePickUp::action()
{
	moveTo(10, 15);	//TODO waypoints
	gripper.setTimeout(1.0);
	gripper(1, "open");
	moveTo(12, 12);	//abovePackage
	moveTo(10, 12);	//grippingPosition
	gripper.setTimeout(1.5);
	
	gripper(1, "close");
	
	if ( S.getCS().packageAvailable()==false ) {
		this->runningState="restarting";
	}
	//TODO check packet available = Condition???
	//	No 	-> restart sequence	TODO restart 
	//	Yes -> continue
	
	
	moveTo(12, 12);	//abovePackage
	
	//status = finished; TODO Status
	
	
	
	
};


