// Copyright 2015 Headcrash Industries LLC. All Rights Reserved.

#pragma once

#include "AllowWindowsPlatformTypes.h"


class FDsMediaState;


/**
 * Implements a media player using the DirectShow API.
 */
class FDsMediaPlayer
	: public IMediaInfo
	, public IMediaPlayer
{
public:

	/** Create and initialize a new instance. */
	FDsMediaPlayer();

	/** Destructor. */
	~FDsMediaPlayer();

public:

	// IMediaInfo interface

	virtual FTimespan GetDuration() const override;
	virtual TRange<float> GetSupportedRates( EMediaPlaybackDirections Direction, bool Unthinned ) const override;
	virtual FString GetUrl() const override;
	virtual bool SupportsRate( float Rate, bool Unthinned ) const override;
	virtual bool SupportsScrubbing() const override;
	virtual bool SupportsSeeking() const override;

public:

	// IMediaPlayer interface

	virtual void Close() override;
	virtual const TArray<IMediaAudioTrackRef>& GetAudioTracks() const override;
	virtual const TArray<IMediaCaptionTrackRef>& GetCaptionTracks() const override;
	virtual const IMediaInfo& GetMediaInfo() const override;
	virtual float GetRate() const override;
	virtual FTimespan GetTime() const override;
	virtual const TArray<IMediaVideoTrackRef>& GetVideoTracks() const override;
	virtual bool IsLooping() const override;
	virtual bool IsPaused() const override;
	virtual bool IsPlaying() const override;
	virtual bool IsReady() const override;
	virtual bool Open(const FString& Url ) override;
	virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl) override;
	virtual bool Seek(const FTimespan& Time) override;
	virtual bool SetLooping(bool Looping) override;
	virtual bool SetRate(float Rate) override;

	DECLARE_DERIVED_EVENT(FDsMediaPlayer, IMediaPlayer::FOnMediaEvent, FOnMediaEvent);
	virtual FOnMediaEvent& OnMediaEvent() override
	{
		return MediaEvent;
	}

protected:

	/**
	 * Initialize the media player object.
	 *
	 * @param Media The media to play.
	 * @return true on success, false otherwise.
	 */
	bool InitializeMediaPlayer(/*FLibvlcMedia* Media*/);

	/** Initialize the media tracks. */
	void InitializeTracks();

private:

	/** The available audio tracks. */
	TArray<IMediaAudioTrackRef> AudioTracks;

	/** The available caption tracks. */
	TArray<IMediaCaptionTrackRef> CaptionTracks;

	/** Current media state object, if any. */
	TSharedPtr<FDsMediaState> CurrentState;

	/** The duration of the currently loaded media. */
	FTimespan Duration;

	/** Holds an event delegate that is invoked when a media event occurred. */
	FOnMediaEvent MediaEvent;

	/** Currently opened media. */
	FString MediaUrl;

	/** Handle to the registered ticker. */
	FDelegateHandle TickerHandle;

	/** The available video tracks. */
	TArray<IMediaVideoTrackRef> VideoTracks;
};


#include "HideWindowsPlatformTypes.h"
