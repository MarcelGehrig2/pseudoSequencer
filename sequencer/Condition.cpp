#include "Condition.hpp"


// bool getConditionState() {
// 	checkCondition();
// 	return conditionState;
// };

bool Condition::check()
{
	validate();
	return conditionState;
}


