// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PreviewScene.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CUSTOMIZEDETAILEDITOR_API STestTab : public SCompoundWidget
{
public:
	STestTab();
	
	SLATE_BEGIN_ARGS(STestTab)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
private:
	/** The preview scene that owns the preview GUI */
	FPreviewScene PreviewScene;
};
