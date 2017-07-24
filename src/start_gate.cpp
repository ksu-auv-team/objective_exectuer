/**
start_gate.h
Purpose: source file for start_gate state

@author shadySource
@version 0.0.1
*/
#include "start_gate.h"

using namespace state;

StartGate::StartGate(ros::Publisher &motionPub, boxes::Boxes& boxes)
     : State::State(&motionPub, &boxes)
{
    MotionMessage[0] = 0;// mode 0
    MotionMessage[1] = 0;// x
    MotionMessage[2] = 0.762; //depth, 2.5ft/.76m down
    MotionMessage[3] = .2; // forward motion, 1 is full forward, -1 is full reverse
    MotionMessage[4] = 0; //lateral throttle, same as ablve
}

int StartGate::Execute()
{
    float start(ros::Time::now().toSec());
    while(ros::ok())
    {
        if(Boxes->NewBox() && Boxes->Contains(START_GATE))
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

void StartGate::UpdateTarget()
{
    std::vector target(Boxes->GetNearest(START_GATE));
    this->MotionMessage[0] = target[0]; //x
    // this->MotionMessage[1] = target[1]; //y
}