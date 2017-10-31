#include "GameAnalyticsPrivatePCH.h"
#if PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#endif
#include "../GA-SDK-CPP/GameAnalytics.h"
#elif PLATFORM_HTML5_BROWSER
#include "../GA-SDK-HTML5/GameAnalytics.h"
#endif

#include "EngineVersion.h"

#define GA_VERSION TEXT("2.6.6")

DEFINE_LOG_CATEGORY_STATIC(LogGameAnalyticsAnalytics, Display, All);

IMPLEMENT_MODULE( FAnalyticsGameAnalytics, GameAnalytics )

void FAnalyticsGameAnalytics::StartupModule()
{
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsGameAnalytics Constructor"));
	GameAnalyticsProvider = MakeShareable(new FAnalyticsProviderGameAnalytics());
}

void FAnalyticsGameAnalytics::ShutdownModule()
{
	if (GameAnalyticsProvider.IsValid())
	{
		GameAnalyticsProvider->EndSession();
	}
}

#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 13
TSharedPtr<IAnalyticsProvider> FAnalyticsGameAnalytics::CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const
{
	return GameAnalyticsProvider;
}
#else
TSharedPtr<IAnalyticsProvider> FAnalyticsGameAnalytics::CreateAnalyticsProvider(const FAnalytics::FProviderConfigurationDelegate& GetConfigValue) const
{
    return GameAnalyticsProvider;
}
#endif


FAnalyticsGameAnalytics::FGameAnalyticsProjectSettings FAnalyticsGameAnalytics::LoadProjectSettings()
{
	FGameAnalyticsProjectSettings Settings;

	if (!GConfig) return Settings;

	if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidGameKey"), Settings.AndroidGameKey, GetIniName()))
    {
        Settings.AndroidGameKey = "";
    }
	if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidSecretKey"), Settings.AndroidSecretKey, GetIniName()))
    {
        Settings.AndroidSecretKey = "";
    }
	if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidBuild"), Settings.AndroidBuild, GetIniName()))
    {
        Settings.AndroidBuild = "0.1";
    }

	if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosGameKey"), Settings.IosGameKey, GetIniName()))
    {
        Settings.IosGameKey = "";
    }
	if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosSecretKey"), Settings.IosSecretKey, GetIniName()))
    {
        Settings.IosSecretKey = "";
    }
	if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosBuild"), Settings.IosBuild, GetIniName()))
    {
        Settings.IosBuild = "0.1";
    }

    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("MacGameKey"), Settings.MacGameKey, GetIniName()))
    {
        Settings.MacGameKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("MacSecretKey"), Settings.MacSecretKey, GetIniName()))
    {
        Settings.MacSecretKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("MacBuild"), Settings.MacBuild, GetIniName()))
    {
        Settings.MacBuild = "0.1";
    }

	if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("WindowsGameKey"), Settings.WindowsGameKey, GetIniName()))
    {
        Settings.WindowsGameKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("WindowsSecretKey"), Settings.WindowsSecretKey, GetIniName()))
    {
        Settings.WindowsSecretKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("WindowsBuild"), Settings.WindowsBuild, GetIniName()))
    {
        Settings.WindowsBuild = "0.1";
    }

    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("LinuxGameKey"), Settings.LinuxGameKey, GetIniName()))
    {
        Settings.LinuxGameKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("LinuxSecretKey"), Settings.LinuxSecretKey, GetIniName()))
    {
        Settings.LinuxSecretKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("LinuxBuild"), Settings.LinuxBuild, GetIniName()))
    {
        Settings.LinuxBuild = "0.1";
    }

    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("Html5GameKey"), Settings.Html5GameKey, GetIniName()))
    {
        Settings.Html5GameKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("Html5SecretKey"), Settings.Html5SecretKey, GetIniName()))
    {
        Settings.Html5SecretKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("Html5Build"), Settings.Html5Build, GetIniName()))
    {
        Settings.Html5Build = "0.1";
    }

    if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("UseCustomId"), Settings.UseCustomId, GetIniName()))
    {
        Settings.UseCustomId = false;
    }
    if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("UseManualSessionHandling"), Settings.UseManualSessionHandling, GetIniName()))
    {
        Settings.UseManualSessionHandling = false;
    }
	if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("InfoLogBuild"), Settings.InfoLogBuild, GetIniName()))
    {
        Settings.InfoLogBuild = true;
    }
	if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("VerboseLogBuild"), Settings.VerboseLogBuild, GetIniName()))
    {
        Settings.VerboseLogBuild = false;
    }

	GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+CustomDimensions01"), Settings.CustomDimensions01, GetIniName());
	GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+CustomDimensions02"), Settings.CustomDimensions02, GetIniName());
	GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+CustomDimensions03"), Settings.CustomDimensions03, GetIniName());
	GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+ResourceCurrencies"), Settings.ResourceCurrencies, GetIniName());
	GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+ResourceItemTypes"), Settings.ResourceItemTypes, GetIniName());

	return Settings;
}


