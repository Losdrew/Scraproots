// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularCharacter/SRModularCharacter.h"
#include "SRRobot.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRRobotPreset : public FSRModularCharacterPreset
{
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRRobotData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
	FSRRobotPreset CharacterPreset;
};

UCLASS()
class SCRAPROOTS_API ASRRobot : public ASRModularCharacter
{
	GENERATED_BODY()

public:
	ASRRobot(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitializeFromPreset(const FSRModularCharacterPreset& Preset) override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Robot")
	TObjectPtr<USRRobotData> RobotDataAsset;
};
