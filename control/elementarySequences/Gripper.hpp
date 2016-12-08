#include <string>

#include "../../sequencer/Sequence.hpp"

class Gripper : public Sequence {
public:
	// CONSTRUCTOR TODO
	
	int operator()(int gripperID, std::string action);	//interface to caller
	
	bool action();
	
	bool stopCondition();
	
private:
	int gripperID;
	std::string action;
};