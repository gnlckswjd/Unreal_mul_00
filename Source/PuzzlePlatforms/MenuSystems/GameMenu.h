// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.generated.h"

class IMenuInterface;
class UButton;
class UWidget;
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup();

	void Teardown();

	UFUNCTION()
	void JoinToMenu();

	UFUNCTION()
	void CancelPressed();

	void SetMenuInterface(IMenuInterface* MenuInterface);
protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* InGameCancel;

	UPROPERTY(meta=(BindWidget))
	UButton* InGameMenu;

	class IMenuInterface* _MenuInterface;
	
};
