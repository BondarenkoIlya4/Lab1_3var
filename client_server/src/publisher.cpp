#include "ros/ros.h"
#include "my_service/my_step.h"
#include <std_msgs/String.h>
#include <iostream>
#include <string>


ros::Subscriber sub;
ros::Publisher pub;

int count = 0;

int main(int argc, char **argv)
{
  ros::init(argc, argv,"glass_bridge_publisher");
  ros::NodeHandle n;
  ros::ServiceClient client=n.serviceClient<my_service::my_step>("glass_bridge"); 
  pub = n.advertise<std_msgs::String>("my_topic",100);

  my_service::my_step srv;

  std::string my_route[] = {"r","r","r","l","r","r","r","r","r","r","r","r","r","r","r","r","r","r"};

  while(ros::ok())
  {
    srv.request.step = my_route[count];
    client.call(srv);

    if (srv.response.result == "dead")
    {   
    ros::shutdown();
    }

    else if (srv.response.result == "move next")
    { 
      count ++;
    }

    if (count > 17)
    {
    count=0;
    }
  }
}
