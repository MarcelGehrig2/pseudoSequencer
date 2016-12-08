#include "CondMovementBlocked.hpp"

// CondMovementBlocked::CondMovementBlocked() 
// {
// 	//TODO is base constructor executed
// }

void CondMovementBlocked::validate()
{
	conditionState = S.getCS().movementIsBlocked().getSignal(); //block in CS checks, if movement is blocked
}
