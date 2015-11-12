#include "MyRobot.hpp"
#include "controller_manager/controller_manager.h"
#include "hardware_interface/actuator_state_interface.h"

#include <ros/callback_queue.h>
int main(int argc, char** argv)
{
  ros::init(argc, argv, "test_iface_node");
  ros::NodeHandle nh;
  ros::CallbackQueue queue;
  nh.setCallbackQueue(&queue);


  MyRobot robot;
  controller_manager::ControllerManager cm(&robot,nh);


  ros::AsyncSpinner spinner(4, &queue);
  spinner.start();

  ros::Time ts = ros::Time::now();

  while (ros::ok())
  {
     ros::Duration d = ts - ros::Time::now();
     ts = ros::Time::now();
     robot.read();
     cm.update(ts, d);
     robot.write();
     usleep(500000);
  }

  spinner.stop();

  return 0;
}
