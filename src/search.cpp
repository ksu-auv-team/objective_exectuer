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
    int targetSeenCounter = 0;
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
            targetSeenCounter ++;
            if (_targetSeenCounter > 3) //sees the object more than 3 times
            {
                _target = -1; // reset target
                return 0; //object found, return to previous state
            }
        }
        //TODO: Add timer, quit with error code if object not found
        MotionPub.publish(this->MotionMessage); //tell motion package to enter search pattern (probably spin in place)
        ros::spinOnce();
        this->SleepRate.sleep();
    }
}

