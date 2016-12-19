#include "../../sequencer/Sequence.hpp"
#include "../../control/elementarySequences/MoveTo.hpp"
#include "../../control/elementarySequences/Gripper.hpp"
#include "../../control/conditions/CondMovementBlocked.hpp"
#include "SequencePickUp.hpp"


class SequenceRendevous : public Sequence {
public:
	SequenceRendevous(Sequencer& S, Sequence* caller, std::string name = "");
// 	
	
	
// 	//Steps
// 	MoveTo* moveTo;
	Gripper* gripper;
	
	//Sequences
	SequencePickUp pickUp;
	SequenceBringToRendezvous bringToRendezvous;
	
	//Conditions
	CondMovementBlocked* condMovementBlocked;
	
	
private:	
	
};