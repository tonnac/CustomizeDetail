// Fill out your copyright notice in the Description page of Project Settings.


#include "STestTab.h"

#include "SlateOptMacros.h"
#include "STestEditorViewport.h"
#include "Blueprint/UserWidget.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STestTab::Construct(const FArguments& InArgs)
{
	FStreamableManager& StreamableManager =	UAssetManager::Get().GetStreamableManager();
	const UBlueprintCore* BlueprintCore = CastChecked<UBlueprintCore>(StreamableManager.LoadSynchronous(FSoftObjectPath{TEXT("WidgetBlueprint'/Game/NewWidgetBlueprint1.NewWidgetBlueprint1'")}));
	auto b = CreateWidget(PreviewScene.GetWorld(), *BlueprintCore->GeneratedClass);

	int32 mn = 53;

	ChildSlot
	[
		SNew(SSplitter)
		.Orientation(Orient_Vertical)

		+ SSplitter::Slot()
		.Value(0.3f)
		[
			SNew(STestEditorViewport)
		]

		+ SSplitter::Slot()
		.Value(0.7f)
		[
			SNew(SBorder)
			[
				b->TakeWidget()
			]
		]
	];

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

STestTab::STestTab()
	: PreviewScene(FPreviewScene::ConstructionValues().AllowAudioPlayback(true).ShouldSimulatePhysics(true))
{
}
