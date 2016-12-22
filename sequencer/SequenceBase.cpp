#include "SequenceBase.hpp"
#include "Sequencer.hpp"
#include "SequencerException.hpp"
// #include "Sequencer.hpp"
#include <thread>
#include <chrono>

SequenceBase::SequenceBase(Sequencer& S, SequenceBase* caller)
: S(S), startTime(std::chrono::steady_clock::now()), callerSequence(caller)
{ 

	
	setState("idle");
	
	S.addSequence(this);	//register this new Sequence-Object in Sequencer
	
	
	//get and update callerStack
	callerStack = callerSequence->getCallerStack();
	callerStack.push_back(callerSequence->getID());	//add latest caller
	//get and update callerStackBlocking
	//TODO
	
	
	//inherit SequencerException from caller
	//TODO if mainSequence no caller exists
	sequencerException = callerSequence->getSequencerException();
	
}

int SequenceBase::runBlocking()
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
			
			if(runningState == "running") checkMonitorsOfAllCallers();		//of all callers
			if(runningState == "running") checkMonitorsOfThisSequence();	//of all callers
		// 	checkPause();			//TODO or us a global Condition instead?
		// 	checkStop();			//TODO a condition as well?
			std::this_thread::sleep_for (std::chrono::milliseconds(pollingTime));
		}
	}

}

int SequenceBase::runNonBlocking()
{
	setIsNonBlocking();
	
}

int SequenceBase::run()
{
// 	bool execute = true;
// 	if (	   ( callerSequence->getRunningState() == terminated )
// 			&& ( true ) );
	
	// if sequencerException is active: abort or repete sequence, depending on exception behavior:
	sequencerException->setRunningStateOfThisSequence(this);

	
	if ( runningState != aborting ) {
		runCounter++;
		
		if ( callerSequence->runningState == running ) {
			repetitionCounter=0;
			
			// while loop, if multiple repetition OR this sequence is RESTARTED
			while ( ( nrOfSequenceRepetitions==0 ) || (repetitionCounter <= nrOfSequenceRepetitions) ) {
				repetitionCounter ++;
				
				
				//RUN
				if (getIsBlocking()) { runBlocking(); }
				else { runNonBlocking(); }
				
				
				// if sequencerException is active: abort or repete sequence, depending on exception behavior:
				sequencerException->setRunningStateOfThisSequence(this);
				if ( runningState == restarting ) {
					runningState = running;
				}
				if ( runningState == aborting )	break;
			}
		}
		
		if ( runningState == aborting ) runningState = aborted;
		else runningState = terminated;	//TODO terminated with warning/error?
	}
	
}

int SequenceBase::start()
{
	run();
}



bool SequenceBase::isStep() const
{
	return false;
}


bool SequenceBase::checkPreconditions()
{
	bool pass;		//TODO
	pass = !( S.sequencerException.error );		//Subsequence does not start, if an error is activ. Like a timeout of a caller sequence.
	return pass;
}



SequenceBase* SequenceBase::getCallerSequence()
{
	return callerSequence;
}


bool SequenceBase::stopCondition()
{
	return true;	// Sequence is immediately stopped after action is performed.
}

void SequenceBase::setIsBlocking()
{
	isBlocking = true;
}

void SequenceBase::setIsNonBlocking()
{
	isBlocking = false;
}

bool SequenceBase::getIsBlocking() const
{
	return isBlocking;
}

std::string SequenceBase::getState() const {
	return state;
}

SequenceBase::setState(std::string state) : state(state) { }

runningStateEnum SequenceBase::getRunningState() const {
	return runningState;
}

SequenceBase::setRunningState(runningStateEnum runningState) : runningState(runningState) { }

std::vector< SequenceBase* > SequenceBase::getCallerStack() const
{
	return callerStack;
}

std::vector< SequenceBase* > SequenceBase::getCallerStackBlocking() const
{
	return callerStackBlocking;
}


SequencerException& SequenceBase::getSequencerException() const
{
	return sequencerException;
}

void SequenceBase::setID(int ID)
{
	sequenceID = ID;
}


int SequenceBase::getID() const
{
	return sequenceID;
}

void SequenceBase::restartSequence()
{
	state="restarting";
}



//Timeout handling
bool SequenceBase::checkTimeoutOfThisSequence()
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

bool SequenceBase::checkTimeout(int sequenceID)
{
	SequenceBase* sequence = S.getSequenceByID(sequenceID);
	return checkTimeout(&sequence);
}

bool SequenceBase::checkTimeout(SequenceBase* sequence)
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

	
bool SequenceBase::checkTimeoutOfAllBlockedCallers()	//does not check timeout of "this"
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

bool SequenceBase::timeoutAction()
{
	S.sequencerError.throwError();
}



