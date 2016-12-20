

class Behavior {
public:
	
	enum enumerator {
		notSet,
		repeteOwnerSequence,	//repete the owner sequence of this monitor
		repeteCallerOfOwnerSequence,	//caller of the owner of this monitor
		repeteStep,		//step, which detects the exception
		abortOwnerSequence,
		abortCallerofOwnerSequence,
		abortStep,
		pause,			//pause, till condition==false
		goTo,
	};
	
};