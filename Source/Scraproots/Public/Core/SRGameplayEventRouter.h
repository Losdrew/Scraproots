// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "SRGameplayEventRouter.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRGameplayEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay Event")
	FGameplayTag EventTag;	// Represents the event using a Gameplay Tag

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay Event")
	FString Payload;  // Additional data, can be JSON or structured as needed

	bool IsEmpty() const
	{
		return EventTag == FGameplayTag::EmptyTag;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("EventTag: %s, Payload: %s"), *EventTag.ToString(), *Payload);
	}

	FSRGameplayEvent()
	{
		EventTag = FGameplayTag::EmptyTag;
		Payload = TEXT("");
	}

	FSRGameplayEvent(const FGameplayTag& InEventTag, const FString& InPayload)
	{
		EventTag = InEventTag;
		Payload = InPayload;
	}

	// Get Payload as a GameplayTag
	FGameplayTag GetPayloadAsGameplayTag() const
	{
		return Payload.IsEmpty() ? FGameplayTag::EmptyTag : FGameplayTag::RequestGameplayTag(FName(Payload, false));
	}

	// Get Payload as an Integer
	int32 GetPayloadAsInt() const
	{
		return Payload.IsEmpty() ? 0 : FCString::Atoi(*Payload);
	}

	// Get Payload as a Float
	float GetPayloadAsFloat() const
	{
		return Payload.IsEmpty() ? 0.0f : FCString::Atof(*Payload);
	}

	// Get Payload as a Boolean
	bool GetPayloadAsBool() const
	{
		return Payload.Equals(TEXT("true"), ESearchCase::IgnoreCase) || Payload.Equals(TEXT("1"));
	}

	// Get Payload as a Name
	FName GetPayloadAsName() const
	{
		return FName(*Payload, FNAME_Find);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSRGameplayEventDelegate, const FSRGameplayEvent&, Event);

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRGameplayEventRouter : public UObject
{
	GENERATED_BODY()

public:
	// Broadcast a structured event
	UFUNCTION(BlueprintCallable, Category = "Gameplay Events")
	void Broadcast(const FSRGameplayEvent& Event) const;

	// Delegate for listeners
	UPROPERTY(BlueprintAssignable, Category = "Gameplay Events")
	FSRGameplayEventDelegate OnGameplayEvent;
};