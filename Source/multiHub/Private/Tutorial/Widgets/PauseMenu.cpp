// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/Widgets/PauseMenu.h"
#include "Components/Button.h"


bool UPauseMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (backBtn && quitBtn)
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, TEXT("Back pressed"));
		backBtn->OnClicked.AddUniqueDynamic(this,&UPauseMenu::OnBackClicked);
		quitBtn->OnClicked.AddUniqueDynamic(this,&UPauseMenu::OnQuitClicked);
	}
	return true;
}


void UPauseMenu::OnBackClicked()
{
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, TEXT("Back pressed"));
	this->Remove();
}

void UPauseMenu::OnQuitClicked()
{
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, TEXT("QUIT pressed"));
	if (connecter)
	{
		connecter->JoinToMainMenu();
	}
}
