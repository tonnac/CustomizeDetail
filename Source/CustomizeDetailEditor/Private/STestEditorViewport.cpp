// Fill out your copyright notice in the Description page of Project Settings.


#include "STestEditorViewport.h"
#include "SlateOptMacros.h"
#include "TestEditorViewportClient.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STestEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
	
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

TSharedRef<FEditorViewportClient> STestEditorViewport::MakeEditorViewportClient()
{
	return MakeShareable(new FTestEditorViewportClient());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
