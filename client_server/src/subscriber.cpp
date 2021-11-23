#include "ros/ros.h"
#include "my_service/my_step.h"
#include <std_msgs/String.h>
#include <iostream>
#include <string>

ros::Subscriber sub;
ros::Publisher pub;

std::string win_route (18, 'a');
int plate = 0;
std::string output = "";

void handler(const std_msgs::String message)
{  
	if (plate == 17) 
	{
		ROS_INFO ("Congratulations, you won");
		ros::shutdown();
	}
	output += message.data; 
	ROS_INFO ("%s",output.c_str());
}

bool recognition(my_service::my_step::Request &req,
       		 my_service::my_step::Response &res)
{
	if ((req.step != "r") && (req.step != "l"))
	{
		return false;
	}
	if (req.step[0] == win_route[plate])
	{
		res.result = "move next";
		pub.publish(req);
	}
	else
	{ 
		res.result = "dead";
		ros::shutdown(); 
	}
	plate ++;
	return true;
}																

int main(int argc, char **argv)
{
	ros::init(argc, argv,"glass_bridge_server");
	ros::NodeHandle n;
	ros::ServiceServer my_service=n.advertiseService("glass_bridge",recognition);
	pub = n.advertise<std_msgs::String>("my_topic",100);
	sub = n.subscribe ("my_topic", 100, handler);

	srand(time(NULL));

	for (int count=0; count < 18; count ++) 
	{
		int indicator = rand() % 2;
		if (indicator == 0)
		{ 
			win_route[count] = 'l';
		}
		else
		{
			win_route[count] = 'r'; 
		}  
	}  
	ROS_INFO ("True_road: %s",win_route.c_str());   
	ros::spin();
	return 0;
}
