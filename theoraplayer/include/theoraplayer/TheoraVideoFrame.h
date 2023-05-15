/************************************************************************************
This source file is part of the Theora Video Playback Library
For latest info, see http://libtheoraplayer.googlecode.com
*************************************************************************************
Copyright (c) 2008-2014 Kresimir Spes (kspes@cateia.com)
This program is free software; you can redistribute it and/or modify it under
the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
*************************************************************************************/
#ifndef THEORA_VIDEOFRAME_H
#define THEORA_VIDEOFRAME_H

#include "TheoraExport.h"
#include "TheoraVideoClip.h"

struct TheoraPixelTransform;
/**
	
*/
class TheoraPlayerExport TheoraVideoFrame
{
public:
	//! global time in seconds this frame should be displayed on
	float timeToDisplay;
	//! whether the frame is ready for display or not
	bool ready;
	//! indicates the frame is being used by TheoraWorkerThread instance
	bool inUse;
	//! used to keep track of linear time in looping videos
	int iteration;
	
	int bpp;

	TheoraVideoFrame(TheoraVideoClip* parent);
	virtual ~TheoraVideoFrame();

	//! returns the frame number of this frame in the theora stream
	unsigned long getFrameNumber() { return this->frameNumber; }

	int getWidth();
	int getStride();
	int getHeight();

	unsigned char* getBuffer();

	//! internal function, do not use directly
	void _setFrameNumber(unsigned long number) { this->frameNumber = number; }	

	void clear();	

	//! Called by TheoraVideoClip to decode a source buffer onto itself
	virtual void decode(struct TheoraPixelTransform* t);

protected:
	TheoraVideoClip* parent;
	unsigned char* buffer;
	unsigned long frameNumber;
};
#endif
