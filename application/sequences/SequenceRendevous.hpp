#include "../../sequencer/Sequence.hpp"
#include "../../control/steps/MoveTo.hpp"
#include "../../control/steps/Gripper.hpp"
#include "../../control/conditions/CondMovementBlocked.hpp"
#include "SequencePickUp.hpp"


class SequenceRendevous : public Sequence {
public:
	SequenceRendevous(Sequencer& S, Sequence* caller, std::string name = "");
// 	
	bool action();
	
	// Sequences
	// ////////////////////////////////////////////////////////////////////////
	SequencePickUp* pickUp;
	Sequence* bringToRendezvous;
	Sequence* waitForSecondGripper;
	
	// Conditions
	// ////////////////////////////////////////////////////////////////////////
	CondMovementBlocked* condMovementBlocked;
	
	
private:	
	
};