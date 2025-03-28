// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRStatics.h"

#include "Core/SRGameplayEventRouter.h"
#include "Core/SRGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Core/SRGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRStatics, Log, All);

USRGameplayEventRouter* USRStatics::GetGameplayEventRouter(const UObject* WorldContextObject)
{
	if (const ASRGameMode* GameMode = Cast<ASRGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return GameMode->GameplayEventRouter;
	}

	return nullptr;
}

bool USRStatics::BroadcastGameplayEvent(const UObject* WorldContextObject, const FSRGameplayEvent& Event)
{
	if (const USRGameplayEventRouter* GameplayEventRouter = GetGameplayEventRouter(WorldContextObject))
	{
		GameplayEventRouter->Broadcast(Event);
		return true;
	}

	return false;
}

AActor* USRStatics::FindActorByName(const UObject* WorldContextObject, const FString& ObjectName)
{
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		UE_LOG(LogSRStatics, Error, TEXT("USRStatics::FindActorByName: Invalid World"));
		return nullptr;
	}

	for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
	{
		FString ActorName = ActorItr->GetName();
		if (ActorName == ObjectName)
		{
			return *ActorItr;
		}
	}

	return nullptr;
}

USRInventoryManager* USRStatics::GetInventoryManager(const UObject* WorldContextObject)
{
	if (const USRGameInstance* GameInstance = Cast<USRGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject)))
	{
		return GameInstance->GetInventoryManager();
	}

	return nullptr;
}

USRProductManager* USRStatics::GetProductManager(const UObject* WorldContextObject)
{
	if (const USRGameInstance* GameInstance = Cast<USRGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject)))
	{
		return GameInstance->GetProductManager();
	}

	return nullptr;
}