#if !UE_BUILD_SHIPPING
/**
* Verifies that the event name matches GameAnalytics's 32 char limit and warns if it doesn't
*/
inline void CheckEventNameLen(const FString& EventName)
{
	const int32 Length = EventName.Len();
	if (Length > 32)
	{
		UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("GameAnalytics event name is too long: %s and will be truncated by GameAnalytics. 32 character max limit."), *EventName);
	}
	else if (Length == 0)
	{
		UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("GameAnalytics event name is empty!"));
	}
}

#define WarnIfEventNameIsWrongLength(x) CheckEventNameLen(x)
#else
// Have these compile out
#define WarnIfEventNameIsWrongLength(x)
#endif



// Provider
FAnalyticsProviderGameAnalytics::FAnalyticsProviderGameAnalytics() :
	bHasSessionStarted(false),
	bHasWrittenFirstEvent(false),
	Age(0)
{
	AnalyticsFilePath = FPaths::GameSavedDir() + TEXT("Analytics/");
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 15
    UserId = FPlatformMisc::GetDeviceId();
#else
	UserId = FPlatformMisc::GetUniqueDeviceId();
#endif
}

FAnalyticsProviderGameAnalytics::~FAnalyticsProviderGameAnalytics()
{
	if (bHasSessionStarted)
	{
		EndSession();
	}
}

bool FAnalyticsProviderGameAnalytics::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes)
{
    if(!bHasSessionStarted)
    {
        ProjectSettings = FAnalyticsGameAnalytics::LoadProjectSettings();

#if PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
        gameanalytics::GameAnalytics::configureWritablePath(TCHAR_TO_ANSI(*FPaths::GameSavedDir()));
#endif

        ////// Enable log
        UGameAnalytics::setEnabledInfoLog(ProjectSettings.InfoLogBuild);
        UGameAnalytics::setEnabledVerboseLog(ProjectSettings.VerboseLogBuild);

        ////// Configure engine version
        FString EngineVersionString = FString::Printf(TEXT("unreal %d.%d.%d"), FEngineVersion::Current().GetMajor(), FEngineVersion::Current().GetMinor(), FEngineVersion::Current().GetPatch());
        UGameAnalytics::configureGameEngineVersion(TCHAR_TO_ANSI(*EngineVersionString));
        FString SdkVersionString = FString::Printf(TEXT("unreal %s"), GA_VERSION);
        UGameAnalytics::configureSdkGameEngineVersion(TCHAR_TO_ANSI(*SdkVersionString));

        //// Configure build version
#if PLATFORM_IOS
        UGameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.IosBuild));
#elif PLATFORM_ANDROID
        UGameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.AndroidBuild));
#elif PLATFORM_MAC
        UGameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.MacBuild));
#elif PLATFORM_WINDOWS
        UGameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.WindowsBuild));
#elif PLATFORM_LINUX
        UGameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.LinuxBuild));
#elif PLATFORM_HTML5
        UGameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.Html5Build));
