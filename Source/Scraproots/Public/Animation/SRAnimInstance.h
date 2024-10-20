// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "SRAnimInstance.generated.h"

class ASRBodyPart;

UCLASS()
class SCRAPROOTS_API USRAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	ASRBodyPart* GetBodyPartOwner() const;
};
