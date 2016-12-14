#include "Sequence.hpp"
#include "Condition.hpp"
#include "SequencerError.hpp"
#include <string>
#include <list>

// #include <eeros/safety/SafetySystem.hpp>	//TODO SS and CS are not known at EEROS compile time -> polymorfic
// #include "control/ControlSystem.hpp"		//TODO SS and CS are not known at EEROS compile time -> polymorfic

class Sequencer {
public:
	Sequencer(auto& cs, auto& ss);
	
	void addSequence(Sequence* sequence);	//new sequence-object registered in sequences
	Sequence* getSequenceByID(int ID);				//TODO implementation
	Sequence* getSeqenceByName(std::string name);	//TODO implementation
	
	void addCondition(Condition* condition);
	Condition* getConditionByName(std::string name);	// TODO
	
	SequencerError* getSeqencerException();
	
	auto& getCS();
	auto& getSS();
	
private:
	SequencerError sequencerException;
	std::list< Sequence* > sequences;
	std::list< Condition* > conditions;
	auto& cs;
	auto& ss;
};