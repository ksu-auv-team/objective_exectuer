/**
bouy.h
Purpose: source file for dropper_finder

@author vnguye34
@version 0.0.1
*/
#include "dropper_finder.h"

using namespace state;

Dropper_finder::Dropper_finder(ros::Publisher &motionPub, boxes::Boxes& boxes)
     : State::State(&motionPub, &boxes), _target(DROPPER_BIN)
{
    MotionMessage[0] = 3; //mode 3, dropper movement
	MotionMessage[1] = 0; //x 
	MotionMessage[2] = 0; //y 
    MotionMessage[3] = .5; //forward thrust, -1, 1, forward backward
    MotionMessage[4] = 0; //lateral thrust, -1, 1, rolling side to side
}

int Dropper::Execute()
{
    float start(ros::Time::now().toSec());
	float lastSeen(-1);
	
    while(ros::ok())
    {
		switch(_target)
		{
			case DROPPER_BIN:
			if (Boxes->NewBox() && Boxes->Contains(DROPPER_BIN)):
			{
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
				lastSeen = ros::Time::now().toSec();
			}
			else if (lastSeen > 5)
			{
				//write state transition to dropper
			}
			break;
        }
		}
        ros::spinOnce();
        SleepRate.sleep();
    }
}

void Dropper::UpdateTarget()
{
    std::vector target(Boxes->GetNearest(_target));
    this->MotionMessage[0] = target[0];
}