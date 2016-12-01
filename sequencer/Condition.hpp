

class Condition {	
public:
	Condition();
	
	
	bool check();
	
	void validate() = 0;		// has to be overwritten (pure virtual function)
	
	
protected:
	bool conditionState = false;
	bool heritable = false;
	
};