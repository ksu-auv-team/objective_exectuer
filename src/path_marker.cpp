/**
path_marker.h
Purpose: source file for start_gate state

@author DeusExMachina96
@version 0.0.1
*/
#include "path_marker.h"

using namespace state;

PathMarker::PathMarker(ros::Publisher &motionPub, boxes::Boxes& boxes)
     : State::State(&motionPub, &boxes)
{
    MotionMessage[0] = 0;
    MotionMessage[1] = 0;
    MotionMessage[2] = 1;
    MotionMessage[3] = 0;
    MotionMessage[4] = 1;
}
 
void PathMarker::Execute()
{
    float start(ros::Time::now().toSec());
    while(ros::ok())
    {
        if(Boxes->NewBox() && Boxes->Contains(PATH_MARKER))
        {
            this->UpdateTarget();
            MotionPub.publish(this->MotionMessage);
        }
        if (ros::Time::now().toSec() - start > 30)
        {
            break; //TODO enter disarm state?
        }
        ros::spinOnce();
        SleepRate.sleep();
    }
}

void PathMarker::UpdateTarget()
{
    std::vector target(Boxes->GetNearest(PATH_MARKER));
    this->MotionMessage[0] = target[0];
    this->MotionMessage[1] = target[1];
}