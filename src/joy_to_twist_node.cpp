#include "joy_to_twist/joy_to_twist.hpp"

int main (int argc, char **argv)
{
	ros::init(argc, argv, "joy_to_twist");

	ros::NodeHandle nh;
	ros::NodeHandle nh_priv( "~" );

	joy_to_twist::joy_to_twist joy_to_twist( nh, nh_priv );

	joy_to_twist.start();

	ros::spin();

	return 0;
}
