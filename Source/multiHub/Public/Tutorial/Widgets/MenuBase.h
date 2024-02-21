// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Connectable.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class MULTIHUB_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	IConnectable* connecter;
	
public:
	
	void Setup();
	void Remove();

	FORCEINLINE void SetConnector(IConnectable* c) { this->connecter = c; };
};
