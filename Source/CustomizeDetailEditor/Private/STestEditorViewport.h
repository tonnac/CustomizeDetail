// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CUSTOMIZEDETAILEDITOR_API STestEditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(STestEditorViewport)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
};
