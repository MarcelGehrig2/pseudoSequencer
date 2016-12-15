#include "Sequencer.hpp"
#include "Sequence.hpp"
#include <string.h>


class SequencerException {
public:
	SequencerException();
	
	void throwException(Sequence* invoking, Sequence* owner, behaviorEnum behavior, std::string exceptionDescription="");
	void clearException();
	bool isSet() const;
	Sequence* getRootSequence() const;
	Sequence* getOwnerSequence() const;
// 	Sequence* getCallerOfOwnerSequence() const;
	std::string getExceptionDescription()  const;
	void setRunningStateOfThisSequence(Sequence* sequence);	
	
	enum behaviorEnum {
		notSet,
		repeteOwnerSequence,	//repete the owner sequence of this monitor
		repeteCallerOfOwnerSequence,	//caller of the owner of this monitor
		repeteStep,		//step, which detects the exception
		abortOwnerSequence,
		abortCallerofOwnerSequence,
		abortStep,
		goTo,
	};
	
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
	behaviorEnum behavior;
	Sequence::runningStateEnum invokingSequenceRunningState;
	Sequence::runningStateEnum ownerSequenceRunningState;
	Sequence::runningStateEnum callerOfOwnerSequenceRunningState;
	
	
	void setAllRelevantRunningStates();	//depends on 'behavior'
	
	int exceptionCounter;		//total count of exception since sequencer start
	int exceptionInARowCounter;
};