#endif

        ////// Configure available virtual currencies and item types
        if (ProjectSettings.ResourceCurrencies.Num() > 0)
        {
            std::vector<std::string> currencies;
            for (const FString& currency : ProjectSettings.ResourceCurrencies)
            {
                currencies.push_back(TCHAR_TO_ANSI(*currency));
            }
            UGameAnalytics::configureAvailableResourceCurrencies(currencies);
        }

        if (ProjectSettings.ResourceItemTypes.Num() > 0)
        {
            std::vector<std::string> resourceItem;
            for (const FString& item : ProjectSettings.ResourceItemTypes)
            {
                resourceItem.push_back(TCHAR_TO_ANSI(*item));
            }
            UGameAnalytics::configureAvailableResourceItemTypes(resourceItem);
        }

        // Configure available custom dimensions
        if (ProjectSettings.CustomDimensions01.Num() > 0)
        {
            std::vector<std::string> customDimension01;
            for (const FString& dimension01 : ProjectSettings.CustomDimensions01)
            {
                customDimension01.push_back(TCHAR_TO_ANSI(*dimension01));
            }
            UGameAnalytics::configureAvailableCustomDimensions01(customDimension01);
        }

        if (ProjectSettings.CustomDimensions02.Num() > 0)
        {
            std::vector<std::string> customDimension02;
            for (const FString& dimension02 : ProjectSettings.CustomDimensions02)
            {
                customDimension02.push_back(TCHAR_TO_ANSI(*dimension02));
            }
            UGameAnalytics::configureAvailableCustomDimensions02(customDimension02);
        }

        if (ProjectSettings.CustomDimensions03.Num() > 0)
        {
            std::vector<std::string> customDimension03;
            for (const FString& dimension03 : ProjectSettings.CustomDimensions03)
            {
                customDimension03.push_back(TCHAR_TO_ANSI(*dimension03));
            }
            UGameAnalytics::configureAvailableCustomDimensions03(customDimension03);
        }

        if(ProjectSettings.UseManualSessionHandling)
        {
            UGameAnalytics::setEnabledManualSessionHandling(ProjectSettings.UseManualSessionHandling);
        }

        if(!ProjectSettings.UseCustomId)
        {
            ////// Initialize
#if PLATFORM_IOS
            UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.IosGameKey), TCHAR_TO_ANSI(*ProjectSettings.IosSecretKey));
#elif PLATFORM_ANDROID
            UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.AndroidGameKey), TCHAR_TO_ANSI(*ProjectSettings.AndroidSecretKey));
#elif PLATFORM_MAC
            UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.MacGameKey), TCHAR_TO_ANSI(*ProjectSettings.MacSecretKey));
#elif PLATFORM_WINDOWS
            UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.WindowsGameKey), TCHAR_TO_ANSI(*ProjectSettings.WindowsSecretKey));
#elif PLATFORM_LINUX
            UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.LinuxGameKey), TCHAR_TO_ANSI(*ProjectSettings.LinuxSecretKey));
#elif PLATFORM_HTML5
            UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.Html5GameKey), TCHAR_TO_ANSI(*ProjectSettings.Html5SecretKey));
#endif
        }
        else
        {
            UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::StartSession Custom id is enabled. Initialize is delayed until custom id has been set."));
        }

        bHasSessionStarted = true;
    }
    else if(ProjectSettings.UseManualSessionHandling)
    {
        UGameAnalytics::startSession();
    }

    return bHasSessionStarted;
}

void FAnalyticsProviderGameAnalytics::EndSession()
{
	if (bHasSessionStarted)
	{
		if(ProjectSettings.UseManualSessionHandling)
		{
			UGameAnalytics::endSession();
		}
		else
		{
#if PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
			gameanalytics::GameAnalytics::onStop();
#elif PLATFORM_HTML5_BROWSER
            js_onStop();
#else
			UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::EndSession ignored."));
#endif
		}
	}
}

void FAnalyticsProviderGameAnalytics::FlushEvents()
{
	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::FlushEvents ignored."));
}

void FAnalyticsProviderGameAnalytics::SetUserID(const FString& InUserID)
{
    if(ProjectSettings.UseCustomId)
    {
        UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::SetCustomId('%s')"), *InUserID);
        UGameAnalytics::configureUserId(TCHAR_TO_ANSI(*InUserID));
        UserId = InUserID;
#if PLATFORM_IOS
        UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.IosGameKey), TCHAR_TO_ANSI(*ProjectSettings.IosSecretKey));
#elif PLATFORM_ANDROID
        UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.AndroidGameKey), TCHAR_TO_ANSI(*ProjectSettings.AndroidSecretKey));
#elif PLATFORM_MAC
        UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.MacGameKey), TCHAR_TO_ANSI(*ProjectSettings.MacSecretKey));
#elif PLATFORM_WINDOWS
        UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.WindowsGameKey), TCHAR_TO_ANSI(*ProjectSettings.WindowsSecretKey));
#elif PLATFORM_LINUX
        UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.LinuxGameKey), TCHAR_TO_ANSI(*ProjectSettings.LinuxSecretKey));
#elif PLATFORM_HTML5
        UGameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.Html5GameKey), TCHAR_TO_ANSI(*ProjectSettings.Html5SecretKey));
#endif
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::SetCustomId Custom id is not enabled."));
    }
}

FString FAnalyticsProviderGameAnalytics::GetUserID() const
{
	return UserId;
}

FString FAnalyticsProviderGameAnalytics::GetSessionID() const
{
	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::GetSessionID ignored."));
	return SessionId;
}

bool FAnalyticsProviderGameAnalytics::SetSessionID(const FString& InSessionID)
{
	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::SetSessionID ignored."));
	return !bHasSessionStarted;
}

