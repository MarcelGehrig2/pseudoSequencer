#include "Sequencer.hpp"
#include <string>
#include <vector>
#include <chrono>

class Sequence {
	
// 	friend class eeros::sequencer::Sequencer;
	
public:
	Sequence(Sequencer& S, int callerID, std::string name = "");
	
	int runBlocking();
	int runNonBlocking();
	int run();				//uses standard value "isBlocking"	
	bool checkPreconditions();
	bool checkPostconditions();
	bool checkExceptionMonitors();
	
	virtual bool action() = 0;		//pure virtual function
	
	virtual void set(std::string instruction, type value);	//TODO ??? polymorph or string
	
	void addMonitor(Monitor monitor); //TODO Exception Monitor
	
	std::string getName() const;
	void setName(std::string name);
	int getID() const;
	std::vector<int> getCallerStack();
	
	
	std::string getState() const;
	void setState(std::string state);
	
	//Timeout
	void setTimeout(double timeout);		//in seconds. For this sequence
	bool checkTimeout();
	bool checkTimeout(int sequenceID);
	bool checkTimeout(Sequence* sequence);
	bool checkTimeoutOfAllCallers();		//including "this" sequence, goes up to (but without) latest caller of a non blocking sequence
	
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
protected:
	Sequencer &s;			//reference to singleton Sequencer
	
	std::string name;
	int sequenceID = 0;
	auto startTime;
	double timeout = 0;				//0 = not set or infinite
	int pollingTime = 10;			//in milliseconds for checkPostconditions (including timeout and stuff)
	
	std::string state;				//TODO use enum
	bool isBlocking = true;			//standard run mode
	std::vector<int> callerStack;	//vector with callerIDs. Top element is latest caller
	std::vector<int> callerStackBlocking;	//TODO vector with callerIDs since last non blocking call. Botten element is the oldest blocked caller in this row.
	
	
	
	static int sequenceCount = 0;	//TODO works like intended? every object created from an inherited class increments cont
};
		