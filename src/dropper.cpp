/**
bouy.h
Purpose: source file for dropper

@author vnguye34
@version 0.0.1
*/
#include "dropper.h"

using namespace state;

Dropper::Dropper(ros::Publisher &motionPub, boxes::Boxes& boxes)
     : State::State(&motionPub, &boxes), _target(DROPPER_HANDLE)
{
    MotionMessage[0] = 4; //mode 4, dropper movement
	MotionMessage[1] = 0; //x bottom cam
	MotionMessage[2] = 0; //y bottom cam
    MotionMessage[3] = 0; //forward thrust, -1, 1, forward backward
    MotionMessage[4] = 0; //lateral thrust, -1, 1, rolling side to side
}

int Dropper::Execute()
{
    float start(ros::Time::now().toSec());
	float lastSeen(-1);
	
    while(ros::ok())
    {
				//find box for dropper lid
				//go until center of camera = centroid of dropper lid
				//move backward offset to grabber arm + error value
				//send signal to servo to open grabber arm
				//move forward to position of grabber arm + error value
				//send signal to servo to close grabber arm
				//move sub forward until bottom camera does not see dropper lid
				//send signal to servo to let go of lid
				//switch mode into depth_hold and tilt sub to let lid dropper
				//move sub backwards until uncovered dropper bin is back in view of bottom facing camera
				//move offset to uncovered bin
				//send signal to servo to drop 2 droppers
				//end state
			if (Boxes->NewBox() && Boxes->Contains(DROPPER_HANDLE):
			{
				//idenify target and move towards centroid 
				this->UpdateTarget();
				MotionPub.publish(this->MotionMessage);
				
			}
			else if (lastSeen > 10)
			{
				_target = GREEN_BUOY;
			}
        ros::spinOnce();
        SleepRate.sleep();
    }
}

void Bouy::UpdateTarget()
{
    std::vector target(Boxes->GetNearest(_target));
    this->MotionMessage[0] = target[0]; //x
	this->MotionMessage[1] = target[1]; //y
}