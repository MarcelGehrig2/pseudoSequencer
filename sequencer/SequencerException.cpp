#include "SequencerException.hpp"


void SequencerError::throwException(Sequence* caller)
{
	std::string errorDescription;
	errorDescription = "Error from: " + caller->getName();
	throwError(caller, errorDescription);
}

void SequencerError::throwException(Sequence* caller, std::__cxx11::string errorDescription)
{
	error = true;
	
	if ( (this->rootSequence == caller)  && (this->errorDescription == errorDescription) ) {
		errorInARowCounter++;
	} else {
		errorInARowCounter = 1;
	}
	
	rootSequence = caller;
	this->errorDescription = errorDescription;
	errorCounter++;
}


void SequencerError::clearException()
{
	error = false;
}

bool SequencerError::isSet()
{
	return error;
}

Sequence* SequencerError::getRootSequence()
{
	return rootSequence;
}

std::__cxx11::string SequencerError::getExceptionDescription()
{
	return errorDescription;
}
