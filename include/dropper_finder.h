/**
dropper.h
Purpose: contains state object for dropper_finder

@author vnguye34
@version 0.0.1
*/
#ifndef DROPPER_FINDER_DEF
#define DROPPER_FINDER_DEF

#include "state.h"

namespace state
{

class Dropper_finder : public State
{
    private:
        //@var time that state starts
		int _target;

        /**
        update the MotionMessge to reflect current active bouy
        */
        void UpdateTarget();

    public:
        /**
        loop for the Bouy state
        */
        int Execute();

    Dropper(ros::Publisher &motionPub, boxes::Boxes& boxes);
    
};

}

#endif