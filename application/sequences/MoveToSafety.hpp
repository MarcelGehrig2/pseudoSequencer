#include "../../sequencer/Sequence.hpp"
#include "../../control/elementarySequences/MoveTo.hpp"
// #include <string.h>


class MoveToSafety : public Sequence {
public:
	MoveToSafety(Sequencer &S, int callerID, std::string name = "");
	
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