#include "Condition.hpp"
#include "Sequencer.hpp"

Condition::Condition(Sequencer& seq) : S(seq)
{
	S.addCondition(this);
}


// bool getConditionState() {
// 	checkCondition();
// 	return conditionState;
// };

bool Condition::operator()()
{
	return check();
}


bool Condition::check()
{
	validate();
	
	return conditionState;
}


