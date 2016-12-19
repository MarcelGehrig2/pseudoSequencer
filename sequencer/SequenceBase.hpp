#include "Sequencer.hpp"
#include "Condition.hpp"
#include "SequencerException.hpp"
#include "Monitor.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <functional>

class SequenceBase {
	
// 	friend class eeros::sequencer::Sequencer;
	
public:
	SequenceBase(Sequencer& S, SequenceBase* caller, std::string name = "");
	
// 	virtual int operator()(std::string args) = 0;	//has to be implemented in derived class
	int start();	//called bei operator() by derived class
	
	int runBlocking();
	int runNonBlocking();
	int run();				//uses standard value "isBlocking"
	void restartSequence();
	
	bool checkPreconditions();
	bool checkPostconditions();
	bool checkExceptionMonitors();
// 	void addStopCondition(std::function<bool ()> f);
	virtual bool stopCondition();
	virtual bool checkExitCondition() = 0;
	
	virtual bool action() = 0;		//pure virtual function
	
// 	virtual void set(std::string instruction, type value);	//TODO ??? polymorph or string
	
	void addMonitor(Monitor monitor); //TODO Exception Monitor
	
	std::string getName() const;
	void setName(std::string name);
	int getID() const;
	SequenceBase* getCallerSequence() const;
	std::vector< SequenceBase* > getCallerStack() const;
	SequencerException& getSequencerException() const;
	
	
	std::string getState() const;
	void setState(std::string state) const;
	runningStateEnum getRunningState() const;
	void setRunningState(runningStateEnum runningState);
// 	void setCallerRunningState(runningStateEnum runningState);
	
	void restartSequence();
	void pauseSequence();
	
	//Timeout
	void setTimeout(double timeoutInSec);		//in seconds. For this sequence
// 	bool checkTimeout();
	bool checkTimeout(int sequenceID);
	bool checkTimeout(SequenceBase* sequence);
	bool checkTimeoutOfAllBlockedCallers();		//excluding "this" sequence, goes up to (but without) latest caller of a non blocking sequence
	bool checkTimeoutOfThisSequence();
	virtual timeoutAction();				//action when timout occours: standard throw error
	
	// run mode
	void setIsBlocking();		//standard run mode
	void setIsNonBlocking();
	bool getIsBlocking() const;
// 	
// protected:
// 	virtual void yield();
// 	
// 	virtual void init();
// 	virtual void exit();
// 	
	eeros::logger::Logger<eeros::logger::LogWriter> log;
	
	enum runningStateEnum {
		notSet,
		idle,
		running,
		paused,
		aborting,
		aborted,
		terminated,
		restartingStep,
		restarting,
	};	// terminatedWithWarning, terminatedBecauseCallerMonitor
	
	
protected:
	Sequencer &S;			//reference to singleton Sequencer
	
	std::string name;
	int sequenceID = 0;
	auto startTime;
	double timeout = 0;				//0 = not set or infinite
	int pollingTime = 10;			//in milliseconds for checkPostconditions (including timeout and stuff)
	int nrOfSequenceRepetitions = 1;	//number of repetitions of this sequence; 0==infinite; 1==run only once; 2==run once and repete once
											//sequence restarts are not counted
	int repetitionCounter = 0;		//how many times the sequence got repeted within a single run
	int runCounter = 0;	
	int timeoutsInARowCounter = 0;	//TODO when to reset??
	
	std::string state;				//TODO use enum,	userdefined
	runningStateEnum runningState = idle;	
	
	
	
	bool isBlocking = true;			//standard run mode
	std::vector< SequenceBase* > callerStack;	//vector with all caller sequences. Top element is latest caller
	std::vector< SequenceBase* > callerStackBlocking;	//TODO vector with all sequences, which are blocked with this sequence. Bottom element is the oldest blocked caller
	SequenceBase* callerSequence;
	
	SequencerException& sequencerException;
	
	std::vector< Condition* > preconditions;
	std::vector< Condition* > postconditions;
	
	static int sequenceCount = 0;	//TODO works like intended? every object created from an inherited class increments cont
	
	
	private:
	void checkExceptionMonitorsOfThisSequence();
	void checkExceptionMonitorsOfThisSequence();
	void checkExceptionMonitorsOfAllCallers();
	void checkExceptionMonitorsOfAllCallers();
	void checkExceptionMonitorsOfAllCallers();
};
		