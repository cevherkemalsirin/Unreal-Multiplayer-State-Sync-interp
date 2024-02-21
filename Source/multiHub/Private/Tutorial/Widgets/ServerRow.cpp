// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/Widgets/ServerRow.h"
#include "Components/TextBlock.h"
#include "Tutorial/Widgets/MainMenu.h"
#include "Components/Button.h"


void UServerRow::SetServerInfo(const FServerData& data)
{
	this->serverName->SetText(FText::FromString(data.Name));
	this->hostName->SetText(FText::FromString(data.HostName));
	this->playerCount->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"),data.currentPlayerNum,data.maxPlayer)));
}


void UServerRow::SetUp(UMainMenu* parentValue, uint32 indexValue)
{
	this->startingColor = this->GetColorAndOpacity();
	this->parent = parentValue;
	this->index = indexValue;
	this->isSelected = false;
	if (rowBtn)
	{
		rowBtn->OnClicked.AddUniqueDynamic(this, &UServerRow::OnServerClicked);
	}
}


void UServerRow::OnServerClicked()
{
	if (isSelected)
	{
		this->parent->OnConnectBtnClicked();
	}
	else
	{
		this->SetSelected(true);
		parent->SetIndex(index);
	}
}
