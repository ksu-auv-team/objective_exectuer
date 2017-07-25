/**
bouy.h
Purpose: source file for bouy state

@author vnguye34
@version 0.0.1
*/
#include "bouy.h"

using namespace state;

Bouy::Bouy(ros::Publisher &motionPub, boxes::Boxes& boxes)
     : State::State(&motionPub, &boxes), _target(RED_BUOY)
{
    MotionMessage[0] = 1; //mode 1, bouy action
    MotionMessage[1] = 0; //x
    MotionMessage[2] = 0; //y
    MotionMessage[3] = .5; //forward thrust, -1, 1, forward backward
    MotionMessage[4] = 0; //lateral thrust, -1, 1, rolling side to side
}

int Bouy::Execute()
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