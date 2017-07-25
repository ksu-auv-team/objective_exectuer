/**
bouy.h
Purpose: source file for dropper

@author vnguye34
@version 0.0.1
*/
#include "dropper.h"

using namespace state;

Dropper::Dropper(ros::Publisher &motionPub, boxes::Boxes& boxes)
     : State::State(&motionPub, &boxes), _target(DROPPER_BIN)
{
    MotionMessage[3] = 1; //mode 3, dropper movement
    MotionMessage[1] = 0; //x front cam
    MotionMessage[2] = 0; //y front cam
	MotionMessage[3] = 0; //x bottom cam
	MotionMessage[4] = 0; //y bottom cam
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
			case RED_BUOY:
			if (Boxes->NewBox() && Boxes->Contains(RED_BOUY)):
			{
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
				lastSeen = ros::Time::now().toSec();
			}
			else if (lastSeen > 10)
			{
				_target = GREEN_BUOY;
			}
			break;
			
			case GREEN_BOUY:
			lastSeen = -1;
			if(Boxes->NewBox() && Boxes->Contains(GREEN_BOUY)):
			{
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
				lastSeen = ros::Time::now().toSec();
			}
			else if (lastSeen > 10)
			{
				_target = YELLOW_BOUY;
			}
			break;
			
			case YELLOW_BOUY:
			lastSeen = -1;
			if(Boxes->NewBox() && Boxes->Contains(YELLOW_BOUY)):
			{
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
				lastSeen = ros::Time::now().toSec();
			}
			else if (lastSeen > 10)
			{
				_target = PATH_MARKER;	
			}
			break;
        }
		}
        ros::spinOnce();
        SleepRate.sleep();
    }
}

void Bouy::UpdateTarget()
{
    std::vector target(Boxes->GetNearest(_target));
    this->MotionMessage[0] = target[0];
}