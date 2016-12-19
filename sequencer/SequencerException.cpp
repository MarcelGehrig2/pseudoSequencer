#include "SequencerException.hpp"
#include "Sequence.hpp"
#include <string>


SequencerException::SequencerException()
: exceptionCounter(0), exceptionInARowCounter(0)
{

}

void SequencerException::throwException(SequenceBase* invoking, SequenceBase* owner, behaviorEnum setBehavior, std::string descriptionOfException="")
{
	exception = true;
	exceptionCounter++;
	
	previousRootSequence = invokingSequence;
	previousOwnerSequence = ownerSequence;
	previousExceptionDescription = exceptionDescription;
	invokingSequence = invoking;
	ownerSequence = owner;
	callerOfOwnerSequence = ownerSequence->getCallerSequence();
	behavior = setBehavior;
	
	//create default name if empty:
	if ( descriptionOfException == "" ) exceptionDescription = "Exception from: " + ownerSequence->getName();
	else exceptionDescription = descriptionOfException;
	
	//check if same exception got thrown multiple times:
	if (   ( previousRootSequence			== invokingSequence)
		&& ( previousOwnerSequence			== ownerSequence) 
		&& ( previousExceptionDescription	== exceptionDescription ) ) 
	{
		exceptionInARowCounter++;
	} else exceptionInARowCounter = 1;
	
	
	invokingSequenceRunningState = ownerSequenceRunningState = callerOfOwnerSequenceRunningState = SequenceBase::notSet;
	switch( behavior ) {
		case SequencerException::repeteOwnerSequence :
			invokingSequenceRunningState = SequenceBase::aborting;			//sequence of following lines does matter
			ownerSequenceRunningState = SequenceBase::restarting;		//invoking and owner can be the same
			break;
		case SequencerException::repeteCallerOfOwnerSequence :
			if( !callerOfOwnerSequence ) {	//owner seqence is allready lowest sequence (mainSequence)
				//TODO error
			}
			else {
				invokingSequenceRunningState = SequenceBase::aborting;
				callerOfOwnerSequenceRunningState = SequenceBase::restarting;
			}
			break;
		case SequencerException::repeteStep :
			invokingSequenceRunningState = SequenceBase::restartingStep;
			break;
			
		//TODO implemente remaining cases 
			
		default:
			//TODO Error
		break;
	}
	
	setAllRelevantRunningStates();
}

void SequencerException::setAllRelevantRunningStates()
{
			setRunningStateOfThisSequence( invokingSequence );
			setRunningStateOfThisSequence( ownerSequence );
			setRunningStateOfThisSequence( callerOfOwnerSequence );
}

void SequencerException::setRunningStateOfThisSequence(SequenceBase* sequence)
{
	if ( this->isSet() ) {
		
		switch( sequence ) {
			case invokingSequence :
				if( invokingSequenceRunningState != SequenceBase::notSet )
					sequence->setRunningState(invokingSequenceRunningState);
				break;
			case ownerSequence :
				if( ownerSequenceRunningState != SequenceBase::notSet )
					sequence->setRunningState(ownerSequenceRunningState);
				break;				
			case callerOfOwnerSequence :
				if( callerOfOwnerSequenceRunningState != SequenceBase::notSet )
					sequence->setRunningState(callerOfOwnerSequenceRunningState);
				break;
			default :
					sequence->setRunningState(SequenceBase::aborting);
				break;
		}
				
	}
}

void SequencerException::clearException()	//TODO ?
{
	exception = false;
	invokingSequenceRunningState = SequenceBase::notSet;
	ownerSequenceRunningState = SequenceBase::notSet;
	callerOfOwnerSequenceRunningState = SequenceBase::notSet;
}

bool SequencerException::isSet() const
{
	return exception;
}

SequenceBase* SequencerException::getRootSequence() const
{
	return invokingSequence;
}

SequenceBase* SequencerException::getOwnerSequence() const
{
	return ownerSequence;
}

std::__cxx11::string SequencerException::getExceptionDescription()  const
{
	return exceptionDescription;
}
