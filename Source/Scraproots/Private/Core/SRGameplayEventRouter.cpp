// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRGameplayEventRouter.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRGameplayEventRouter, Log, All);

void USRGameplayEventRouter::Broadcast(const FSRGameplayEvent& Event) const
{
	OnGameplayEvent.Broadcast(Event);

	UE_LOG(LogSRGameplayEventRouter, Log, TEXT("Broadcasting event: %s"), *Event.ToString());
}
