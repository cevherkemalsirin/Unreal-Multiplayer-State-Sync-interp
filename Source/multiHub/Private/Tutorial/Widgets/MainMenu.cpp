// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/Widgets/MainMenu.h"
#include "Tutorial/Widgets/ServerRow.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/PanelWidget.h"
#include "Components/EditableTextBox.h"


bool UMainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (hostBtn && joinBtn)
	{
		hostBtn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnHostBtnClicked);
		joinBtn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnJoinBtnClicked);
		connectBtn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnConnectBtnClicked);
		backBtn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnBackBtnClicked);
		refreshBtn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnRefreshBtnClicked);
		hostBackBtn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnHostBackBtnClicked);
		createBtn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnCreateBtnClicked);
		serverNameBox->OnTextChanged.AddUniqueDynamic(this, &UMainMenu::OnServerNameTextChanged);
	}
	else
	{
		return false;
	}
	return true;
}


void UMainMenu::SetUpServerList(const TArray<FServerData>& data)
{
	if (serverList)
	{
		serverList->ClearChildren();

		for (int i = 0; i < data.Num(); i++)
		{
			UServerRow* rowWidget =	CreateWidget<UServerRow>(this, BP_ServerRow);
			rowWidget->SetUp(this,i);
			rowWidget->SetServerInfo(data[i]);
			serverList->AddChild(rowWidget);
		}
	}

}


void UMainMenu::SetIndex(uint32 index)
{
	currentIndex = index;

	for (int i = 0; i <serverList->GetAllChildren().Num(); i++)
	{
		if (UServerRow* serverRow = Cast<UServerRow>(serverList->GetAllChildren()[i]))
		{
			if (i != currentIndex)
			{
				serverRow->SetSelected(false);
			}
		}
	}
}


void UMainMenu::OnHostBtnClicked()
{
	if (hostMenu && widgetSwitcher)
	{
		widgetSwitcher->SetActiveWidget(hostMenu);
	}
}


void UMainMenu::OnJoinBtnClicked()
{
	if (joinMenu && connecter && widgetSwitcher)
	{
		widgetSwitcher->SetActiveWidget(joinMenu);
		connecter->RefreshServerList();
	}
}


void UMainMenu::OnConnectBtnClicked()
{
	if (connecter)
	{
		connecter->Join(currentIndex);
	}
}


void UMainMenu::OnBackBtnClicked()
{
	if (mainMenu)
	{
		widgetSwitcher->SetActiveWidget(mainMenu);
	}
}


void UMainMenu::OnRefreshBtnClicked()
{
	if (serverList)
	{
		serverList->ClearChildren();
		if (connecter)
		{
			connecter->RefreshServerList();
		}
	}
}


void UMainMenu::OnCreateBtnClicked()
{
	serverName = serverNameBox->GetText().ToString();
	if (connecter)
	{
		connecter->Host();
	}
}


void UMainMenu::OnHostBackBtnClicked()
{
	if (mainMenu)
	{
		widgetSwitcher->SetActiveWidget(mainMenu);
		serverNameBox->SetText(FText::FromString(""));
	}
}


void UMainMenu::OnServerNameTextChanged(const FText& text)
{
	if (serverNameBox)
	{
		if (text.ToString().Len() >= maxServerNameLength)
		{
			serverNameBox->SetText(FText::FromString(text.ToString().Mid(0, maxServerNameLength)));
		}
	}
}






