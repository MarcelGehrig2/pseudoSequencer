#include "Sequencer.hpp"
#include "Sequence.hpp"
#include <string.h>


class SequencerException {
public:
	SequencerException();
	
	void throwException(Sequence* root, Sequence* owner, behaviorEnum behavior, std::string exceptionDescription="");
	void clearException();
	bool isSet() const;
	Sequence* getRootSequence() const;
	std::string getExceptionDescription()  const;
	
	
	enum behaviorEnum {
		repeteOwnerSequence,	//repete the owner sequence of this monitor
		repeteCallerOfOwnerSequence,	//caller of the owner of this monitor
		repeteStep,		//step, which detects the exception
		abortOwnerSequence,
		abortCallerofOwnerSequence,
		abortStep,
		goTo,
	};
	
protected:
	bool exception = false;
	Sequence* rootSequence;		//sequence, which detected the exception
	Sequence* ownerSequence;	//owner of the monitor. often the same as the caller
	std::string exceptionDescription;
	Sequence* previousRootSequence;
	Sequence* previousOwnerSequence;
	std::string previousExceptionDescription;
	behaviorEnum behavior;
	
	int exceptionCounter;		//total count of exception since sequencer start
	int exceptionInARowCounter;
};