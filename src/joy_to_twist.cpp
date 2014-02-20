#include "joy_to_twist/joy_to_twist.hpp"

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

namespace joy_to_twist
{
joy_to_twist::joy_to_twist( const ros::NodeHandle &_nh, const ros::NodeHandle &_nh_priv ) :
	nh( _nh ),
	nh_priv( _nh_priv ),
	pub_callback( boost::bind(&joy_to_twist::pub_cb, this) ),
	linear_scale( 0.20 ),
	angular_scale( M_PI / 4 )
{
}

joy_to_twist::~joy_to_twist( )
{
}

bool joy_to_twist::start( )
{
	if( !( twist_pub = nh.advertise<geometry_msgs::Twist>( "cmd_vel", 1, pub_callback, pub_callback, ros::VoidConstPtr( ), false ) ) )
		return false;

	pub_cb( );

	return true;
}

void joy_to_twist::stop( )
{
	if( joy_sub )
		joy_sub.shutdown( );

	if( twist_pub )
		twist_pub.shutdown( );
}

bool joy_to_twist::stat( )
{
	return twist_pub;
}

void joy_to_twist::pub_cb( )
{
	if( twist_pub.getNumSubscribers( ) > 0 )
	{
		if( !joy_sub && !( joy_sub = nh.subscribe( "joy", 1, &joy_to_twist::joy_cb, this ) ) )
			ROS_ERROR( "Failed to start twist subscription" );
	}
	else if( joy_sub )
		joy_sub.shutdown( );
}

void joy_to_twist::joy_cb( const sensor_msgs::JoyConstPtr &msg )
{
	geometry_msgs::TwistPtr new_msg( new geometry_msgs::Twist );

	new_msg->linear.y = msg->axes[0] * linear_scale;
	new_msg->linear.x = msg->axes[1] * linear_scale;
	new_msg->angular.z = msg->axes[2] * angular_scale;
	new_msg->linear.z = msg->axes[3] * linear_scale;

	twist_pub.publish( new_msg );
}

void joy_to_twist::set_linear_scale( const float _linear_scale )
{
	linear_scale = _linear_scale;
}

void joy_to_twist::set_angular_scale( const float _angular_scale )
{
	angular_scale = _angular_scale;
}

}
