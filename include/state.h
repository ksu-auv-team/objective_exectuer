/**
state.h
Purpose: parent class for all states.

@author ShadySource
@version 0.0.1
*/
#ifndef STATE_DEF
#define STATE_DEF

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include "boxes.h"

namespace state
{

class State
{
    public:
        //@var Boxes - boxes object to organize currently seen boxes
        boxes::Boxes *Boxes;

        //@var MotionPub - publisher to be shared byall states
        ros::Publisher *MotionPub

        //@var MotionMsg - motion message to be used, generated per state
        ros::Float32MultiArray MotionMsg;

        //@var SleepRate - sleep rate
        ros::Rate SleepRate;

        /**
        Loop method for child classes. All states must execute in some manner.
        */
        virtual int Execute() = 0;

    /**
    constructor for base state object

    @param motionPub - publisher for motion package
    @param boxes - boxes object to store all yolo boxes
    */
    State(ros::Publisher &motionPub, boxes::Boxes& boxes);
  
};

}


#endif