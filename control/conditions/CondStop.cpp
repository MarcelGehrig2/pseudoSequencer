#include "CondStop.hpp"


void CondStop::validate()
{
	conditionState = S.getCS().stopButton().getSignal();
	S.getCS().stopButton().reset();
}
