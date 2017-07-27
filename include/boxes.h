/**
boxes.h
Purpose: class to manage active boxes

@author shadySource
@version 0.0.1
*/
#ifndef BOXES_DEF
#define BOXES_DEF

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <vector>
#include <math.h>

namespace boxes
{

class Boxes
{
    private:
        //@var max number of boxes
        const int MAX_BOXES;

        //@var nodehandle for boxes subscriber
        ros::NodeHandle _nh;

        //@var subscriber to yolo boxes for first cam
        ros::Subscriber _boxesSub;

        //@var boxes holding data structure
        float ** _boxes;
        int _numBoxes;
        bool _newBoxes;

        /*
        Callback for the first boxes message
        */
        void BoxesCallback(const std_msgs::Float32MultiArray &msg);


    public:
        /*
        find if boxes contains a certain object

        @param object: int of object to search for
        @param camera: 1 for first camera, 2 for second camera

        @return bool true/false where object contained
        */
        bool Contains(int object);

        /*
        find if boxes contains new information

        @param camera: 1 for first camera, 2 for second camera

        @return bool true/false where object contained
        */
        bool NewBox();

        /**
        finds a box of a certain type closest to the center.

        @param object: int object to find the  best box for

        @return vector of center x, center y coordinates of closest box of type <object>.
        returns empty if not found. 
        */
        std::vector<float> GetNearest(int object);

        /**
        prints all current boxes with ros_info
        */
        void PrintBoxes();


    Boxes();

    ~Boxes();
};

}

#endif