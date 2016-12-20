#include "Sequencer.hpp"
#include "Sequence.hpp"
#include "Behavior.hpp"
#include <string.h>


class SequencerException {
public:
	SequencerException();
	
	void throwException(Sequence* invoking, Sequence* owner, Behavior::Enumerator behavior, std::string exceptionDescription="");
	void clearException();
	void reset();			//resets all member value
	bool isSet() const;
	Sequence* getRootSequence() const;
	Sequence* getOwnerSequence() const;
// 	Sequence* getCallerOfOwnerSequence() const;
	std::string getExceptionDescription()  const;
	void setRunningStateOfThisSequence(Sequence* sequence);	

	
// protected:
private:
	bool exception = false;
	Sequence* invokingSequence;		//sequence, which detected the exception
	Sequence* ownerSequence;	//owner of the monitor. may be the same as the caller
	Sequence* callerOfOwnerSequence;
	std::string exceptionDescription;
	Sequence* previousRootSequence;
	Sequence* previousOwnerSequence;
	std::string previousExceptionDescription;
	Behavior::Enumerator behavior;
	Sequence::runningStateEnum invokingSequenceRunningState;
	Sequence::runningStateEnum ownerSequenceRunningState;
	Sequence::runningStateEnum callerOfOwnerSequenceRunningState;
	
	
	void setAllRelevantRunningStates();	//depends on 'behavior'
	
	int exceptionCounter;		//total count of exception since sequencer start
	int exceptionInARowCounter;
};