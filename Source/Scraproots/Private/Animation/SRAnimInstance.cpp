// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/SRAnimInstance.h"

#include "ModularCharacter/Parts/SRBodyPart.h"

ASRBodyPart* USRAnimInstance::GetBodyPartOwner() const
{
	if (AActor* OwningActor = GetOwningActor())
	{
		return Cast<ASRBodyPart>(OwningActor);
	}
	return nullptr;
}
