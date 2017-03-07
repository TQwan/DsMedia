// Copyright 2015 Headcrash Industries LLC. All Rights Reserved.

#include "DsMediaPrivatePCH.h"
#include "IMediaModule.h"
#include "IMediaPlayerFactory.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ModuleInterface.h"
#include "ModuleManager.h"


DEFINE_LOG_CATEGORY(LogDsMedia);

#define LOCTEXT_NAMESPACE "FDsMediaModule"


/**
 * Implements the DsMedia module.
 */
class FDsMediaModule
	: public IModuleInterface
	, public IMediaPlayerFactory
{
public:

	/** Default constructor. */
	FDsMediaModule()
		: Initialized(false)
	{ }

public:

	// IModuleInterface interface

	virtual void StartupModule() override
	{
		// load required libraries
		IMediaModule* MediaModule = FModuleManager::LoadModulePtr<IMediaModule>("Media");

		if (MediaModule == nullptr)
		{
			UE_LOG(LogDsMedia, Warning, TEXT("Failed to load Media module"));

			return;
		}

		// initialize DirectShow


		// initialize supported media formats
/*
		SupportedFileTypes.Add(TEXT("3gp"), LOCTEXT("Format3gp", "3GP Video Stream"));
		SupportedFileTypes.Add(TEXT("a52"), LOCTEXT("FormatA52", "Dolby Digital AC-3 Audio"));
		SupportedFileTypes.Add(TEXT("aac"), LOCTEXT("FormatAac", "MPEG-2 Advanced Audio Coding File"));
		SupportedFileTypes.Add(TEXT("asf"), LOCTEXT("FormatAsf", "ASF Media File"));
		SupportedFileTypes.Add(TEXT("au"), LOCTEXT("FormatAu", "Sun Microsystems Audio"));
		SupportedFileTypes.Add(TEXT("avi"), LOCTEXT("FormatAvi", "Audio Video Interleave File"));
		SupportedFileTypes.Add(TEXT("dts"), LOCTEXT("FormatDts", "Digital Theater System File"));
		SupportedFileTypes.Add(TEXT("dv"), LOCTEXT("FormatDv", "Digital Video File"));
		SupportedFileTypes.Add(TEXT("flac"), LOCTEXT("FormatFlac", "Free Lossless Audio Codec"));
		SupportedFileTypes.Add(TEXT("flv"), LOCTEXT("FormatFlv", "Adobe Flash Video"));
		SupportedFileTypes.Add(TEXT("mkv"), LOCTEXT("FormatMkv", "Matroska Video"));
		SupportedFileTypes.Add(TEXT("mka"), LOCTEXT("FormatMka", "Matroska Audio"));
		SupportedFileTypes.Add(TEXT("mov"), LOCTEXT("FormatMov", "Apple QuickTime Movie"));
		SupportedFileTypes.Add(TEXT("mp2"), LOCTEXT("FormatMp2", "MPEG-1 Audio"));
		SupportedFileTypes.Add(TEXT("mp3"), LOCTEXT("FormatMp3", "MPEG-2 Audio"));
		SupportedFileTypes.Add(TEXT("mp4"), LOCTEXT("FormatMp4", "MPEG-4 Movie"));
		SupportedFileTypes.Add(TEXT("mpg"), LOCTEXT("FormatMpg", "MPEG-2 Movie"));
		SupportedFileTypes.Add(TEXT("nsc"), LOCTEXT("FormatNsc", "Windows Media Station"));
		SupportedFileTypes.Add(TEXT("nsv"), LOCTEXT("FormatNsv", "Nullsoft Streaming Video"));
		SupportedFileTypes.Add(TEXT("nut"), LOCTEXT("FormatNut", "NUT Multimedia Container"));
		SupportedFileTypes.Add(TEXT("ogm"), LOCTEXT("FormatMp4", "Ogg Multimedia"));
		SupportedFileTypes.Add(TEXT("ogg"), LOCTEXT("FormatOgg", "Ogg Multimedia"));
		SupportedFileTypes.Add(TEXT("ra"), LOCTEXT("FormatRa", "Real Audio"));
		SupportedFileTypes.Add(TEXT("ram"), LOCTEXT("FormatRam", "Real Audio Metadata"));
		SupportedFileTypes.Add(TEXT("rm"), LOCTEXT("FormatRm", "Real Media"));
		SupportedFileTypes.Add(TEXT("rmvb"), LOCTEXT("FormatRmvb", "Real Media VBR"));
		SupportedFileTypes.Add(TEXT("rv"), LOCTEXT("FormatRv", "Real Video"));
		SupportedFileTypes.Add(TEXT("ts"), LOCTEXT("FormatTs", "MPEG-2 Transport Stream"));
		SupportedFileTypes.Add(TEXT("tac"), LOCTEXT("FormatTac", "True Audio Codec File"));
		SupportedFileTypes.Add(TEXT("tta"), LOCTEXT("FormatTta", "True Audio Codec File"));
		SupportedFileTypes.Add(TEXT("ty"), LOCTEXT("FormatTy", "Tivo Container"));
		SupportedFileTypes.Add(TEXT("vid"), LOCTEXT("FormatVid", "Generic Video File"));
		SupportedFileTypes.Add(TEXT("wav"), LOCTEXT("FormatWav", "Wave Audio File"));
		SupportedFileTypes.Add(TEXT("wmv"), LOCTEXT("FormatWmv", "Windows Media Video"));
		SupportedFileTypes.Add(TEXT("xa"), LOCTEXT("FormatXa", "PlayStation Audio File"));

		// initialize supported URI schemes
		SupportedUriSchemes.Add(TEXT("cdda://"));
		SupportedUriSchemes.Add(TEXT("file://"));
		SupportedUriSchemes.Add(TEXT("dvd://"));
		SupportedUriSchemes.Add(TEXT("ftp://"));
		SupportedUriSchemes.Add(TEXT("http://"));
		SupportedUriSchemes.Add(TEXT("https://"));
		SupportedUriSchemes.Add(TEXT("mms://"));
		SupportedUriSchemes.Add(TEXT("rtp://"));
		SupportedUriSchemes.Add(TEXT("rtsp://"));
		SupportedUriSchemes.Add(TEXT("sap://"));
		SupportedUriSchemes.Add(TEXT("screen://"));
		SupportedUriSchemes.Add(TEXT("vcd://"));
*/
		// register factory
		MediaModule->RegisterPlayerFactory(*this);

		Initialized = true;
	}

	virtual void ShutdownModule() override
	{
		if (!Initialized)
		{
			return;
		}

		Initialized = false;

		// unregister video player factory
		IMediaModule* MediaModule = FModuleManager::GetModulePtr<IMediaModule>("Media");

		if (MediaModule != nullptr)
		{
			MediaModule->UnregisterPlayerFactory(*this);
		}
	}

public:

	// IMediaPlayerFactory interface

	virtual TSharedPtr<IMediaPlayer> CreatePlayer() override
	{
		if (!Initialized)
		{
			return nullptr;
		}

		return MakeShareable(new FDsMediaPlayer);
	}

	virtual const FMediaFileTypes& GetSupportedFileTypes() const override
	{
		return SupportedFileTypes;
	}

	virtual bool SupportsUrl(const FString& Url) const override
	{
		const FString Extension = FPaths::GetExtension(Url);

		if (!Extension.IsEmpty())
		{
			return SupportedFileTypes.Contains(Extension);
		}

		for (const FString& Scheme : SupportedUriSchemes)
		{
			if (Url.StartsWith(Scheme))
			{
				return true;
			}
		}

		return false;
	}

private:

	/** Whether the module has been initialized. */
	bool Initialized;

	/** The collection of supported media file types. */
	FMediaFileTypes SupportedFileTypes;

	/** The collection of supported URI schemes. */
	TArray<FString> SupportedUriSchemes;
};


IMPLEMENT_MODULE(FDsMediaModule, DsMedia);


#undef LOCTEXT_NAMESPACE
