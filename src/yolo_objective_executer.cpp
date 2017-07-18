#include <iostream>
#include <string>
#include <time.h>
#include “ros/ros.h”
#include “ros/console.h”
#include <std_msgs>
#include <math.h>
#include "std_msgs/Int8"
#include "std_msgs/String"
#include "std_msgs/Int32MultiArray.h"
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <vector>
#include <array>
#include <mavros_msgs/OverrideRCIn.h>
#include <mavros_msgs/Mavlink.h>
#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

using namespace std;

//callback function to grab string data and put it into our own array. each array will have 6 values
//[object type]
//[top y coordinate]
//[left x coordinate]
//[bottom y coordinate]
//[right x coordinate]
//[confidence value, %]
//read length of array, vector.length
//each multiple of 6 is one detected object
//6 values = 1 object
//12 values = 2 objects
//...
//YOLO input data

vector<array<int, 6>> yolo_data_input;
vector<array<int, 2>>object_centroid;

//PI_loop status of object
//This is a Bool, either sub has reached object or it is still on the way
bool object_status;

//This is the data being published to pi_data
//It is in the format:
//[x, y, dist_to_object, camera_num]
//
//x, y is coordinates of the centroid of detected object
//
//distance is in [insert unit here]
//
//cam_num:
//0 = front facing camera
//1 = bottom facing camera
//
//NOTE:
//If desired position is to pass through object, e.g. Start gate/Channel
//distance to stop from object = 0
int pi_loop_data[4];

//This determines current case for switch statement
int objective;

//This determines the currently focused object
int detected_object;

//This determines which set of objects are allowed to be accessed
int detected_object_current_set;

//The SMACH State Manager is looking for any string rather than a specific set. When a string is published, a bool is changed to 1 and the state is considered finished

string_complete = 'done bitch';

