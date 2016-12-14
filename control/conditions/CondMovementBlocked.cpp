#include "CondMovementBlocked.hpp"

//Base Constructor is used

void CondMovementBlocked::validate()
{
	conditionState = S.getCS().movementIsBlocked().getSignal(); //block in CS checks, if movement is blocked
}
