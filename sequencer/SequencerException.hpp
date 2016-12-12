#include "Sequencer.hpp"
#include "Sequence.hpp"
#include <string.h>


class SequencerError {
public:
	
	void throwException(Sequence* caller);
	void throwException(Sequence* caller, std::string errorDescription);
	void clearException();
	bool isSet();
	Sequence* getRootSequence();
	std::string getErrorDescription();
	
protected:
	bool error = false;
	Sequence* rootSequence;
	std::string errorDescription;
	
	int errorCounter = 0;
	int errorInARowCounter = 0;	//TODO counter is reset to 1, if two error in a row don't hav the same source
};