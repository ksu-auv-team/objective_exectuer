/**
search.cpp
Purpose: source file for search state

@author shadySource
@version 0.0.1
*/
#include "search.h"

using namespace state;

Search::Search(ros::Publisher& motionPub, boxes::Boxes& boxes)
    : State(motionpub, boxes), _target(-1), _targetSeenCounter(0)
{
    this->MotionMessage.data = [0, 0, 0, 1]; // example array for a message
}

int Search::Execute()
{
    if (_target == -1)
    {
        ROS_ERROR("Target not set before search");
        return -1;
    }
    //do stuff, calculate message, publish message
    while(ros::ok())
    {
        if (Boxes->NewBox() && Boxes->Contains(_target))// new box available, target found
        {
            _targetSeenCounter ++;
            if (_targetSeenCounter > 10) //sees the object more than 3 times
            {
                _target = -1; // reset target
                _targetSeenCounter = 0; //reset counter
                return 0; //object found, return to previous state
            }
        }
        //TODO: Add timer, quit with error code if object not found
        MotionPub.publish(this->MotionMessage); //tell motion package to enter search pattern (probably spin in place)
        ros::spinOnce();
        this->SleepRate.sleep();
    }
}

