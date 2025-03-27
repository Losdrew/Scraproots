// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "SRGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSROnLoadingFinishedSignature);

UCLASS()
class SCRAPROOTS_API USRGameInstance : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartLoadingScreen();

	UFUNCTION(BlueprintCallable)
	void StopLoadingScreen();

	UFUNCTION(BlueprintCallable)
	bool IsShowingLoadingScreen() const { return bShowingLoadingScreen; }

public:
	UPROPERTY(BlueprintAssignable)
	FSROnLoadingFinishedSignature OnLoadingFinishedDelegate;

protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	
	void OnPostLoadMap(UWorld* World);

	//~FTickableObjectBase interface
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;
	//~End of FTickableObjectBase interface

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Loading")
	TSubclassOf<UUserWidget> LoadingScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Loading")
	float PostMapLoadDelay;

private:
	TSharedPtr<SWidget> LoadingScreenWidget;
	FTimerHandle LoadingScreenTimerHandle;
	bool bShowingLoadingScreen = false;
};
