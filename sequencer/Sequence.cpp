#include "Sequence.hpp"
#include "Sequencer.hpp"

Sequence::Sequence(Sequencer &S, std::string name="") : S(S), name(name) { 
	sequenceID = sequenceCount++;
	
	if (name == "") {
		setName("sequence " + sequenceID);		//TODO syntax
	}
	
	setState("idle");
	
	S.addSequence(getName());
}

int Sequence::runBlocking()
{

}

int Sequence::runNonBlocking()
{

}

int Sequence::run()
{
	if (getIsBlocking()) {
		runBlocking();
	}
	else {
		runNonBlocking();
	}
}

Sequence::setIsBlocking()
{
	isBlocking = true;
}

Sequence::setIsNonBlocking()
{
	isBlocking = false;
}

bool Sequence::getIsBlocking() const
{

}
	
std::string Sequence::getName() const {
	return name;
}

Sequence::setName(std::string name) : name(name) {
	return;
}

std::string Sequence::getState() const {
	return state;
}

Sequence::setState(std::string state) : state(state) {
	return;
}
