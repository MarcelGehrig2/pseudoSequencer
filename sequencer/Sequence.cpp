#include "Sequence.hpp"


Sequence::Sequence(Sequencer& S, SequenceBase* caller, std::__cxx11::string name)
: SequenceBase(S, caller)
{
	sequenceID = sequenceCount++;	//TODO check how many Sequence-Objects of this type are allowed. Maybe singleton.
	if (name == "") {
		//TODO Error: empty string is not allowed Stop 
	} else {
		//TODO Error if name allready exists
		this->name = name;
	}
	
}

Sequence::~Sequence()
{
	//TODO remove this sequence from list in Sequencer
}




int Sequence::operator()()
{
	return SequenceBase::start();
}

bool Sequence::isStep()
{
	return false;
}


void Sequence::addMonitor(Monitor* monitor)
{
	monitors.push_back(monitor);
}





std::__cxx11::string Sequence::getName() const
{
	return name;
}
