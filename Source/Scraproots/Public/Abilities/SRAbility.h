// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SRAbility.generated.h"

UENUM(BlueprintType)
enum class ESRAbilityType : uint8
{
	Movement,
	Attack,
	Utility,
	Other
};

UCLASS()
class SCRAPROOTS_API ASRAbility : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (DisplayPriority = 1))
	ESRAbilityType AbilityType;

	// Additional priority used for sorting.
	// Higher priority means the ability will be placed first in the list.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (DisplayPriority = 2))
	int32 Priority = 0;
};
