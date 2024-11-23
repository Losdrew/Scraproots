// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SRInventoryTypes.h"
#include "SRInventoryComponent.generated.h"

enum class ESRInventoryMode : uint8;
struct FSRInventoryItem;
class UInputAction;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SCRAPROOTS_API USRInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
	void OpenInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
	void CloseInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
	void ToggleInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
	bool IsInventoryOpen() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(const FGameplayTag& ProductTag);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(const FGuid& ItemID);

protected:
	virtual void BeginPlay() override;
	void SetupInput();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Input")
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|UI")
	TSoftClassPtr<UUserWidget> InventoryWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory|UI")
	TObjectPtr<UUserWidget> InventoryWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TWeakObjectPtr<APlayerController> ControllerOwner;
};
