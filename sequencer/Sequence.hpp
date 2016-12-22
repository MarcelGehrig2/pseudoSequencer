#include "SequenceBase.hpp"
#include "Monitor.hpp"


class Sequence : public SequenceBase {
public:
	Sequence(Sequencer& S, SequenceBase* caller, std::string name);
	~Sequence();
	
	std::string getName() const;
	setName(std::string name);
	
	int operator() ();
	int runBlocking();
	int runNonBlocking();
	
	bool isStep();
	
	void addMonitor(Monitor* monitor);	//TODO implement
	
	//TODO run(
	//TODO runBlocking()
	
	
protected:
	
private:
	std::string name;
	int sequenceID = 0;
	
	
	static int sequenceCount = 0;	//TODO works like intended? counts all created sequences
	
	
	
	
};