void FAnalyticsProviderGameAnalytics::RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        // Send an event for each attribute
        for (auto Attr : Attributes)
        {
            if (Attr.AttrName == TEXT("custom1"))
            {
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
                UGameAnalytics::setCustomDimension01(TCHAR_TO_ANSI(*Attr.AttrValueString));
#else
                UGameAnalytics::setCustomDimension01(TCHAR_TO_ANSI(*Attr.AttrValue));
#endif
            }
            else if (Attr.AttrName == TEXT("custom2"))
            {
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
                UGameAnalytics::setCustomDimension02(TCHAR_TO_ANSI(*Attr.AttrValueString));
#else
                UGameAnalytics::setCustomDimension02(TCHAR_TO_ANSI(*Attr.AttrValue));
#endif
            }
            else if (Attr.AttrName == TEXT("custom3"))
            {
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
                UGameAnalytics::setCustomDimension03(TCHAR_TO_ANSI(*Attr.AttrValueString));
#else
                UGameAnalytics::setCustomDimension03(TCHAR_TO_ANSI(*Attr.AttrValue));
#endif
            }
            else if (Attr.AttrName == TEXT("facebook"))
            {
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
                UGameAnalytics::setFacebookId(TCHAR_TO_ANSI(*Attr.AttrValueString));
#else
                UGameAnalytics::setFacebookId(TCHAR_TO_ANSI(*Attr.AttrValue));
#endif
            }
            else
            {
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
                float AttrValue = Attr.AttrValueNumber;
                UGameAnalytics::addDesignEvent(TCHAR_TO_ANSI(*Attr.AttrName), AttrValue);
#else
                float AttrValue = FCString::Atof(*Attr.AttrValue);
                UGameAnalytics::addDesignEvent(TCHAR_TO_ANSI(*Attr.AttrName), AttrValue);
#endif
            }
        }
    }
    else if (EventName.Len() > 0)
    {
        // Send an event without value
        UGameAnalytics::addDesignEvent(TCHAR_TO_ANSI(*EventName));
    }
}

void FAnalyticsProviderGameAnalytics::SetAge(int InAge)
{
	UGameAnalytics::setBirthYear(InAge);
}

void FAnalyticsProviderGameAnalytics::SetGender(const FString& InGender)
{
    EGAGender gender = GetEnumValueFromString<EGAGender>("EGAGender", InGender.ToLower());

    if (gender == EGAGender(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("SetGender: Error value must be either male or female."));
        return;
    }

	UGameAnalytics::setGender(gender);
}

void FAnalyticsProviderGameAnalytics::RecordError(const FString& Error)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordError(const FString& Error) - ignoring call"));
}

