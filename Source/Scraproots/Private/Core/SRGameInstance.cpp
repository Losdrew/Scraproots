// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "StreamingPauseRendering.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRGameInstance, Log, All);

void USRGameInstance::StartLoadingScreen()
{
	if (!LoadingScreenClass)
	{
		UE_LOG(LogSRGameInstance, Warning, TEXT("No LoadingScreenClass specified"));
		return;
	}

	UUserWidget* LoadingScreen = UUserWidget::CreateWidgetInstance(*this, LoadingScreenClass, FName());
	if (!LoadingScreen)
	{
		UE_LOG(LogSRGameInstance, Warning, TEXT("Failed to create LoadingScreen widget"));
		return;
	}

	UGameViewportClient* GameViewportClient = GetGameViewportClient();
	if (!GameViewportClient)
	{
		UE_LOG(LogSRGameInstance, Warning, TEXT("Failed to get GameViewportClient"));
		return;
	}

	LoadingScreenWidget = LoadingScreen->TakeWidget();
	GameViewportClient->AddViewportWidgetContent(LoadingScreenWidget.ToSharedRef(), 1000);
	bShowingLoadingScreen = true;
}

void USRGameInstance::StopLoadingScreen()
{
	if (!LoadingScreenWidget.IsValid())
	{
		UE_LOG(LogSRGameInstance, Warning, TEXT("No LoadingScreenWidget to remove"));
		return;
	}

	if (UGameViewportClient* GameViewportClient = GetGameViewportClient())
	{
		GameViewportClient->RemoveViewportWidgetContent(LoadingScreenWidget.ToSharedRef());
	}

	LoadingScreenWidget.Reset();
	bShowingLoadingScreen = false;
}

void USRGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnPostLoadMap);

	// Disable unwanted loading behaviour when opening levels
	GEngine->RegisterBeginStreamingPauseRenderingDelegate(nullptr);
}

void USRGameInstance::Shutdown()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
	Super::Shutdown();
}

void USRGameInstance::OnPostLoadMap(UWorld* World)
{
	if (bShowingLoadingScreen)
	{
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			OnLoadingFinishedDelegate.Broadcast();
		});

		World->GetTimerManager().SetTimer(LoadingScreenTimerHandle, TimerDelegate, PostMapLoadDelay, false);
	}
}

void USRGameInstance::Tick(float DeltaTime)
{
	FSlateApplication::Get().Tick();
}

ETickableTickType USRGameInstance::GetTickableTickType() const
{
	return ETickableTickType::Conditional;
}

bool USRGameInstance::IsTickable() const
{
	return !HasAnyFlags(RF_ClassDefaultObject) && bShowingLoadingScreen;
}

TStatId USRGameInstance::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(ULoadingScreenManager, STATGROUP_Tickables);
}

UWorld* USRGameInstance::GetTickableGameObjectWorld() const
{
	return GetWorld();
}
