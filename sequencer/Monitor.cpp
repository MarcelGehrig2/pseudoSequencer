#include "Monitor.hpp"
#include "Sequence.hpp"
#include "SequencerException.hpp"



Monitor::Monitor(SequenceBase* owner, Condition* condition, Behavior::enumerator behavior)
: Monitor(owner, condition, behavior, NULL)	{ }

Monitor::Monitor(SequenceBase* owner, Condition* condition, Behavior::enumerator behavior, SequenceBase* exceptionSequence)
: Monitor(owner, condition, behavior, exceptionSequence, "") { }

Monitor::Monitor(SequenceBase* owner, Condition* condition, Behavior::enumerator behavior, SequenceBase* exceptionSequence, std::__cxx11::string goToTarget)
: owner(owner), condition((condition), behavior), exceptionSequence(exceptionSequence), goToTarget(goToTarget)
{

}


bool Monitor::check(SequenceBase* caller)	//caller is the sequence, which
{
	if( condition->isTrue() ) {
		
		//TODO n-times repetition watch
		SequenceBase::runningStateEnum currentRunningState = caller->getRunningState();
		
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


void Monitor::setBehavior(Behavior::enumerator behavior)
{
	this->behavior = behavior;
}

void Monitor::setExceptionSequence(SequenceBase* exceptionSequence)
{
	this->exceptionSequence = exceptionSequence;
}

void Monitor::setGotToTarget(std::__cxx11::string goToTarget)
{
	this->goToTarget = goToTarget;
}
