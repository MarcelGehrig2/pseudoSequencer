#include "Sequencer.hpp"
#include "Sequence.hpp"
#include "Condition.hpp"
#include "SequencerException.hpp"


class Monitor {
public:
	Monitor(Sequence* caller, Condition condition, behaviorEnum behavior);
	Monitor(Sequence* caller, Condition condition, behaviorEnum behavior, Sequence* exceptionSequence);
	Monitor(Sequence* caller, Condition condition, behaviorEnum behavior, Sequence* exceptionSequence, std::string goToTarget);

	void setExceptionSequence(Sequence* exceptionSequence);
	void setBehavior(behaviorEnum behavior);
	void setGotToTarget(std::string goToTarget);
	
	bool check();	//returns true if runningState of caller is changed
	
	
protected:
	Sequence* owner;
	Condition* condition;
	Sequence* exceptionSequence;
	behaviorEnum behavior;
	std::string goToTarget;			//
	std::string exceptionDescription;
	
private:
	void startExceptionSequence();
	
};