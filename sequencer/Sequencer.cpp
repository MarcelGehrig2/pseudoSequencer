#include "Sequencer.hpp"


Sequencer::Sequencer(auto& cs, auto& ss) : cs(cs), ss(ss)
{
	
}

void Sequencer::addSequence(Sequence* sequence)
{
	//check if sequence allready exists
	//TODO
}


auto& Sequencer::getCS()
{
	return cs;
}

auto& Sequencer::getSS()
{
	return ss;
}


