#include "Sequencer.hpp"
#include "Sequence.hpp"
#include "Condition.hpp"
#include "SequencerException.hpp"
#include "Behavior.hpp"


class Monitor {
public:
	Monitor(Sequence* caller, Condition condition, Behavior::enumerator behavior);
	Monitor(Sequence* caller, Condition condition, Behavior::enumerator behavior, Sequence* exceptionSequence);
	Monitor(Sequence* caller, Condition condition, Behavior::enumerator behavior, Sequence* exceptionSequence, std::string goToTarget);

	void setExceptionSequence(Sequence* exceptionSequence);
	void setBehavior(Behavior::enumerator behavior);
	void setGotToTarget(std::string goToTarget);
	
	bool check();	//returns true if runningState of caller is changed
	

	

	
protected:
	Sequence* owner;
	Condition* condition;
	Sequence* exceptionSequence;
	Behavior::enumerator behavior;
	std::string goToTarget;			//
	std::string exceptionDescription;
	
private:
	void startExceptionSequence();
	
};