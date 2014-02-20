#ifndef _joy_to_twist_nodelet_hpp
#define _joy_to_twist_nodelet_hpp

#include "joy_to_twist/joy_to_twist.hpp"

#include <nodelet/nodelet.h>

namespace joy_to_twist
{
	class joy_to_twist_nodelet : public nodelet::Nodelet
	{
	public:
		joy_to_twist_nodelet( const bool _autostart = true );
		~joy_to_twist_nodelet( );
		bool start( );
		void stop( );
		bool stat( );
		void set_linear_scale( const float _linear_scale );
		void set_angular_scale( const float _angular_scale );

	private:
		virtual void onInit( );
		joy_to_twist *controller;
		const bool autostart;
	};
}

#endif /* _joy_to_twist_nodelet_hpp */
