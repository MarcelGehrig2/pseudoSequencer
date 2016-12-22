#include "Step.hpp"

Step::Step(Sequencer& S, BaseSequence* caller)
: BaseSequence(S, caller)
{
	setID(-99);		//all steps have the ID -99
}



bool Step::isStep() const
{
	return true;
}
