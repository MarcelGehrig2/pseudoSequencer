#include "Sequence.hpp"
#include <string>
#include <list>


class Sequencer {
public:
	Sequencer();
	
	void addSequence(Sequence &sequence, std::string name);	//new sequence-object registered in sequences
	Sequence* getSequenceByID(int ID);
	Sequence* getSeqenceByName(std::string name);
	
private:
	std::list< Sequence* > sequences;
};