// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/SRInventoryComponent.h"

#include "Core/SRStatics.h"
#include "EnhancedInputComponent.h"
#include "Inventory/SRInventoryManager.h"
#include "Inventory/SRInventoryTypes.h"

void USRInventoryComponent::BeginPlay()
{
	ControllerOwner = Cast<APlayerController>(GetOwner());
	SetupInput();

	Super::BeginPlay();
}

void USRInventoryComponent::SetupInput()
{
	if (!ControllerOwner.IsValid())
	{
		return;
	}

	if (UEnhancedInputComponent* InputComponent = Cast<UEnhancedInputComponent>(ControllerOwner->InputComponent))
	{
		InputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &ThisClass::ToggleInventory);
	}
}

void USRInventoryComponent::AddItem(const FGameplayTag& ProductTag)
{
	if (USRInventoryManager* InventoryManager = USRStatics::GetInventoryManager(this))
	{
		InventoryManager->AddProduct(ProductTag);
	}
}

void USRInventoryComponent::RemoveItem(const FGuid& ItemID)
{
	if (USRInventoryManager* InventoryManager = USRStatics::GetInventoryManager(this))
	{
		InventoryManager->RemoveItem(ItemID);
	}
}
