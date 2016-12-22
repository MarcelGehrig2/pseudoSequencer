#include "TimeoutCondition.hpp"


TimeoutCondition::TimeoutCondition(Sequencer& seq, double timeInSec)
: Condition(seq, polling, 0), timeInSec(timeInSec)
{

}


bool TimeoutCondition::valdiate()
{
	auto now = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime) > timeInSec*1000) return true;
		else return false;
}


void TimeoutCondition::setTime(double timeInSec)
{
	this->timeInSec = timeInSec;
}

void TimeoutCondition::resetTimeout()
{
	started = true;
	startTime = std::chrono::steady_clock::now();
}
