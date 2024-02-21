// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/MultiHubGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIHUB_API ALobbyGameMode : public AMultiHubGameMode
{
	GENERATED_BODY()
	uint32 numberOfPlayers = 0;

public:
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
