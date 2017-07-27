#!bin/bash
sleep 15
roslaunch objective_executer mavros.launch &\
sleep 15
roslaunch objective_executer movement_package.launch &\
roslaunch objective_executer objective_executer.launch
