#include "Sequence.hpp"
#include "Sequencer.hpp"
#include <thread>
#include <chrono>

Sequence::Sequence(Sequencer& seq, int callerID, std::string name="") :
S(seq), startTime(std::chrono::steady_clock::now()) 
{ 
	sequenceID = sequenceCount++;	//TODO check how many Sequence-Objects of this type are allowed. Maybe singleton.
	if (name == "") {
		setName("sequence " + sequenceID);		//TODO syntax
	} else {
		//TODO what is, if name already exists?
		setName(name);
	}
	
	setState("idle");
	
	S.addSequence(getName());	//register this new Sequence-Object in Sequencer
	
	//get and update callerStack
	Sequence* callerSequence = S.getSequenceByID(callerID);
	callerStack = callerSequence.getCallerStack();
	callerStack.push_back(callerSequence.getID());	//add latest caller
	//get and update callerStackBlocking
	//TODO
	

}

int Sequence::runBlocking()
{
	setIsBlocking();
	
	// 1 Check precondition
	// ////////////////////
	checkPreconditions();	//Only preconditions of this seqeuences are checked
	
	
	
	
	// 2 Action
	// ////////
	action();		//Send action to Controlsystem and or Safetysystem.
					//Send signal to other sequence
					//Star a Sequence
	
	
	
	
	// 3 Check postcondition
	// /////////////////////
	while(bool stop = false) {
		stop = stop | checkTimeoutOfAllCallers();
		stop = stop | stopCondition();		//TODO beter checkExitCondition() ??
		stop = stop | checkExceptionMonitors();	//of all callers
	// 	checkPause();			//TODO or us a global Condition instead?
	// 	checkStop();			//TODO a condition as well?
		std::this_thread::sleep_for (std::chrono::milliseconds(pollingTime));
	}
	

}

int Sequence::runNonBlocking()
{
	setIsNonBlocking();
	
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

int Sequence::start()
{
	run();
}


bool Sequence::checkPreconditions()
{

}





bool Sequence::stopCondition()
{
	return true;	// Sequence is immediately stopped after action is performed.
}

void Sequence::setIsBlocking()
{
	isBlocking = true;
}

void Sequence::setIsNonBlocking()
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

std::vector< int > Sequence::getCallerStack()
{

}


//Timeout handling
bool Sequence::checkTimeout()
{
	return checkTimeout(getID());
}

bool Sequence::checkTimeout(int sequenceID)
{
	Sequence* sequence = S.getSequenceByID(sequenceID);
	return checkTimeout(&sequence);
}

bool Sequence::checkTimeout(Sequence* sequence)
{
	//TODO implement Timeout check
	if (sequence->timeout > 0) {
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - sequence->startTime) > sequence->timeout) return true;
		else return false;
	}
	// 	sequence->getStartOfTimeout;
// 	sequence->getTotalTimeoutTime;
}

	
bool Sequence::checkTimeoutOfAllCallers()	//does not check timeout of "this"
{
	//TODO what should happen if a callerTimeout happens
	//TODO non blocking seqeuences should not inherit timeouts --> outer iterator
	//TODO how do the list iterator exactly work?
	//lates (newest) caller of a non blocking call. Timeouts of this caller and older callers are ignored
	
	bool isTimeout = false;
// 	for (std::list<int>::const_iterator iterator = callerStack.end(), end = callerStack.begin(); iterator != end; --iterator) {
// // 		int a = iterator.operator*();
// 		if ( (!(S.getSequenceByID(iterator.operator*())->getIsBlocking)) | (iterator == callerStack.begin()) {	//latest caller of a non blocking sequence, or first sequence
// 			for (iterator, end = callerStack.end(); iterator != end; ++iterator) {
// 				isTimeout = isTimeout | checkTimeout(*iterator);
// 			}
// 		}
// 	}
	return isTimeout;		//if true, at least on1 timeout occoured
}


