#include "Condition.hpp"
#include "Sequencer.hpp"

Condition::Condition(Sequencer& seq)
: Condition(seq, polling) { }

Condition::Condition(Sequencer& seq, Condition::validateStyleEnum validateStyle)
: S(seq), validateStyle(validateStyle)
{
	//TODO validateStyle == periodic
}

bool Condition::isTrue()
{
	if ( validateStyle == polling ) {
		validate();
		return conditionState;
	}
	else if ( validateStyle == periodic )
		return conditionState;
	else {
		//TODO Throw EEROS Error
	}
}




// Condition::Condition(Sequencer& seq, Condition::validateStyleEnum)
// : S(seq),
// {
// 
// }

// Condition::Condition(Sequencer& seq) : S(seq)
// {
// 	S.addCondition(this);
// }


// bool getConditionState() {
// 	checkCondition();
// 	return conditionState;
// };

// bool Condition::operator()()
// {
// 	return check();
// }


// bool Condition::check()
// {
// 	validate();
// 	
// 	return conditionState;
// }
// 

