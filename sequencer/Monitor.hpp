#include "Sequencer.hpp"
#include "Sequence.hpp"
#include "Condition.hpp"


class Monitor {
public:
	Monitor(Sequence* caller, Condition condition, behaviorEnum behavior);
	Monitor(Sequence* caller, Condition condition, behaviorEnum behavior, Sequence* exceptionSequence);
	Monitor(Sequence* caller, Condition condition, behaviorEnum behavior, Sequence* exceptionSequence, std::string goToTarget);

	void setExceptionSequence(Sequence* exceptionSequence);
	void setBehavior(behaviorEnum behavior);
	void setGotToTarget(std::string goToTarget);
	
	bool check();	//returns true if runningState of caller is changed
	
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
	Sequence* owner;
	Condition* condition;
	Sequence* exceptionSequence;
	behaviorEnum behavior;
	std::string goToTarget;			//
	
private:
	void startExceptionSequence();
	
};