// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIHUB_API UPauseMenu : public UMenuBase
{
	GENERATED_BODY()

	UFUNCTION()
	void OnBackClicked();
	UFUNCTION()
	void OnQuitClicked();

protected:
	//preconstruct is construct, construct is beginplay, and initialize is 
	virtual bool Initialize() override;
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* backBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* quitBtn;

};
