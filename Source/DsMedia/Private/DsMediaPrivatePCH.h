// Copyright 2015 Headcrash Industries LLC. All Rights Reserved.

#pragma once


/* Dependencies
 *****************************************************************************/

#include "Core.h"
#include "CoreUObject.h"
#include "IMediaInfo.h"
#include "IMediaPlayer.h"
#include "IMediaSink.h"
#include "IMediaStream.h"
#include "IMediaAudioTrack.h"
#include "IMediaCaptionTrack.h"
#include "IMediaVideoTrack.h"

#include "AllowWindowsPlatformTypes.h"
#include <windows.h>
#include <dshow.h>
#include <WTypes.h>
#include "COMPointer.h"
#include "HideWindowsPlatformTypes.h"


/* Private macros
 *****************************************************************************/

DECLARE_LOG_CATEGORY_EXTERN(LogDsMedia, Log, All);


/* Private includes
 *****************************************************************************/

#include "DsMediaPlayer.h"
#include "DsMediaState.h"