//write a series of functions to find: centroids, distance from object, distance required to be from object, current camera mode
//put outputs into a 1x5 array
double centroidFunc1(//array[6][numVec]])
{
 double xBar, yBar;
 double* centroids = new double[2][numVec];
 for (int i = 0; i<numVec; ++i)
 {
  xBar = [4][i] - [2][i];
  yBar = [1][i] - [3][i];
  centroids[0][i] = xBar;
  centroids[1][i] = yBar;
 }
 return centroids;
}

float distance_from_object()
{
 //Jacques write this
}

//write function to define all objects and assign them to an int

void yolo_array_callback(const std_msgs::Int32MultiArray::ConstPtr& msg)
{
 Object_centroid = { 0,0 };
 //note for every 6 = 1 detected object
 array_length = msg.data.size();
 number_boxes = array_length / 6;
 for (int row = 0; row < number_boxes; row++)
 {
  for (int column = 0; column < 6; column++)
  {
   yolo_data_input[row][column] = msg.data[6 * row + column];
  }
 }
 object_centroid.resize[yolo_data_input.size()]
  for (int j = 0; j<yolo_data_input.size(); j++)
  {
   object_centroid[j].push_back({ round((float)(yolo_data_input[j][2] + yolo_data_input[j][4]) / 2),round((float)(yolo_data_input[j][1] + yolo_data_input[j][3]) / 2) });
  }
}

int object_decider()
{
  //hardcode list of detected objects here
  //
  //0 = start gate

  //1 = path_marker

  //2 = red bouy
  //3 = green bouy
  //4 = yellow bouy

  //5 = channel

  //6 = dropper_bin
  //7 = dropper_lid
  //8 = dropper_image_einstein
  //9 = dropper_image_hartung

  //10 = squid_tentacle
  //11 = squid_tentacle_hole_small
  //12 = squid_tentacle_hole_large
  //13 = squid_main_hole_small
  //14 = squid_main_hole_large
  //15 = seaweed
  
  //16 = pinger
  //17 = sample_red
  //18 = sample_green
  //19 = sample_orange
  //20 = sample_blue
  //21 = table_red
  //22 = table_green
  //23 = table_orange
  //24 = table_blue

  switch(detected_object_current_set
  {
    case 1: //start gate
    {
      if (detected_object = 0)
      {

      }

      else
      {

      }
    }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10;
  })


}

void yolo_data_cam_position_callback(const std_msgs::Int8& msg)
{
  objective = msg.data;
}

void pi_loop_objective_verifier_callback(const std_msgs : Bool::ConstPtr& msg)
{
 object_status = msg.data;string channel_string_recieved = 'channel_complete';
}

void objective_callback(const std_msgs::Int8& msg)
{
 objective = msg.data;
}

int main(int argc, char **argv)
{
 // ros node objective_executer
 ros::init(argc, argv, "objective_executer"); //declare ros node name here
 ros::NodeHandle nh;

 // subscriber listening for data from yolo
 ros::Subscriber yolo_data_subscriber = nh.subscribe("/yolo", 10, yolo_array_callback);

 //recieve data to know which camera is input for current task
 ros::Subscriber yolo_data_cam_position_subscriber = nh.subscribe("/yolo/commands/camera_num", 10, yolo_data_cam_position_callback);

 // receive data from pi_loop, if sub has passed through object yet
 ros::Subscriber pi_loop_obejctive_verifier = nh.subscribe("pi_loop/[name of publisher topic]", 10, pi_loop_objective_verifier_callback);

 //recieve data to translate string into int to decide current state of machine in executer
 ros::Subscriber objective_decider = nh.subscriber("/switch_decider/decider", 10, objective_callback);

 // set up publisher to pi_loop to send
 ros::Publisher pi_loop_sender = nh.advertise < std_msgs::Int32MultiArray("pi_loop/[name of topic to receive data]", 10);
  
  //Switch statement is set to whatever is recieved on the subscriber object from Switch_Decider
  switch (objective) 
  {
  case 1: //start_gate
  {
    //define current object set
    detected_object_current_set = 1;
   //ros::Publisher Object [name of function] = [node handler].advertise[declare it]<[library::data type("name of ros topic", number of how many messages you //want to //keep on hand_;
   //set up publisher for data back to smach when complete
   ros::Publisher start_gate_objective_data_sender = nh.advertise < std_msgs::String("sub_ai_state_manager/start_gate_smach_receiver", 10);
   ros::Rate loop_rate(10); //define publish rate at 10hz

   while (ros::ok())
   {
    if (object_status == TRUE)
    {
     //publish string
     start_gate_objective_data_sender.publish(string_complete);
     ros::spinOnce();
    }
    else
    {
     //publish x, y, distance needed to travel to object, distance at when to stop moving - enter 0 if want to pass through
     //send array of values [x, y, distance from object, distance from object on when to stop, current camera mode]
     pi_loop_sender.publish(pi_loop_data); 
     ros::spinOnce();
    }
   }
  }
  case 2: //path_1
  {
    //define current object set
    detected_object_current_set = 2;
   //set up publisher to state machine
   ros::Publisher path_1_obejctive_data_sender = nh.advertise < std_msgs::String("sub_ai_state_manager/path_1_smach_receiver", 10);
   ros::Rate loop_rate(10);
   while (ros::ok())
   {
    if (“object_status == TRUE”)
    {
      //publish string to SMACH to end state
     path_1_objective_data_sender.publish(string_complete);
     ros::spinOnce();
    }
    else
    {
      //send information to PID
     pi_loop_sender.publish(pi_loop_data);
     ros::spinOnce();
    }
   }
  }
  case 3://buoy_red
  {
    //define current object set
    detected_object_current_set = 3;
   ros::Publisher buoy_red = nh.advertise < std_msgs::String("sub_ai_state_manager/buoy_red_smach_receiver", 10);
   ros::Rate loop_rate(10);
   int buoy = 0;
   while (ros::ok())
   {
    if (buoy = 2)
    {
     buoy_red.publish(COMPLETE);
    }
    else
    {
     buoy_red.publish(INCOMPLETE);
    }
    buoy_red.publish(SOMETHING);
    buoy = buoy + 1;
    {
     if (buoy == 0) {
      //get location data?
      buoy_red.publish(SOMETHING);
      buoy = buoy + 1;
     }
     else if (buoy == 1) {
      //get location data?
      buoy_red.publish(SOMETHING ELSE);
      buoy = buoy + 1;
     }
    }
   }
  }
  case 4: //path_2
  {
    //define current object set
    detected_object_current_set = 4;
   //set up publisher to state machine
   ros::Publisher path_2_obejctive_data_sender = nh.advertise < std_msgs::String("sub_ai_state_manager/path_2_smach_receiver", 10);
   ros::Rate loop_rate(10);
   while (ros::ok())
   {
     detected_object_current_set = 4;
    if (“object_status == TRUE”)
    {
      //publish string to SMACH to end state
     path_2_objective_data_sender.publish(string_complete);
     ros::spinOnce();
    }
    else
    {
      //send information to PID
     pi_loop_sender.publish(pi_loop_data);
     ros::spinOnce();
    }
   }
  }
  case 5://channel
  {
    //define current object set
    detected_object_current_set = 5;
    //set up publisher to SMACH
   ros::Publisher channel_obejctive_data_sender = nh.advertise < std_msgs::String("sub_ai_state_manager/channel_smach_receiver", 10);
   ros::Rate loop_rate(10);
  //set MAVROS to Manual Mode
   mavros_msgs::SetMode offb_set_mode;
   offb_set_mode.request.custom_mode = "MANUAL";

   while (ros::ok())
   {
    if (object_status == true)
    {
     pi_loop_sender.publish(pi_loop_data);
     

    }
    else if
    {
     
     ros::spinOnce();
    }
    else
    {
      channel_objective_data_sender.publish(string_complete);
     //change mode back to stabilize
     mavros_msgs::SetMode offb_set_mode;
     offb_set_mode.request.custom_mode = "STABILIZE";
     ros::spinOnce();
    }
    }
   }
  }
  case 6: //hydrophone_1
  {
    //define current object set
    detected_object_current_set = 6;
  }
  case 7: //dropper
  {
    //define current object set
    detected_object_current_set = 7;
  }
  case 8: //torpedo
  {
    //define current object set
    detected_object_current_set = 8;
  }
  case 9: //hydrophone_2
  {
    //define current object set
    detected_object_current_set = 9;
  }
  case 10: //samples
  {
    //define current object set
    detected_object_current_set = 10;
  }

  }
  return 0;
}

