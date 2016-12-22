#include "SequenceBase.hpp"


class Step : public SequenceBase {
public:
	Step(Sequencer& S, SequenceBase* caller);

	
	bool isStep() const;
	
protected:
	
	
private:
	
	
};