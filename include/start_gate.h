/**
start_gate.h
Purpose: contains state object for going throught the start gate

@author shadySoruce
@version 0.0.1
*/
#ifndef START_GATE_DEF
#define START_GATE_DEF

#include "state.h"

namespace state
{

class StartGate : public State
{
    private:
        //@var time that state starts
        double _start;

        /**
        update the MotionMessge to reflect current start gate
        */
        void UpdateTarget();

    public:
        /**
        loop for the StartGate state
        */
        int Execute();

    StartGate(ros::Publisher &motionPub, boxes::Boxes& boxes);
    
};

}

#endif