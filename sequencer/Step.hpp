#include "SequenceBase.hpp"


class Step : public BaseSequence {
public:
	Step(Sequencer& S, BaseSequence* caller);

	
	bool isStep() const;
	
protected:
	
	
private:
	
	
};