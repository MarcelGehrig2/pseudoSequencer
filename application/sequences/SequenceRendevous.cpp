#include "SequenceRendevous.hpp"
#include "SequencePickUp.hpp"

SequenceRendevous::SequenceRendevous(Sequencer& S, Sequence* caller, std::__cxx11::string name)
: Sequence(S, caller, name)
{
	
	// create sequences
	// ////////////////////////////////////////////////////////////////////////
	pickUp = new SequencePickUp(S, this, "pickUp Sequence");
	pickUp->setTimeout(5);
	//TODO:
// 	SequenceBringToRendezvous* bringToRendezvous = new bringToRendezvous(S, this, "bringToRendezvous Sequence");
	bringToRendezvous = new BringToRendezvous(S, this, "bringToRendezvous Sequence");
	bringToRendezvous->setTimeout(1);
	//TODO: waitFor instruction
	waitForSecondGripper = new WaitForSecondGripper(S, this, "waitForSecondGripper Sequence");
	waitForSecondGripper->setTimeout(7);
// 	SequenceWaitForSecondGripper waitForSecondGripper();

	// create conditions
	// ////////////////////////////////////////////////////////////////////////
	// TODO
	

	// create monitors
	// ////////////////////////////////////////////////////////////////////////
	monitorMovementBlocked = Monitor(this, condMovementBlocked, Monitor::abortOwnerSequence);
	this->addMonitor( &monitorMovementBlocked );
}


bool SequenceRendevous::action()
{
	// create steps
	// ////////////////////////////////////////////////////////////////////////////
	Gripper gripper;
	gripper.setTimeout(1);

	
	// run seqence
	// ////////////////////////////////////////////////////////////////////////////

	pickUp->runBlocking();

	if ( pickUp->getState() == "movement Blocked" ) ; 	//TODO SequenceA->runBlocking()
	else if ( pickUp->getState() == "package lost" ) ;	//TODO SequenceB->runBlocking()
	else //TODO SequenceC->runBlocking()
	
	bringToRendezvous->runBlocking();
	
	setState("ready");
	
	//TODO waitFor
// 	waitFor( S.getSeqenceByName("conveyorSequence")->getState() == "ready", 7 );
	waitForSecondGripper->runBlocking();
	
	gripper(1, Gripper::open);
	
	setState("open");

	if (this.stop = false) restartSequence();

}