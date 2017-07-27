/**
start_gate.h
Purpose: source file for start_gate state

@author shadySource
@version 0.0.1
*/
#include "start_gate.h"

using namespace state;

StartGate::StartGate(ros::Publisher *motionPub, boxes::Boxes *boxes)
     : State::State(motionPub, boxes), TIMEOUT(30)
{
    _startTime = ros::Time::now().toSec();
    while (round(_startTime) == 0)
    {
        ros::Duration(0.5).sleep();
        _startTime = ros::Time::now().toSec();
    }
    // MotionMsg.data = {0, 0, 0.762, .5, 0};
    // MotionMsg.data[0] = 0;// mode 0
    // MotionMsg.data[1] = 0;// x
    // MotionMsg.data[2] = 0.762; //depth, 2.5ft/.76m down
    // MotionMsg.data[3] = .2; // forward motion, 1 is full forward, -1 is full reverse
    // MotionMsg.data[4] = 0; //lateral throttle, same as ablve
}

int StartGate::Execute()
{
    while(ros::ok())
    {
        // if(Boxes->NewBox() && Boxes->Contains(START_GATE))
        // {
        //     this->UpdateTarget();
        //     MotionPub->publish(this->MotionMsg);
        // }
        this->UpdateTarget();
        MotionPub->publish(this->MotionMsg);
        ROS_INFO("%f", MotionMsg.data[0]);
        ros::spinOnce();
        SleepRate.sleep();
    }
}

void StartGate::UpdateTarget()
{
    // std::vector<float> target(Boxes->GetNearest(START_GATE));
    // this->MotionMsg.data[1] = target[0]; //x
    // // this->MotionMsg[1] = target[1]; //y
    MotionMsg.data.clear();
    MotionMsg.data.push_back(5);
    MotionMsg.data.push_back(0.762);//full speed ahead, 2.5ft down
    float time = ros::Time::now().toSec();
    if (round(time) !=0)
    if ((time - _startTime) > TIMEOUT)
    {
        MotionMsg.data.clear();
        MotionMsg.data.push_back(0);
    }
}