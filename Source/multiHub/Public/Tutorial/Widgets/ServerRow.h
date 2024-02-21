// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UTextBlock;

struct FServerData;


UCLASS()
class MULTIHUB_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
	
	UFUNCTION()
	void OnServerClicked();

	uint32 index;
	class UMainMenu* parent;
	bool isSelected;
	FLinearColor startingColor;

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* serverName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* hostName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* playerCount;
	UPROPERTY(meta = (BindWidget))
	class UButton* rowBtn;

public:
	void SetServerInfo(const FServerData& serverData);
	void SetUp(class UMainMenu* parent, uint32 index);
	FORCEINLINE void SetSelected(bool select) 
	{ this->isSelected = select; select ? this->SetColorAndOpacity(FLinearColor::Green) : this->SetColorAndOpacity(startingColor); };
};
