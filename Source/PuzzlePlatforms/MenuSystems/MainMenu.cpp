// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MenuInterface.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->_MenuInterface = MenuInterface;
}

void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();

	if(World == nullptr) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (PlayerController == nullptr)
	{
		return;
	}
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor=true;
}

void UMainMenu::Teardown()
{
	this->RemoveFromViewport();
	
	
	UWorld* World = GetWorld();

	if(World == nullptr) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (PlayerController == nullptr)
	{
		return;
	}

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor=false;
	
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if(HostButton==nullptr) return false;
	
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if(JoinButton==nullptr) return false;
	
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if(CancelButton==nullptr) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::CancelMenu);

	if(JoinTwoButton==nullptr) return false;
	JoinTwoButton->OnClicked.AddDynamic(this, &UMainMenu::JoinToGame);
	
	return true;
}

void UMainMenu::HostServer()
{
	if(_MenuInterface==nullptr) return;
	_MenuInterface->Host();
}

void UMainMenu::OpenJoinMenu()
{ 
	if(MenuSwitcher == nullptr) return;
	if(JoinMenu == nullptr) return;
	
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::CancelMenu()
{
	if(MenuSwitcher == nullptr) return;
	if(Menu == nullptr) return;
	MenuSwitcher->SetActiveWidget(Menu);
}

void UMainMenu::JoinToGame()
{
	if (_MenuInterface==nullptr) return;

	FText IPText = IPAddressField->GetText();
	_MenuInterface->Join(IPText.ToString());
	
	
}
