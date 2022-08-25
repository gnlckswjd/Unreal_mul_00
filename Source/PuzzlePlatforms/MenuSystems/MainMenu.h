// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.h"
#include "MainMenu.generated.h"

/**
 * 
 */
class IMenuInterface;
class UButton;
class UWidget;

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{

	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

	void Teardown();

protected:
	virtual bool Initialize() override;

private:
		
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta=(BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta=(BindWidget))
	UButton* JoinTwoButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ExitButton;
	
	
	UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta=(BindWidget))
	UWidget* Menu;
	
	UPROPERTY(meta =(BindWidget))
	class UEditableTextBox* IPAddressField;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void CancelMenu();

	UFUNCTION()
	void JoinToGame();

	UFUNCTION()
	void EXitGame();

	IMenuInterface* _MenuInterface;
};
