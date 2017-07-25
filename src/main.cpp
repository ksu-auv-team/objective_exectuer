/**
main.cpp
Purpose: main function to run the state machine for objective executions

@version 0.0.1
*/

#include <ros/ros.h>
#include <ros/console.h>
#include "boxes.h"
#include "state.h"
#include "search.h"
#include "start_gate.h"

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "objective_executor");

    ros::NodeHandle nh;
    ros::Publisher motionPub = nh.advertise<std_msgs::Float32MultiArray>("chatter", 1000);

    boxes::Boxes boxes;

    state::Search searchState(motionPub, boxes);
    ROS_INFO("Node Start.");

    //auto startGate = new StartGate::StartGate();
}