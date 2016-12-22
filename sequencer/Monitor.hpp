#include "Sequencer.hpp"
#include "Sequence.hpp"
#include "Condition.hpp"
#include "SequencerException.hpp"
#include "Behavior.hpp"


class Monitor {
public:
	Monitor(SequenceBase* owner, Condition* condition, Behavior::enumerator behavior);
	Monitor(SequenceBase* owner, Condition* condition, Behavior::enumerator behavior, Sequence* exceptionSequence);
	Monitor(SequenceBase* owner, Condition* condition, Behavior::enumerator behavior, Sequence* exceptionSequence, std::string goToTarget);

	void setExceptionSequence(Sequence* exceptionSequence);
	void setBehavior(Behavior::enumerator behavior);
// 	void setGotToTarget(std::string goToTarget);
	
	bool check();	//returns true if runningState of caller is changed
	

	

	
protected:
	SequenceBase* owner;
	Condition* condition;
	SequenceBase* exceptionSequence;
	Behavior::enumerator behavior;
	std::string goToTarget;			//
	std::string exceptionDescription;
	
private:
	void startExceptionSequence();
	
};