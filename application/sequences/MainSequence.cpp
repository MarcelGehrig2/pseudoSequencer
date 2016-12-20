#include "MainSequence.hpp"
// #include "../../sequencer/Sequence.hpp"
// #include "../../sequencer/SequenceBase.hpp"

MainSequence::MainSequence(Sequencer& S, Sequence* caller, std::__cxx11::string name)
: Sequence(S, caller , name)
{
	
	// create sequences
	// ////////////////////////////////////////////////////////////////////////
	seqRendevous = new SequenceRendevous(S, this, "rendevous Sequence");
	seqConveyer = new SequenceConveyer(S, this, "conveyer Sequence");

	// create conditions	//TODO move to Sequencer
	// ////////////////////////////////////////////////////////////////////////
	condStop = new CondStop(S);
	condPause = new CondPause(S);

	// create monitors
	// ////////////////////////////////////////////////////////////////////////
	//TODO syntax
	//TODO destruction of monitors -> not on heap?
	monitorStop = Monitor(this, condStop, Monitor::abortOwnerSequence);
	this->addMonitor( &monitorStop );
	monitorPause = Monitor(this, condPause, Monitor::pause);
	this->addMonitor( &monitorPause );
}


bool MainSequence::action()
{
	// create steps
	// ////////////////////////////////////////////////////////////////////////////

	
	// run seqence
	// ////////////////////////////////////////////////////////////////////////////
	
	seqRendevous->runNonBlocking();
	seqConveyer->runNonBlocking();
	
	while ( (seqRendevous != Sequence::terminated) && (seqRendevous != Sequence::terminated) ) {
		sleep(1);	//TODO sleep 1sec
	}

}
