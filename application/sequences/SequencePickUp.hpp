#include "../../sequencer/Sequence.hpp"
#include "../../control/conditions/CondMovementBlocked.hpp"

class SequencePickUp : public Sequence {
public:
	SequencePickUp(Sequencer& S, Sequence* caller, std::string name = "");
	
	bool action();
	
	
	//Conditions
	// ////////////////////////////////////////////////////////////////////////
	CondMovementBlocked* condMovementBlocked;

	
	
private:	
	
};



