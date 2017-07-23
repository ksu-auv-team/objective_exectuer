/**
boxes.cpp
Purpose: source file for Boxes object

@author shadySource
@version 0.0.1
*/
#include "boxes.h"

using namespace boxes;

Boxes::Boxes()
    : _newBoxes(false), _numBoxes(0)
{
    _boxesSub = _nh.Subscribe("yolo/first/boxes", 10, &Boxes::boxesCallback, this);
    _boxes = new float[100][8];
}

Boxes::~Boxes()
{
    delete _boxes;
}

void Boxes::BoxesCallback(const std_msgs::Float32MultiArray &msg)
{
    _numFirstBoxes = msg.layout.dim[0].shape;
    for (int i(0); i < _numFirstBoxes; i++)
    {
        _boxes[i][0] = msg.data[i*6]; // class
        _boxes[i][1] = msg.data[i*6+5]; //confidence
        _boxes[i][2] = msg.data[i*6+1]; //ymin, 0 to 1   
        _boxes[i][3] = msg.data[i*6+2]; //xmin
        _boxes[i][4] = msg.data[i*6+3]; //yMax
        _boxes[i][5] = msg.data[i*6+4]; //xMax
        _boxes[i][6] = (_boxes[i][3] + _boxes[i][5])/2 - 0.5; //xCenter, -.5 to .5
        _boxes[i][7] = (_boxes[i][2] + _boxes[i][4])/2 - 0.5; //yCenter, -.5 to .5
    }
    _newBoxes = true;
}

bool Boxes::NewBox()
{
    _newBoxes = False;
    return _newBoxes;
}

bool Boxes::Contains(int object)
{
    for (int i(0); i < _numBoxes; i++)
    {
        if (round(_boxes[i][0]) == object)
        {
            return true;
        }
    }

    return false;
}

float * GetNearest(int object)
{
    int idx;
    int err(1);
    for (int i(0); i < _numBoxes; i++)
    {
        if (round(_boxes[i][0]) == object &&
        sqrt(pow(_boxes[i][6], 2) + pow(_boxes[i][7], 2)) < err)
        {
            idx = i;
        }
    }

    if (err < 1)
    {
        return &(_boxes[idx][6]);
    }
    else
    {
        return &NULL;
    }
}