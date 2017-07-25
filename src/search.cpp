/**
search.cpp
Purpose: source file for search state

@author shadySource
@version 0.0.1
*/
#include "search.h"

using namespace state;

Search::Search(ros::Publisher& motionPub, boxes::Boxes& boxes)
    : State(motionPub, boxes), _target(-1), _targetSeenCounter(0)
{
    MotionMsg.data[0] = 4;// mode 0
    MotionMsg.data[1] = .3;// yaw
    MotionMsg.data[2] = 0; //depth, 2.5ft/.76m down
    MotionMsg.data[3] = 0; // forward motion, 1 is full forward, -1 is full reverse
    MotionMsg.data[4] = 0; //lateral throttle, same as ablve
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
        MotionPub->publish(this->MotionMsg); //tell motion package to enter search pattern (probably spin in place)
        ros::spinOnce();
        this->SleepRate.sleep();
    }
}

void Search::SetTarget(int target)
{
    _target = target;
}
