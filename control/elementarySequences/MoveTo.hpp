#include "../../sequencer/Sequence.hpp"

#include <eeros/math/Matrix.hpp>

class MoveTo : public Sequence {
public:
	MoveTo(Sequencer &S, int callerID, std::string name = "");
	
	int operator()(int posX, int posY);	//interface to caller
	
	bool action();
	
	bool stopCondition();
	
	
	
	

	
	
private:	
	AxisVector nextWaypoint;	//EEROS AxisVector
};