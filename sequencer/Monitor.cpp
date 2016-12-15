#include "Monitor.hpp"
#include "Sequence.hpp"
#include "SequencerException.hpp"



Monitor::Monitor(Sequence* owner, Condition* condition, Monitor::behaviorEnum behavior)
: Monitor(owner, condition, behavior, NULL)	{ }

Monitor::Monitor(Sequence* owner, Condition* condition, Monitor::behaviorEnum behavior, Sequence* exceptionSequence)
: Monitor(owner, condition, behavior, exceptionSequence, "") { }

Monitor::Monitor(Sequence* owner, Condition* condition, Monitor::behaviorEnum behavior, Sequence* exceptionSequence, std::__cxx11::string goToTarget)
: owner(owner), condition((condition), behavior), exceptionSequence(exceptionSequence), goToTarget(goToTarget)
{

}


bool Monitor::check(Sequence* caller)	//caller is the sequence, which
{
	if( condition->isTrue() ) {
		
		//TODO n-times repetition watch
		Sequence::runningStateEnum currentRunningState = caller->getRunningState();
		
		caller->getSequencerException()->throwException(caller, owner, behavior, exceptionDescription);		
		startExceptionSequence();
		
		if ( currentRunningState != caller->getRunningState() ) return true;
		else return false;
	}
	else return false;
}

void Monitor::startExceptionSequence()
{
	exceptionSequence->start();
	//TODO start sequence
	//TODO function parameter of sequence?
}


void Monitor::setBehavior(Monitor::behaviorEnum behavior)
{
	this->behavior = behavior;
}

void Monitor::setExceptionSequence(Sequence* exceptionSequence)
{
	this->exceptionSequence = exceptionSequence;
}

void Monitor::setGotToTarget(std::__cxx11::string goToTarget)
{
	this->goToTarget = goToTarget;
}
