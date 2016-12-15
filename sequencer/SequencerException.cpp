#include "SequencerException.hpp"
#include "Sequence.hpp"
#include <string>


SequencerException::SequencerException()
: exceptionCounter(0), exceptionInARowCounter(0)
{

}

void SequencerException::throwException(Sequence* invoking, Sequence* owner, behaviorEnum setBehavior, std::string descriptionOfException="")
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
	
	
	invokingSequenceRunningState = ownerSequenceRunningState = callerOfOwnerSequenceRunningState = Sequence::notSet;
	switch( behavior ) {
		case SequencerException::repeteOwnerSequence :
			invokingSequenceRunningState = Sequence::aborting;			//sequence of following lines does matter
			ownerSequenceRunningState = Sequence::restarting;		//invoking and owner can be the same
			break;
		case SequencerException::repeteCallerOfOwnerSequence :
			if( !callerOfOwnerSequence ) {	//owner seqence is allready lowest sequence (mainSequence)
				//TODO error
			}
			else {
				invokingSequenceRunningState = Sequence::aborting;
				callerOfOwnerSequenceRunningState = Sequence::restarting;
			}
			break;
		case SequencerException::repeteStep :
			invokingSequenceRunningState = Sequence::restartingStep;
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

void SequencerException::setRunningStateOfThisSequence(Sequence* sequence)
{
	if ( this->isSet() ) {
		
		switch( sequence ) {
			case invokingSequence :
				if( invokingSequenceRunningState != Sequence::notSet )
					sequence->setRunningState(invokingSequenceRunningState);
				break;
			case ownerSequence :
				if( ownerSequenceRunningState != Sequence::notSet )
					sequence->setRunningState(ownerSequenceRunningState);
				break;				
			case callerOfOwnerSequence :
				if( callerOfOwnerSequenceRunningState != Sequence::notSet )
					sequence->setRunningState(callerOfOwnerSequenceRunningState);
				break;
			default :
					sequence->setRunningState(Sequence::aborting);
				break;
		}
				
	}
}

void SequencerException::clearException()	//TODO ?
{
	exception = false;
}

bool SequencerException::isSet() const
{
	return exception;
}

Sequence* SequencerException::getRootSequence() const
{
	return invokingSequence;
}

Sequence* SequencerException::getOwnerSequence() const
{
	return ownerSequence;
}

std::__cxx11::string SequencerException::getExceptionDescription()  const
{
	return exceptionDescription;
}
