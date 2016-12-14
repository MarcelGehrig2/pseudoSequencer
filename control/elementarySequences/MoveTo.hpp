#include "../../sequencer/Sequence.hpp"

#include <eeros/math/Matrix.hpp>

class MoveTo : public Sequence {
public:
	MoveTo(Sequencer &S, int callerID, std::string name = "");
	
	int operator()		(int posX, int posY);	//interface to caller
	void setParameter	(int posX, int posY);
	
	bool action();
	
	bool checkExitCondition();
	
	
	
	

	
	
private:	
	AxisVector nextWaypoint;	//EEROS AxisVector
};