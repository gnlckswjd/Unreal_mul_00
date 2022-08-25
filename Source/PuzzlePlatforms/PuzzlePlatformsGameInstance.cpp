// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystems/GameMenu.h"
#include "MenuSystems/MainMenu.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/MainMenu"));

	if(MenuBPClass.Class == nullptr)
	{
		return;
	}

	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> ExitMenuBPClass(TEXT("/Game/MenuSystem/ExitMenu"));

	if(ExitMenuBPClass.Class == nullptr)
	{
		return;
	}
	ExitMenuClass=ExitMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"),*MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if(!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure((Menu != nullptr))) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);

}



void UPuzzlePlatformsGameInstance::Host()
{

	if (Menu !=nullptr)
	{
		Menu->Teardown();
	}
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2,FColor::Green,TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{

	if(Menu != nullptr)
	{
		Menu->Teardown();
	}
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::GameMenu()
{
	if(!ensure(ExitMenuClass != nullptr)) return;
	ExitMenu = CreateWidget<UGameMenu>(this, ExitMenuClass);

	if (ExitMenu==nullptr) return;

	ExitMenu->Setup();

	ExitMenu->SetMenuInterface(this);
	
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(PlayerController == nullptr) return;

	PlayerController->ClientTravel("/Game/PuzzlePlatform/Maps/Main", ETravelType::TRAVEL_Absolute);
	
}

