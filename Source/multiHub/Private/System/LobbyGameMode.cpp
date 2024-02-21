// Fill out your copyright notice in the Description page of Project Settings.


#include "System/LobbyGameMode.h"
#include "Tutorial/Widgets/Connectable.h"

void ALobbyGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	++numberOfPlayers;
	if (numberOfPlayers >= 2)
	{
		if (GetWorld())
		{
			bUseSeamlessTravel = true;
			IConnectable* instance = Cast<IConnectable>(GetGameInstance());
			if (instance)
			{
				instance->StartSession();
				GetWorld()->ServerTravel("/Game/Arena/Maps/Demonstration?listen");
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--numberOfPlayers;
	UE_LOG(LogTemp, Warning, TEXT("Number of players are %d"), numberOfPlayers);
}