void FAnalyticsProviderGameAnalytics::RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	EGAErrorSeverity ErrorSeverity = GetEnumValueFromString<EGAErrorSeverity>("EGAErrorSeverity", Error.ToLower());

	if (ErrorSeverity == EGAErrorSeverity(0))
	{
		UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordError: Error value must be either debug, info, warning, error, critical. Error=%s"), *Error);
		return;
	}

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		for (auto Attr : Attributes)
		{
			if (Attr.AttrName == TEXT("message"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				UGameAnalytics::addErrorEvent(ErrorSeverity, TCHAR_TO_ANSI(*Attr.AttrValueString));
#else
                UGameAnalytics::addErrorEvent(ErrorSeverity, TCHAR_TO_ANSI(*Attr.AttrValue));
#endif
			}
		}
	}
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordError wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Error%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordProgress(const FString& ProgressType, const TArray<FString>& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    EGAProgressionStatus ProgressionStatus = GetEnumValueFromString<EGAProgressionStatus>("EGAProgressionStatus", ProgressType.ToLower());

    if (ProgressionStatus == EGAProgressionStatus(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }

    const int32 ProgressHierarchyCount = ProgressHierarchy.Num();
    if(ProgressHierarchyCount > 0)
    {
        bool useValue = false;

        for (auto Attr : Attributes)
        {
            if (Attr.AttrName == TEXT("value"))
            {
                int32 value;
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
                value = Attr.AttrValueNumber;
#else
                value = FCString::Atod(*Attr.AttrValue);
#endif
                useValue = true;

				if (ProgressHierarchyCount > 2)
		        {
		            UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]), TCHAR_TO_ANSI(*ProgressHierarchy[2]), value);
		        }
		        else if (ProgressHierarchyCount > 1)
		        {
		            UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]), value);
		        }
		        else
		        {
		            UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), value);
		        }
                break;
            }
        }

        if (ProgressHierarchyCount > 2)
        {
            if(!useValue)
            {
                UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]), TCHAR_TO_ANSI(*ProgressHierarchy[2]));
            }
        }
        else if (ProgressHierarchyCount > 1)
        {
            if(!useValue)
            {
                UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]));
            }
        }
        else
        {
            if(!useValue)
            {
                UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]));
            }
        }
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordProgress wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Progression%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity)
{
    UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) ignored. Instead use: FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    EGAResourceFlowType FlowType = EGAResourceFlowType::source;
	FString Currency;
	FString ItemType;

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		for (auto Attr : Attributes)
		{
			if (Attr.AttrName == TEXT("flowType"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
                FlowType = GetEnumValueFromString<EGAResourceFlowType>("EGAResourceFlowType", Attr.AttrValueString.ToLower());
#else
                FlowType = GetEnumValueFromString<EGAResourceFlowType>("EGAResourceFlowType", Attr.AttrValue.ToLower());
#endif

                if (FlowType == EGAResourceFlowType(0))
				{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
					UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordItemPurchaseError: FlowType value must be either sink or source. flowType=%s"), *Attr.AttrValueString);
#else
                    UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordItemPurchaseError: FlowType value must be either sink or source. flowType=%s"), *Attr.AttrValue);
#endif
					return;
				}
			}
			else if (Attr.AttrName == TEXT("currency"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				Currency = Attr.AttrValueString;
#else
                Currency = Attr.AttrValue;
#endif
			}
			else if (Attr.AttrName == TEXT("itemType"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				ItemType = Attr.AttrValueString;
#else
                ItemType = Attr.AttrValue;
#endif
			}
		}

		if (!Currency.IsEmpty() && !ItemType.IsEmpty())
		{
			UGameAnalytics::addResourceEvent(FlowType, TCHAR_TO_ANSI(*Currency), ItemQuantity, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId));
		}
        else
        {
            UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordItemPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Resource%20Event"));
        }
	}
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordItemPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Resource%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) - ignoring call. Instead use: FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount) - ignoring call. Instead use: FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	FString ItemType;
	FString ItemId;
	FString CartType;
	FString Receipt;
	FString Signature;
	bool AutoFetchReceipt = false;

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		for (auto Attr : Attributes)
		{
			FString AttrString = Attr.AttrName;

			if (Attr.AttrName == TEXT("itemType"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				ItemType = Attr.AttrValueString;
#else
                ItemType = Attr.AttrValue;
#endif
			}
			else if (Attr.AttrName == TEXT("itemId"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				ItemId = Attr.AttrValueString;
#else
                ItemId = Attr.AttrValue;
#endif
			}
			else if (Attr.AttrName == TEXT("cartType"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				CartType = Attr.AttrValueString;
#else
                CartType = Attr.AttrValue;
#endif
			}
			else if (Attr.AttrName == TEXT("receipt"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				Receipt = Attr.AttrValueString;
#else
                Receipt = Attr.AttrValue;
#endif
			}
			else if (Attr.AttrName == TEXT("autoFetchReceipt"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				if (Attr.AttrValueBool)
				{
					AutoFetchReceipt = true;
				}
#else
                if (Attr.AttrValue.ToBool())
                {
                    AutoFetchReceipt = true;
                }
#endif
			}
			else if (Attr.AttrName == TEXT("signature"))
			{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
				Signature = Attr.AttrValueString;
#else
                Signature = Attr.AttrValue;
#endif
			}
		}

		if (!ItemType.IsEmpty() && !ItemId.IsEmpty() && !CartType.IsEmpty())
		{
#if PLATFORM_ANDROID
			if (!Receipt.IsEmpty() && !Signature.IsEmpty())
			{
				UGameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType), TCHAR_TO_ANSI(*Receipt), TCHAR_TO_ANSI(*Signature));
			}
			else
			{
				UGameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
			}
#elif PLATFORM_IOS
			if (!Receipt.IsEmpty())
			{
                UGameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType), TCHAR_TO_ANSI(*Receipt));
			}
			else
			{
                if(AutoFetchReceipt)
                {
                    UGameAnalytics::addBusinessEventAndAutoFetchReceipt(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
                }
                else
                {
                    UGameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
                }
			}
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX || PLATFORM_HTML5
            UGameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
#endif
		}
        else
        {
            UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Business%20Event"));
        }
	}
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Business%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordCurrencyGiven - ignoring call"));
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordCurrencyGiven - ignoring call"));
}
