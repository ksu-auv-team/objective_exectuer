/**
state.cpp
Purpose: source file for parent state class

@author shadySource
@version 0.0.1
*/
#include "state.h"

using namespace state;

State::State(ros::Publisher *motionPub, boxes::Boxes *boxes)
    : SleepRate(20)
{
    Boxes = boxes;

    MotionPub = motionPub;

}

// int State::Execute()
// {
//     while(ros::ok())
//     {
//         ROS_INFO("This is supposed to be an abstract class");
//     }
// }