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



int Sequence::operator()()
{
	return SequenceBase::start();
}






std::__cxx11::string Sequence::getName() const
{
	return name;
}
