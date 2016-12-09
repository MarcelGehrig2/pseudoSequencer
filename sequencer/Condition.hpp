#include "Sequencer.hpp"
#include "Sequence.hpp"


class Condition {	
public:
	Condition(Sequencer& seq);
	
	bool operator()();		// checks condition	
	virtual bool check();	
	virtual void validate() = 0;		// has to be overwritten (pure virtual function)
	
	void addExceptionSequence(Sequence* exceptionSequence);
	
protected:
	Sequencer& S;			//reference to singleton Sequencer
	
	Sequence* exceptionSequence;
	int retries = 0;
	int maxRetries = 1;
	
	int counter = 0;
	bool conditionState = false;
	bool heritable = false;
	
};