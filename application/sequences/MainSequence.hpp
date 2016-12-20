#include "SequenceRendevous.hpp"
#include "SequenceConveyer.hpp"
#include "../../control/conditions/CondStop.hpp"
#include "../../control/conditions/CondPause.hpp"
#include "../../sequencer/Monitor.hpp"


class MainSequence : public Sequence {
public:
	MainSequence(Sequencer& S, Sequence* caller, std::string name = "");
	
	bool action();
	
	// Sequences
	// ////////////////////////////////////////////////////////////////////////
	SequenceRendevous* seqRendevous;
	Sequence* seqConveyer;
	
	// Conditions
	// ////////////////////////////////////////////////////////////////////////
	CondStop* condStop;
	Condition* condPause;

	// Monitors
	// ////////////////////////////////////////////////////////////////////////
	Monitor monitorStop;
	Monitor monitorPause;
	
	
private:
	
};