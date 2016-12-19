#include "../../sequencer/Step.hpp"

#include <eeros/math/Matrix.hpp>

class MoveTo : public Step {
public:
// 	MoveTo(Sequencer& S, Sequence* caller, std::string name = "");
	
	int operator()		(int posX, int posY);	//interface to caller
	void setParameter	(int posX, int posY);
	
	bool action();
	
	bool checkExitCondition();
	
	
	
	

	
	
private:	
	AxisVector nextWaypoint;	//EEROS AxisVector
};