#include "Sequencer.hpp"

class Condition {	
public:
	Condition(Sequencer& seq);
	
	bool operator()();
	
	virtual bool check();
	
	virtual void validate() = 0;		// has to be overwritten (pure virtual function)
	
	
protected:
	Sequencer &S;			//reference to singleton Sequencer
	
	bool conditionState = false;
	bool heritable = false;
	
};