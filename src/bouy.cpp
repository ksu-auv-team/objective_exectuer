/**
bouy.h
Purpose: source file for bouy state

@author vnguye34
@version 0.0.1
*/
#include "bouy.h"

using namespace state;

Bouy::Bouy(ros::Publisher &motionPub, boxes::Boxes& boxes)
     : State::State(&motionPub, &boxes)
{
    MotionMessage[0] = 0;
    MotionMessage[1] = 0;
    MotionMessage[2] = 1;
    MotionMessage[3] = 0;
    MotionMessage[4] = 1;
}

int Bouy::Execute()
{
    float start(ros::Time::now().toSec());
    while(ros::ok())
    {
		switch(OBJECTIVE_DEFINITIONS)
		{
			case(Boxes->NewBox() && Boxes->Contains(RED_BOUY)):
			{
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
			}
			case(Boxes->NewBox() && Boxes->Contains(GREEN_BOUY)):
			{
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
			}
			case(Boxes->NewBox() && Boxes->Contains(YELLOW_BOUY)):
			{
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
			}
        }
		}
        ros::spinOnce();
        SleepRate.sleep();
    }
}

void Bouy::UpdateTarget()
{
    std::vector target(Boxes->GetNearest(OBJECTIVE_DEFINITIONS));
    this->MotionMessage[0] = target[0];
    this->MotionMessage[1] = target[1];
}