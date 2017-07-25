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
    _boxesSub = _nh.subscribe("yolo/first/boxes", 10, &Boxes::BoxesCallback, this);
    _boxes = new float * [100];
    for (int i = 0; i < 100; i++)
    {
        _boxes[i] = new float[8];
    }
}

Boxes::~Boxes()
{
    delete _boxes;
}

void Boxes::BoxesCallback(const std_msgs::Float32MultiArray &msg)
{
    _numFirstBoxes = msg.layout.dim[0].size;
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
    _newBoxes = false;
    return _newBoxes;
}

bool Boxes::Contains(int object)
{
    for (int i(0); i < this->_numBoxes; i++)
    {
        if (round(_boxes[i][0]) == object)
        {
            return true;
        }
    }

    return false;
}

std::vector<float> Boxes::GetNearest(int object)
{
    int idx;
    float err(100);
    for (int i(0); i < _numBoxes; i++)//simple search
    {
        if (round(_boxes[i][0]) == object &&
        sqrt(pow(_boxes[i][6], 2) + pow(_boxes[i][7], 2)) < err) // min error
        {
            idx = i;
        }
    }

    if (err < 100)
    {
        std::vector<float> centers;
        centers[0] = _boxes[idx][6]; //x
        centers[1] = _boxes[idx][7]; //y
        return centers;
    }
    else
    {
        std::vector<float> empty;
        return empty;
    }
}