// Copyright 2015 Headcrash Industries LLC. All Rights Reserved.

#include "DsMediaPrivatePCH.h"


#define LOCTEXT_NAMESPACE "FDsMediaPlayer"


/* FDsMediaPlayer structors
 *****************************************************************************/


FDsMediaPlayer::FDsMediaPlayer()
	: Duration(0)
{
}


FDsMediaPlayer::~FDsMediaPlayer()
{
	Close();
}


/* IMediaInfo interface
 *****************************************************************************/

FTimespan FDsMediaPlayer::GetDuration() const
{
	return Duration;
}


TRange<float> FDsMediaPlayer::GetSupportedRates(EMediaPlaybackDirections Direction, bool Unthinned) const
{
	return TRange<float>(1.0f);
}


FString FDsMediaPlayer::GetUrl() const
{
	return MediaUrl;
}


bool FDsMediaPlayer::SupportsRate(float Rate, bool Unthinned) const
{
	return (Rate == 1.0f);
}


bool FDsMediaPlayer::SupportsScrubbing() const
{
	return false;
//	return ((Player != nullptr) && (FVlc::MediaPlayerIsSeekable(Player) != 0));
}


bool FDsMediaPlayer::SupportsSeeking() const
{
	return false;
//	return ((Player != nullptr) && (FVlc::MediaPlayerIsSeekable(Player) != 0));
}


/* IMediaPlayer interface
 *****************************************************************************/

void FDsMediaPlayer::Close()
{
	if (!CurrentState.IsValid())
	{
		return;
	}

	// release state
	CurrentState = nullptr;

	// reset fields
	AudioTracks.Reset();
	CaptionTracks.Reset();
	VideoTracks.Reset();
	MediaUrl.Reset();

	MediaEvent.Broadcast(EMediaEvent::TracksChanged);
	MediaEvent.Broadcast(EMediaEvent::MediaClosed);
}


const TArray<IMediaAudioTrackRef>& FDsMediaPlayer::GetAudioTracks() const
{
	return AudioTracks;
}


const TArray<IMediaCaptionTrackRef>& FDsMediaPlayer::GetCaptionTracks() const
{
	return CaptionTracks;
}


const IMediaInfo& FDsMediaPlayer::GetMediaInfo() const 
{
	return *this;
}


float FDsMediaPlayer::GetRate() const
{
	if (!CurrentState.IsValid() || !IsPlaying())
	{
		return 0.0f;
	}

	return 1.0f;
//	return FVlc::MediaPlayerGetRate(Player);
}


FTimespan FDsMediaPlayer::GetTime() const 
{
	if (!CurrentState.IsValid())
	{
		return FTimespan::Zero();
	}

	return FTimespan::Zero();
//	return FTimespan::FromSeconds(CurrentTime);
}


const TArray<IMediaVideoTrackRef>& FDsMediaPlayer::GetVideoTracks() const
{
	return VideoTracks;
}


bool FDsMediaPlayer::IsLooping() const 
{
	return false;
//	return ShouldLoop;
}


bool FDsMediaPlayer::IsPaused() const
{
	return true;
//	return ((Player != nullptr) && (FVlc::MediaPlayerGetState(Player) == ELibvlcState::Paused));
}


bool FDsMediaPlayer::IsPlaying() const
{
	return false;
//	return ((Player != nullptr) && (FVlc::MediaPlayerGetState(Player) == ELibvlcState::Playing));
}


bool FDsMediaPlayer::IsReady() const
{
	if (!CurrentState.IsValid())
	{
		return false;
	}

	return false;
//	return ((State >= ELibvlcState::Playing) && (State < ELibvlcState::Error));
}


bool FDsMediaPlayer::Open(const FString& Url)
{
	if (Url.IsEmpty())
	{
		return false;
	}

	return false;
}


bool FDsMediaPlayer::Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl)
{
	if ((Archive->TotalSize() == 0) || OriginalUrl.IsEmpty())
	{
		return false;
	}

	Close();

	return false;
}


bool FDsMediaPlayer::Seek(const FTimespan& Time)
{
	if (!IsReady())
	{
		return false;
	}

	return false;
}


bool FDsMediaPlayer::SetLooping(bool Looping)
{
	return false;
}


bool FDsMediaPlayer::SetRate(float Rate)
{
	if (!CurrentState.IsValid())
	{
		return false;
	}

	return false;
//	if ((FVlc::MediaPlayerSetRate(Player, Rate) == -1))
}


/* FDsMediaPlayer implementation
 *****************************************************************************/

bool FDsMediaPlayer::InitializeMediaPlayer(/*FLibvlcMedia* Media*/)
{
	return false;
}


void FDsMediaPlayer::InitializeTracks()
{/*
	if (Player == nullptr)
	{
		return;
	}
	
	FLibvlcMedia* Media = FVlc::MediaPlayerGetMedia(Player);

	if (Media == nullptr)
	{
		return;
	}

	if (Tracks.Num() > 0)
	{
		AudioTracks.Empty();
		CaptionTracks.Empty();
		VideoTracks.Empty();

		MediaEvent.Broadcast(EMediaEvent::TracksChanged);
	}

	// audio tracks
	FLibvlcTrackDescription* AudioTrackDescr = FVlc::AudioGetTrackDescription(Player);
	{
		while (AudioTrackDescr != nullptr)
		{
			if (AudioTrackDescr->Id != -1)
			{
				TSharedRef<FDsMediaAudioTrack, ESPMode::ThreadSafe> NewTrack = MakeShareable(
					new FDsMediaAudioTrack(Player, AudioTracks.Num(), AudioTrackDescr)
				);

				AudioTracks.Add(NewTrack);
				Tracks.Add(NewTrack);
			}

			AudioTrackDescr = AudioTrackDescr->Next;
		}

		FVlc::TrackDescriptionListRelease(AudioTrackDescr);
	}

	// caption tracks
	FLibvlcTrackDescription* CaptionTrackDescr = FVlc::VideoGetSpuDescription(Player);
	{
		while (CaptionTrackDescr != nullptr)
		{
			if (CaptionTrackDescr->Id != -1)
			{
				TSharedRef<FDsMediaCaptionTrack, ESPMode::ThreadSafe> NewTrack = MakeShareable(
					new FDsMediaCaptionTrack(Player, CaptionTracks.Num(), CaptionTrackDescr)
				);

				CaptionTracks.Add(NewTrack);
				Tracks.Add(NewTrack);
			}

			CaptionTrackDescr = CaptionTrackDescr->Next;
		}

		FVlc::TrackDescriptionListRelease(AudioTrackDescr);
	}

	// video tracks
	FLibvlcTrackDescription* VideoTrackDescr = FVlc::VideoGetTrackDescription(Player);
	{
		while (VideoTrackDescr != nullptr)
		{
			if (VideoTrackDescr->Id != -1)
			{
				TSharedRef<FDsMediaVideoTrack, ESPMode::ThreadSafe> NewTrack = MakeShareable(
					new FDsMediaVideoTrack(Player, VideoTracks.Num(), VideoTrackDescr)
				);

				VideoTracks.Add(NewTrack);
				Tracks.Add(NewTrack);
			}

			VideoTrackDescr = VideoTrackDescr->Next;
		}

		FVlc::TrackDescriptionListRelease(VideoTrackDescr);
	}

	if (Tracks.Num() > 0)
	{
		MediaEvent.Broadcast(EMediaEvent::TracksChanged);
	}*/
}


#undef LOCTEXT_NAMESPACE
