// Copyright Epic Games, Inc. All Rights Reserved.

#include "SCommonPreLoadingScreenWidget.h"

#include "Widgets/Layout/SBorder.h"
#include "Widgets/Images/SThrobber.h"

class FReferenceCollector;

#define LOCTEXT_NAMESPACE "SCommonPreLoadingScreenWidget"

void SCommonPreLoadingScreenWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		.BorderBackgroundColor(FLinearColor::Black)
		.Padding(0)
        [
            SNew(SOverlay)
            + SOverlay::Slot()
            .HAlign(HAlign_Right)
            .VAlign(VAlign_Bottom)
            .Padding(FMargin(20))
            [
                SNew(SHorizontalBox)

                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Center)
                [
                    SNew(STextBlock)
                    .Text(FText::FromString("Loading"))
                    .Font(FSlateFontInfo(FPaths::ProjectContentDir() / TEXT("Scraproots/Fonts/KodeMono-Regular.ttf"), 24))
                    .ColorAndOpacity(FSlateColor(FLinearColor::White))
                ]

                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Center)
                .Padding(FMargin(22, 0, 0, 0))
                [
                    SNew(SCircularThrobber)
                        .NumPieces(13)
                        .Period(0.75f)
					    .Radius(27.f)
                ]
            ]
        ]
	];
}

void SCommonPreLoadingScreenWidget::AddReferencedObjects(FReferenceCollector& Collector)
{
	//WidgetAssets.AddReferencedObjects(Collector);
}

FString SCommonPreLoadingScreenWidget::GetReferencerName() const
{
	return TEXT("SCommonPreLoadingScreenWidget");
}

#undef LOCTEXT_NAMESPACE
