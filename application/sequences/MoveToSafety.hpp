#include "../../sequencer/Sequence.hpp"
#include "../../control/elementarySequences/MoveTo.hpp"
// #include <string.h>


class MoveToSafety : public SequenceBase {
public:
	MoveToSafety(Sequencer& S, SequenceBase* caller, std::string name = "");
	
	int operator()		(int safetyPos);
	void setParameter	(int safetyPos);
	
	bool action();
	
	bool checkExitCondition();
	
	
	

	// sequences
	// ////////////////////////////////////////////////////////////////////////
	MoveTo* moveTo;
	
private:
	int safetyPos;
};