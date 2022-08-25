// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystems/MainMenu.h"
#include "MenuSystems/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

	UFUNCTION(BlueprintCallable)
	void GameMenu();
	class UMainMenu* Menu;
private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> ExitMenuClass;
	
	
	class UGameMenu* ExitMenu;

	virtual  void LoadMainMenu() override;
	
};
