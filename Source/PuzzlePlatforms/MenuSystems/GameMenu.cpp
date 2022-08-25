// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"
#include "Components/Button.h"
#include "MenuInterface.h"
#include "../PuzzlePlatformsGameInstance.h"

void UGameMenu::Setup()
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

void UGameMenu::Teardown()
{
	UE_LOG(LogTemp, Warning, TEXT("test Tear"));
	
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

void UGameMenu::JoinToMenu()
{
	if(_MenuInterface== nullptr) return;
	Teardown();
	_MenuInterface->LoadMainMenu();
}

void UGameMenu::CancelPressed()
{
	
	Teardown();

}

bool UGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if(InGameCancel==nullptr) return false;
	InGameCancel->OnClicked.AddDynamic(this, &UGameMenu::CancelPressed);
	UE_LOG(LogTemp,Warning,TEXT("binding"));
	
	if(InGameMenu==nullptr) return false;
	InGameMenu->OnClicked.AddDynamic(this, &UGameMenu::JoinToMenu);
	
	return true;
}

void UGameMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->_MenuInterface = MenuInterface;
}
