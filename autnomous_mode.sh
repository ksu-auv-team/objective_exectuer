#!bin/bash
#sleep 30
roslaunch mavros apm2.launch
roslauch sub_vision sub_vision_recording.launch
rosrun objective_executer main