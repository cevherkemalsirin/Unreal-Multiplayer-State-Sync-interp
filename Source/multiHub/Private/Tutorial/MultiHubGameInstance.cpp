// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/MultiHubGameInstance.h"
#include "Tutorial/Widgets/MainMenu.h"
#include "Tutorial/Widgets/PauseMenu.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemTypes.h"
#include "OnlineSessionSettings.h"

const FName SESSION_NAME = NAME_GameSession;

void UMultiHubGameInstance::Init()
{
	menuWidget = nullptr;
	onlineSubSys = IOnlineSubsystem::Get();
	
	if (onlineSubSys)
	{
		sessionInterface = onlineSubSys->GetSessionInterface();
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString::Printf(TEXT("%s"), *onlineSubSys->GetSubsystemName().ToString()));
		
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiHubGameInstance::OnSessionCreated);
		sessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiHubGameInstance::OnSessionDestroyed);
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiHubGameInstance::OnSessionFound);
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiHubGameInstance::OnSessionJoined);
		if (GEngine)
		{
			GEngine->NetworkFailureEvent.AddUObject(this, &UMultiHubGameInstance::OnNetworkError);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, TEXT("Online Sub System is not found"));
	}
}


void UMultiHubGameInstance::Host()
{
	if (sessionInterface.IsValid())
	{
		FNamedOnlineSession* previousSession = sessionInterface->GetNamedSession(SESSION_NAME);
		if (previousSession)
		{
			this->DestroySession(SESSION_NAME);
		}
		else
		{
			this->CreateSession(SESSION_NAME);
		}
		
	}

}


void UMultiHubGameInstance::Join(uint32 serverIndex)
{
	if (sessionInterface.IsValid())
	{
		sessionInterface->JoinSession(0, SESSION_NAME, searchSettings->SearchResults[serverIndex]);
	}
}


void UMultiHubGameInstance::RefreshServerList()
{
	searchSettings = MakeShareable(new FOnlineSessionSearch());
	if (searchSettings.IsValid())
	{
		//searchSettings->bIsLanQuery = false;
		searchSettings->MaxSearchResults = 200;
		searchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		sessionInterface->FindSessions(0, searchSettings.ToSharedRef());
	}
}


void UMultiHubGameInstance::SetupMainMenu()
{
	if (BP_MenuWidget)
	{
		menuWidget = CreateWidget<UMainMenu>(this, BP_MenuWidget);
		menuWidget->SetConnector(this);
		menuWidget->Setup();
	}
}


void UMultiHubGameInstance::SetupPauseMenu()
{
	if (BP_PauseWidget)
	{
		pauseWidget = CreateWidget<UPauseMenu>(this, BP_PauseWidget);
		pauseWidget->SetConnector(this);
		pauseWidget->Setup();
	}
}


void UMultiHubGameInstance::JoinToMainMenu()
{
	if (GetWorld())
	{
		//travel specific controller to the host world
		GetWorld()->GetFirstPlayerController()->ClientTravel("/Game/Map/MainMenu", ETravelType::TRAVEL_Absolute);
	}

}


void UMultiHubGameInstance::CreateSession(const FName& sessionName)
{
	if (sessionInterface.IsValid())
	{
		FOnlineSessionSettings sessionSettings;
		if (onlineSubSys->GetSubsystemName().ToString() == NULL_SUBSYSTEM)
		{
			sessionSettings.bIsLANMatch = true;
		}
		else
		{
			sessionSettings.bIsLANMatch = false;
		}
		sessionSettings.bUsesPresence = true; //enables steam lobbies
		sessionSettings.bUseLobbiesIfAvailable = true;
		sessionSettings.bShouldAdvertise = true;
		sessionSettings.NumPublicConnections = 4;
		//create server name variable in settings
		if (menuWidget->GetServerName() != "")
		{
			sessionSettings.Set(TEXT("ServerName"), menuWidget->GetServerName(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		}
		else
		{
			sessionSettings.Set(TEXT("ServerName"),FString("Default Name"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		}

		sessionInterface->CreateSession(0, sessionName, sessionSettings);
	}
}


void UMultiHubGameInstance::DestroySession(const FName& sessionName)
{
	if (sessionInterface.IsValid())
	{
		sessionInterface->DestroySession(sessionName);
	}
}


void UMultiHubGameInstance::OnSessionCreated(FName sessionName, bool isSuccessful)
{
	if (isSuccessful)
	{
		if (menuWidget)
		{
			menuWidget->Remove();
		}
		if (GetWorld())
		{
			//travel the whole game with all controllers to the new map. 
			GetWorld()->ServerTravel("/Game/Map/Lobby?listen");
		}
	}

}


void UMultiHubGameInstance::OnSessionDestroyed(FName sessionName, bool isSuccessful)
{
	if (isSuccessful)
	{
		CreateSession(sessionName);
	}

}


void UMultiHubGameInstance::OnSessionFound(bool isSuccessfull)
{

	if (isSuccessfull && searchSettings.IsValid() && menuWidget)
	{
		TArray<FServerData> serverdatas;
		for (const auto & SR : searchSettings->SearchResults)
		{
			FServerData newdata;
			if (!SR.Session.SessionSettings.Get(TEXT("ServerName"), newdata.Name))
			{
				newdata.Name = "Default Name";
			}
			newdata.HostName = SR.Session.OwningUserName;
			newdata.maxPlayer = SR.Session.SessionSettings.NumPublicConnections;
			newdata.currentPlayerNum = newdata.maxPlayer - SR.Session.NumOpenPublicConnections;
			serverdatas.Add(newdata);
		}
		menuWidget->SetUpServerList(serverdatas);
	}
	 
}


void UMultiHubGameInstance::OnSessionJoined(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
	if (result == EOnJoinSessionCompleteResult::Type::Success && sessionInterface.IsValid())
	{

		FString ipAdress;
		if (sessionInterface->GetResolvedConnectString(sessionName, ipAdress))
		{
			if (menuWidget)
			{
				menuWidget->Remove();
			}
			if (GetWorld())
			{
				GetWorld()->GetFirstPlayerController()->ClientTravel(ipAdress, ETravelType::TRAVEL_Absolute);
			}
		}

	}
}

void UMultiHubGameInstance::OnNetworkError(UWorld* world, UNetDriver* networkDriver, ENetworkFailure::Type, const FString& ErrorString)
{
	JoinToMainMenu();
}


void UMultiHubGameInstance::StartSession()
{
	if (sessionInterface)
	{
		sessionInterface->StartSession(SESSION_NAME);
	}
}


