// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MenuInterface.h"
#include "Components/Button.h"

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->_MenuInterface = MenuInterface;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if(Host==nullptr) return false;
	
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	
	return true;
}

void UMainMenu::HostServer()
{
	if(_MenuInterface==nullptr) return;
	_MenuInterface->Host();
}
