/************************************************************************************
This source file is part of the Theora Video Playback Library
For latest info, see http://libtheoraplayer.googlecode.com
*************************************************************************************
Copyright (c) 2008-2014 Kresimir Spes (kspes@cateia.com)
This program is free software; you can redistribute it and/or modify it under
the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
*************************************************************************************/

#ifndef THEORA_TIMER_H
#define THEORA_TIMER_H

#include "TheoraExport.h"

/**
	This is a Timer object, it is used to control the playback of a TheoraVideoClip.

	You can inherit this class and make a timer that eg. plays twice as fast,
	or playbacks an audio track and uses it's time offset for syncronizing Video etc.
 */
class TheoraPlayerExport TheoraTimer
{
public:
	TheoraTimer();
	virtual ~TheoraTimer();

	virtual float getTime();

	//! return the update speed 1.0 is the default
	virtual float getSpeed();

	virtual bool isPaused();
	/**
		\brief advance the time.

		If you're using another synronization system, eg. an audio track,
		then you can ignore this call or use it to perform other updates.

		NOTE: this is called by TheoraVideoManager from the main thread
	 */
	virtual void update(float timeDelta);

	virtual void pause();
	virtual void play();	
	virtual void stop();
	/**
		\brief set's playback speed

		1.0 is the default. The speed factor multiplies time advance, thus
		setting the value higher will increase playback speed etc.

		NOTE: depending on Timer implementation, it may not support setting the speed
		 
	 */
	virtual void setSpeed(float speed);	

	/**
		\brief change the current time.

		if you're using another syncronization mechanism, make sure to adjust
		the time offset there
	 */
	virtual void seek(float time);

protected:
	//! Current time in seconds
	float time, speed;
	//! Is the timer paused or not
	bool paused;
};
#endif

