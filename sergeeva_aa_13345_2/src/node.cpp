#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
  
geometry_msgs::Twist msg_foots;

void speed_ms_to_foots(const geometry_msgs::Twist& msg)
{
  double speed_ms = msg.linear.x;
  msg_foots.linear.x = 3.28084*speed_ms;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("speed_out", 1000);
  ros::Subscriber sub = n.subscribe("speed_in", 1000, speed_ms_to_foots);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    chatter_pub.publish(msg_foots);
    ros::spinOnce();
    loop_rate.sleep();
  }
}