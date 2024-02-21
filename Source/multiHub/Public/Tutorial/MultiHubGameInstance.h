// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Widgets/Connectable.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiHubGameInstance.generated.h"

//IMPORTANT FIX

UCLASS()
class MULTIHUB_API UMultiHubGameInstance : public UGameInstance , public IConnectable
{
	GENERATED_BODY()
	
	//executes when game starts with play button
	virtual void Init() override;

	 IOnlineSubsystem* onlineSubSys;
	 IOnlineSessionPtr sessionInterface;
	 TSharedPtr <FOnlineSessionSearch> searchSettings;

	 void CreateSession(const FName& sessionName);
	 void DestroySession(const FName& sessionName);
	

	 //delegates
	 void OnSessionCreated(FName sessionName, bool isSuccessful);
	 void OnSessionDestroyed(FName sessionName, bool isSuccessful);
	 void OnSessionFound(bool isSuccessfull);
	 void OnSessionJoined(FName sessionName, EOnJoinSessionCompleteResult::Type result);
	 void OnNetworkError(UWorld* world, UNetDriver* networkDriver, ENetworkFailure::Type, const FString& ErrorString);

public:
	UFUNCTION(Exec)
	virtual void Host() override;
	UFUNCTION(Exec)
	virtual void Join(uint32 serverIndex) override;
	UFUNCTION(Exec)
	virtual void JoinToMainMenu() override;
	virtual void RefreshServerList() override;
	virtual void StartSession() override;

	UFUNCTION(BlueprintCallable)
	void SetupMainMenu();
	UFUNCTION(BlueprintCallable)
	void SetupPauseMenu();



	UPROPERTY(EditDefaultsOnly,Category = Widgets)
	TSubclassOf<class UMenuBase> BP_MenuWidget;
	class UMainMenu* menuWidget;
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<class UMenuBase> BP_PauseWidget;
	class UPauseMenu* pauseWidget;
};
