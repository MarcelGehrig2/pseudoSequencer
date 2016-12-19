#include "../../sequencer/Step.hpp"

#include <string>



class Gripper : public Step {
public:
	// CONSTRUCTOR: Base constructor is used
	
	int operator()		(int gripperID, gripperStateEnum action);	//interface to caller
	void setParameter	(int gripperID, gripperStateEnum action);
	bool action();
	
	bool stopCondition();
	
	enum gripperStateEnum {
		open,
		close,
		notSet,
	};
	
private:
	int gripperID;
	std::string action;
};