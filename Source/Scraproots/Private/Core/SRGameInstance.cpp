// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Core/SRAssetManager.h"
#include "Inventory/SRInventoryManager.h"
#include "Levels/SRLevelSettings.h"
#include "Levels/SRLevelSubsystem.h"
#include "Levels/SRLevelUtilities.h"
#include "Product/SRProductManager.h"
#include "Product/SRProductSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRGameInstance, Log, All);

void USRGameInstance::StartLoadingScreen(TSoftClassPtr<UUserWidget> LoadingScreenClass)
{
	if (LoadingScreenClass.IsNull())
	{
		UE_LOG(LogSRGameInstance, Warning, TEXT("No LoadingScreenClass specified"));
		return;
	}

	USRAssetManager& AssetManager = USRAssetManager::Get();
	AssetManager.LoadClassAsync<UUserWidget>(LoadingScreenClass, TDelegate<void(TSubclassOf<UUserWidget>)>::CreateWeakLambda(this, [this](TSubclassOf<UUserWidget> LoadedWidgetClass)
	{
		UUserWidget* LoadingScreen = UUserWidget::CreateWidgetInstance(*this, LoadedWidgetClass, FName());
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
	}));
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

	ProductManager = NewObject<USRProductManager>(this);
	checkf(ProductManager, TEXT("ProductManager is not set in the SRGameMode!"));
	if (ProductManager)
	{
		const USRProductSettings* ProductSettings = GetDefault<USRProductSettings>();
		ProductManager->Initialize(ProductSettings->ProductsConfig);
	}

	InventoryManager = NewObject<USRInventoryManager>(this);
	checkf(InventoryManager, TEXT("InventoryManager is not set in the SRGameMode!"));
	if (InventoryManager)
	{
		InventoryManager->Initialize();
	}
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
	RETURN_QUICK_DECLARE_CYCLE_STAT(USRGameInstance, STATGROUP_Tickables);
}

UWorld* USRGameInstance::GetTickableGameObjectWorld() const
{
	return GetWorld();
}

void USRGameInstance::RestartGame()
{
	InventoryManager->ClearData();
	InventoryManager->Initialize();

	USRLevelSubsystem* LevelSubsystem = GetSubsystem<USRLevelSubsystem>();
	if (LevelSubsystem)
	{
		LevelSubsystem->ResetLevelSubsystem();
	}

	const USRLevelSettings* LevelSettings = GetDefault<USRLevelSettings>();
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("LevelSettings is null"));
		return;
	}

	const TMap<FName, FSRLevelList>& LevelMap = LevelSettings->LevelConfig;
	const FSRLevelList* OpeningLevelList = LevelMap.Find("Opening_Level");

	if (!OpeningLevelList || OpeningLevelList->Levels.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Opening_Level not found or empty"));
		return;
	}

	const FSRLevel& OpeningLevel = OpeningLevelList->Levels[0];
	USRLevelUtilities::OpenLevel(this, OpeningLevel);
}
