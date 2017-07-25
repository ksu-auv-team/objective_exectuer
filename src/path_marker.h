/**
path_marker.h
Purpose: contains state object for going throught the start gate

@author DeusExMachina96
@version 0.0.1
*/
#ifndef PATH _MARKER_DEF
#define PATH_MARKER_DEF

#include "state.h"

namespace state
{

class PathMarker : public State
{
    private:
        //@var time that state starts
        double _start;

        /**
        update the MotionMessge to reflect current path marker
        */
        void UpdateTarget();

    public:
        /**
        loop for the PathMarker state
        */
        int Execute();

    PathMarker(ros::Publisher &motionPub, boxes::Boxes& boxes);
    
};

}

#endif