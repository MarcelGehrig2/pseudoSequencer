#include "SequencerException.hpp"
#include "Sequence.hpp"
#include <string>


SequencerException::SequencerException()
: exceptionCounter(0), exceptionInARowCounter(0)
{

}

void SequencerException::throwException(Sequence* root, Sequence* owner, behaviorEnum setBehavior, std::string descriptionOfException="")
{
	exception = true;
	exceptionCounter++;
	
	previousRootSequence = rootSequence;
	previousOwnerSequence = ownerSequence;
	previousExceptionDescription = exceptionDescription;
	rootSequence = root;
	ownerSequence = owner;
	behavior = setBehavior;
	
	if ( descriptionOfException == "" ) exceptionDescription = "Exception from: " + ownerSequence->getName();
	else exceptionDescription = descriptionOfException;
	
	if (   ( previousRootSequence			== rootSequence)
		&& ( previousOwnerSequence			== ownerSequence) 
		&& ( previousExceptionDescription	== exceptionDescription ) ) 
	{
		exceptionInARowCounter++;
	} else exceptionInARowCounter = 1;
	
	
	switch( behavior ) {
		case SequencerException::repeteOwnerSequence :
			rootSequence->setRunningState(Sequence::aborting);
			ownerSequence->setRunningState(Sequence::restarting);
			break;
		case SequencerException::repeteCallerOfOwnerSequence :
			if( !ownerSequence->getCallerSequence() ) {	//owner seqence is allready lowest sequence (mainSequence)
				//TODO error
			}
			else {
				rootSequence->setRunningState(Sequence::aborting);
				ownerSequence->getCallerSequence()->setRunningState(Sequence::restarting);					
			}
			break;
		case SequencerException::repeteStep :
			rootSequence->setRunningState(Sequence::restartingStep);
			break;
			
		//TODO implemente remaining cases 
			
		default:
			//TODO Error
		break;
	}
}


void SequencerException::clearException()
{
	exception = false;
}

bool SequencerException::isSet() const
{
	return exception;
}

Sequence* SequencerException::getRootSequence() const
{
	return rootSequence;
}

std::__cxx11::string SequencerException::getExceptionDescription()  const
{
	return exceptionDescription;
}
