#include "Sequencer.hpp"

class Sequence {
	
	friend class eeros::sequencer::Sequencer;
	
public:
	Sequence(Sequencer &S, std::string name = "");
	
	int runBlocking();
	int runNonBlocking();
	int run();				//uses standard value "isBlocking"
	
	virtual set(std::string instruction, type value);	//??? polymorph or string
	
	addMonitor(Monitor monitor); //TODO Monitor
	
	std::string getName() const;
	setName(std::string name);
	std::string getState() const;
	setState(std::string state);
	setTimeout(double timeout);		//in seconds
	
	setIsBlocking();		//standard run mode
	setIsNonBlocking();
	bool getIsBlocking() const;
	
// 	virtual bool checkPreCondition();
// 	virtual bool checkPostCondition();
// 	
// protected:
// 	virtual void yield();
// 	
// 	virtual void init();
// 	virtual void exit();
// 	
// 	eeros::logger::Logger<eeros::logger::LogWriter> log;
protected:
	Sequencer &S;			//reference to singleton Sequencer
	
	std::string name;
	std::string state;		//TODO use enum
	static int sequenceCount;	//TODO works like intended? every object created from an inherited class increments
	int sequenceID;
	double timeout;
	bool isBlocking = true;		//standard run mode
};
		