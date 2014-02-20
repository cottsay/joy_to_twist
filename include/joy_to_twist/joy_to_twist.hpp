#ifndef _joy_to_twist_hpp
#define _joy_to_twist_hpp

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

namespace joy_to_twist
{
class joy_to_twist
{
public:
	joy_to_twist( const ros::NodeHandle &_nh = ros::NodeHandle( ), const ros::NodeHandle &_nh_priv = ros::NodeHandle( "~" ) );
	~joy_to_twist( );

	bool start( );
	void stop( );
	bool stat( );
	void set_linear_scale( const float _linear_scale );
	void set_angular_scale( const float _angular_scale );

private:
	ros::NodeHandle nh;
	ros::NodeHandle nh_priv;
	ros::Subscriber joy_sub;
	ros::Publisher twist_pub;
	const ros::SubscriberStatusCallback pub_callback;

	float linear_scale;
	float angular_scale;

	void pub_cb( );
	void joy_cb( const sensor_msgs::JoyConstPtr &msg );
};
}

#endif /* _joy_to_twist_hpp */
