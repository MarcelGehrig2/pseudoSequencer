#include "Condition.hpp"
#include <chrono>


class TimeoutCondition : Condition {
public:
	TimeoutCondition(Sequencer& seq, double timeInSec);
	
	bool valdiate();
	
	void resetTimeout();
	void setTime(double timeInSec);	//in seconds
	
	
protected:
	double timeInSec;
	
private:
	bool started = false;
	auto startTime;
	
};