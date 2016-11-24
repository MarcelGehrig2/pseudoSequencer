#include "sequenceRendevous.hpp"

//TODO call base consturctor and define derived constructor

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