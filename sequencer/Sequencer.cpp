#include "Sequencer.hpp"
#include <list>

Sequencer::Sequencer(auto& cs, auto& ss) : cs(cs), ss(ss)
{
	
}

void Sequencer::addSequence(Sequence* sequence)
{
	//check if sequence allready exists
	//TODO
}


SequencerException& Sequencer::newSequencerException()
{
	sequencerExceptions.emplace_back();
	return sequencerExceptions.back();
}


auto& Sequencer::getCS()
{
	return cs;
}

auto& Sequencer::getSS()
{
	return ss;
}


