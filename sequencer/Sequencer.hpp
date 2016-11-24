#include "Sequence.hpp"



class Sequencer {
public:
	Sequencer();
	
	addSequence(Sequence &sequence, std::string name);	//new sequence-object registered in sequences
	
private:
	list sequences;
};