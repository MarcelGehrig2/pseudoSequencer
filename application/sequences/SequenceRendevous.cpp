#include "SequenceRendevous.hpp"

SequenceRendevous::SequenceRendevous(Sequencer& S, Sequence* caller, std::__cxx11::string name)
: Sequence(S, caller, name)
{

// create steps
// ////////////////////////////////////////////////////////////////////////////
	gripper = new Gripper(S, this, "openGripper Sequence");
	
// create sequences
// ////////////////////////////////////////////////////////////////////////////
	pickUp = new SequencePickUp(S, this, "openGripper Sequence");
	
		SequencePickUp pickUp;
	SequenceBringToRendezvous bringToRendezvous;

// create conditions
// ////////////////////////////////////////////////////////////////////////////
	
	
}


// create sequences
// ////////////////////////////////////////////////////////////////////////////

sequencePickUp pickUp("pickUp0");
sequenceBringToRendezvous bringToRendezvous();
sequenceWaitForSecondGripper waitForSecondGripper();

 
// run seqence
// ////////////////////////////////////////////////////////////////////////////

int pickUpReturnValue = pickUp.run();		//blocking call
//??? will object be automatically deleted after call?

//pickUpReturnValue decision

int bringToRendezvousReturnValue = bringToRendezvous.run();

setState("ready");
	
int waitForSecondGripperReturnValue waitForSecondGripper.run();		//blocking call
//??? seqenceSecondGrippe is not started in this Object, how do they communicate?

int openGripperReturnValue openGripper.run();
setState("open");

if (this.stop = true) break;