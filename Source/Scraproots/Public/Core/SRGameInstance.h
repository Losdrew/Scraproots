// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "SRGameInstance.generated.h"

class USRInventoryManager;
class USRProductManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSROnLoadingFinishedSignature);

UCLASS()
class SCRAPROOTS_API USRGameInstance : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RestartGame();

	UFUNCTION(BlueprintCallable)
	void StartLoadingScreen(TSoftClassPtr<UUserWidget> LoadingScreenClass);

	UFUNCTION(BlueprintCallable)
	void StopLoadingScreen();

	UFUNCTION(BlueprintCallable)
	bool IsShowingLoadingScreen() const { return bShowingLoadingScreen; }

	virtual USRInventoryManager* GetInventoryManager() const { return InventoryManager; }
	virtual USRProductManager* GetProductManager() const { return ProductManager; }

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
	float PostMapLoadDelay;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Inventory Manager")
	TObjectPtr<USRInventoryManager> InventoryManager;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Product")
	TObjectPtr<USRProductManager> ProductManager;

private:
	TSharedPtr<SWidget> LoadingScreenWidget;
	FTimerHandle LoadingScreenTimerHandle;
	bool bShowingLoadingScreen = false;
};
