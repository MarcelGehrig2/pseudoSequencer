#include "../../sequencer/Sequence.hpp"


class sequenceRendevous : public Sequence {
public:
	sequenceRendevous(Sequencer& S, Sequence* caller, std::string name = "");
	
	sequencePickUp pickUp(std::string name);
	

	
	sequenceBringToRendezvous bringToRendezvous(string name);
	

	
	
private:	
	
};