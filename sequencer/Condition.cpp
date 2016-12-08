#include "Condition.hpp"

Condition::Condition(Sequencer& seq) : S(seq)
{

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


