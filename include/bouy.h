/**
start_gate.h
Purpose: contains state object for bouys

@author vnguye34
@version 0.0.1
*/
#ifndef BOUY_DEF
#define BOUY_DEF

#include "state.h"

namespace state
{

class Bouy : public State
{
    private:
        //@var time that state starts
        double _start;

        /**
        update the MotionMessge to reflect current active bouy
        */
        void UpdateTarget();

    public:
        /**
        loop for the Bouy state
        */
        int Execute();

    Bouy(ros::Publisher &motionPub, boxes::Boxes& boxes);
    
};

}

#endif