#include "Sequence.hpp"
#include "Sequencer.hpp"
#include "SequencerException.hpp"
// #include "Sequencer.hpp"
#include <thread>
#include <chrono>

Sequence::Sequence(Sequencer& S, Sequence* caller, std::string name = "") :
S(S), startTime(std::chrono::steady_clock::now()), callerSequence(caller)
{ 
	sequenceID = sequenceCount++;	//TODO check how many Sequence-Objects of this type are allowed. Maybe singleton.
	if (name == "") {
		setName("sequence " + sequenceID);		//TODO syntax
	} else {
		//TODO what is, if name already exists?
		setName(name);
	}
	
	setState("idle");
	
	S.addSequence(this);	//register this new Sequence-Object in Sequencer
	
	
	//get and update callerStack
	callerStack = callerSequence->getCallerStack();
	callerStack.push_back(callerSequence->getID());	//add latest caller
	//get and update callerStackBlocking
	//TODO
	
	
	//TODO get the correct SequencerException

}

int Sequence::runBlocking()
{
	setIsBlocking();
	
	// 1 Check precondition
	// ////////////////////
	bool preconditionsPass = checkPreconditions();	//Only preconditions of this seqeuences are checked
							//TODO blocking or jump over
	
	
	if( (runningState == "running") && preconditionsPass ) {		//checkPreconditions did not change the runningState
	
		// 2 Action
		// ////////
		action();		//Send action to Controlsystem and or Safetysystem.
						//Send signal to other sequence
						//Star a Sequence
		
		
		
		
		// 3 Check postcondition
		// /////////////////////
		while(runningState == "running") {
			if(runningState == "running") checkExitCondition();	//used for normal stop of this step/sequence 
			
			if(runningState == "running") checkTimeoutOfAllBlockedCallers();	//if caller timeout -> error thrown
			if(runningState == "running") checkTimeoutOfThisSequence(); //if true -> timeoutAction()
			
			if(runningState == "running") checkExceptionMonitorsOfAllCallers();		//of all callers
			if(runningState == "running") checkExceptionMonitorsOfThisSequence();	//of all callers
		// 	checkPause();			//TODO or us a global Condition instead?
		// 	checkStop();			//TODO a condition as well?
			std::this_thread::sleep_for (std::chrono::milliseconds(pollingTime));
		}
	}

}

int Sequence::runNonBlocking()
{
	setIsNonBlocking();
	
}

int Sequence::run()
{
// 	bool execute = true;
// 	if (	   ( callerSequence->getRunningState() == terminated )
// 			&& ( true ) );
	
	
	if ( true ) {	//does this sequence get executed at all
		runCounter++;
		
		if ( callerSequence->runningState == running ) {
			repetitionCounter=0;
			
			// while loop, if multiple repetition OR this sequence is RESTARTED
			while ( ( nrOfSequenceRepetitions==0 ) || (repetitionCounter <= nrOfSequenceRepetitions) ) {
				repetitionCounter ++;
				
				
				//RUN
				if (getIsBlocking()) { runBlocking(); }
				else { runNonBlocking(); }
				
				
				if ( runningState == restarting ) {
					runningState = running;
				}
				if ( runningState == aborting )	break;
			}
		}
		
		if ( runningState == aborting ) runningState = aborted;
		else runningState = terminated;	//TODO terminated with warning/error?
	}
	
	setCallerRunningState();	//TODO TODO TODO
}

int Sequence::start()
{
	run();
}


bool Sequence::checkPreconditions()
{
	bool pass;
	pass = !( S.sequencerException.error );		//Subsequence does not start, if an error is activ. Like a timeout of a caller sequence.
	return pass;
}



Sequence* Sequence::getCallerSequence()
{
	return callerSequence;
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
	return isBlocking;
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

Sequence::setState(std::string state) : state(state) { }

runningStateEnum Sequence::getRunningState() const {
	return runningState;
}

Sequence::setRunningState(runningStateEnum runningState) : runningState(runningState) { }

std::vector< Sequence* > Sequence::getCallerStack() const
{
	return callerStack;
}

SequencerException* Sequence::getSequencerException() const
{
	return sequencerException;
}


int Sequence::getID() const
{
	return sequenceID;
}

void Sequence::restartSequence()
{
	state="restarting";
}



//Timeout handling
bool Sequence::checkTimeoutOfThisSequence()
{
	//TODO this sequences timout, detected by a sub sequence. now clear exception and do timeout action. 
	//clear error, if it is caused by a called seqeuence, beacause of the timeout of this seqeuence
	if ( S.getSeqencerException()->isSet() ) {
		if ( ( S.getSeqencerException()->getRootSequence() == this ) && ( S.getSeqencerException()->getExceptionDescription() == "timeout" ) ) {
			S.getSeqencerException()->clearException();
		}
	}
	
// 	return checkTimeout(this);	//TODO
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

	
bool Sequence::checkTimeoutOfAllBlockedCallers()	//does not check timeout of "this"
{
	//TODO if callerTimeout happens, throw sequencer exception. the caller sequence handles than the timeout action.
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

bool Sequence::timeoutAction()
{
	S.sequencerError.throwError();
}


