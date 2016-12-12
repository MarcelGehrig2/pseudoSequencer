#include "SequencerException.hpp"


void SequencerError::throwError(Sequence* caller)
{
	std::string errorDescription;
	errorDescription = "Error from: " + caller->getName();
	throwError(caller, errorDescription);
}

void SequencerError::throwError(Sequence* caller, std::__cxx11::string errorDescription)
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


void SequencerError::clearError()
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

std::__cxx11::string SequencerError::getErrorDescription()
{
	return errorDescription;
}
