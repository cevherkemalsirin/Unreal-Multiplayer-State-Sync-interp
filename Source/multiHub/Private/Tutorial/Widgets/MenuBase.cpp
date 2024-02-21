// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/Widgets/MenuBase.h"

void UMenuBase::Setup()
{
	this->AddToViewport();

	if (GetWorld()->GetFirstPlayerController())
	{
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		FInputModeUIOnly inputUI;
		inputUI.SetWidgetToFocus(this->TakeWidget());
		inputUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		controller->SetInputMode(inputUI);
		controller->SetShowMouseCursor(true);
	}
}

void UMenuBase::Remove()
{
	this->RemoveFromParent();

	if (GetWorld())
	{
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly inputUI;
		controller->SetInputMode(inputUI);
		controller->SetShowMouseCursor(false);
	}
}
