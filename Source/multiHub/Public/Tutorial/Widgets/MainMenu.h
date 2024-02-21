// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.h"
#include "MainMenu.generated.h"

class UButton;


USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	FString HostName;
	uint32 currentPlayerNum;
	uint32 maxPlayer;
};


UCLASS()
class MULTIHUB_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

	uint32 currentIndex;
	FString serverName = "";

	UFUNCTION()
	void OnHostBtnClicked();
	UFUNCTION()
	void OnJoinBtnClicked();
	UFUNCTION()
	void OnBackBtnClicked();
	UFUNCTION()
	void OnRefreshBtnClicked();
	UFUNCTION()
	void OnHostBackBtnClicked();
	UFUNCTION()
	void OnCreateBtnClicked();
	UFUNCTION()
	void OnServerNameTextChanged(const FText& text);

protected:
	//preconstruct is construct, construct is beginplay, and initialize is 
	virtual bool Initialize() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* joinBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* hostBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* backBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* refreshBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* connectBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* createBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* hostBackBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* serverNameBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* widgetSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidget* mainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidget* joinMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidget* hostMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPanelWidget* serverList;
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<class UServerRow> BP_ServerRow;

	UFUNCTION()
	void OnConnectBtnClicked();

	void SetUpServerList(const TArray<FServerData>& data);
	void SetIndex(uint32 index);
	FORCEINLINE	const FString& GetServerName() const { return this->serverName;};
	
	//Limits the text in given max letter number.
	UPROPERTY(EditAnywhere, Category = TextSize)
	int32 maxServerNameLength = 100;

};
