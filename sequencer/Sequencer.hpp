#include "Sequence.hpp"
#include <string>
#include <list>

// #include <eeros/safety/SafetySystem.hpp>	//TODO SS and CS are not known at EEROS compile time -> polymorfic
// #include "control/ControlSystem.hpp"		//TODO SS and CS are not known at EEROS compile time -> polymorfic

class Sequencer {
public:
	Sequencer(auto& cs, auto& ss);
	
	void addSequence(Sequence &sequence, std::string name);	//new sequence-object registered in sequences
	Sequence* getSequenceByID(int ID);				//TODO implementation
	Sequence* getSeqenceByName(std::string name);	//TODO implementation
	
	auto& getCS();
	auto& getSS();
	
private:
	std::list< Sequence* > sequences;
	auto& cs;
	auto& ss;
};