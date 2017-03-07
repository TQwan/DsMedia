// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AllowWindowsPlatformTypes.h"


struct ISampleGrabber;


/**
 * Implements the state of the media player.
 */
class FDsMediaState
{
private:

	/** Sample grabber filter. */
	TComPtr<IBaseFilter> GrabberFilter;

	/** The DirectShow filter graph builder. */
	TComPtr<IGraphBuilder> GraphBuilder;

	/** The media control object. */
	TComPtr<IMediaControl> MediaControl;

	/** The media event object. */
	TComPtr<IMediaEvent> MediaEvent;

	/** Media seeking object. */
	TComPtr<IMediaSeeking> MediaSeeking;

	/** Sample grabber object. */
	TComPtr<ISampleGrabber> SampleGrabber;

	/** Video window interface. */
	TComPtr<IVideoWindow> VideoWindow;

	// Video output width
	int videoWidth;

	// Video output height
	int videoHeight;
};


#include "HideWindowsPlatformTypes.h"
