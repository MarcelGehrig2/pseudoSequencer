#include "SequenceBase.hpp"
#include "Monitor.hpp"


class Sequence : public SequenceBase {
public:
	Sequence(Sequencer& S, SequenceBase* caller, std::string name);
	
	std::string getName() const;
	
	int operator() ();
	
	void addMonitor(Monitor* monitor);	//TODO implement
	
	//TODO run(
	//TODO runBlocking()
	
	
protected:
	
private:
	std::string name;
	int sequenceID = 0;
	
	static int sequenceCount = 0;	//TODO works like intended? every object created from an inherited class increments cont
	
	
	
	
};