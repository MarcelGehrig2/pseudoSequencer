#include "Sequencer.hpp"


Sequencer::Sequencer(auto& cs, auto& ss) : cs(cs), ss(ss)
{
	
}

auto& Sequencer::getCS()
{
	return cs;
}

auto& Sequencer::getSS()
{
	return ss;
}


