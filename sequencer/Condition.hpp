

class Condition {
	
public:
	Condition();
	
	
	bool getConditionState();
	
	void checkCondition() = 0;		// has to be overwritten (pure virtual function)
	
	
protected:
	bool conditionState = false;
	bool inheritable = false;
	
}