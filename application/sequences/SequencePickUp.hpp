#include "../../sequencer/Sequence.hpp"
#include "../../control/elementarySequences/MoveTo.hpp"
#include "../../control/elementarySequences/Gripper.hpp"
#include "../../control/conditions/CondMovementBlocked.hpp"

class SequencePickUp : public Sequence {
public:
	SequencePickUp();
	

	//Sequences
	MoveTo moveTo;
	Gripper gripper;
	
	
	//Conditions
	CondMovementBlocked condMovementBlocked;

	
	
private:	
	
};



