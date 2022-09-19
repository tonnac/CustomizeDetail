#pragma once
#include "EditorViewportClient.h"

struct FTestEditorViewportClient : public FEditorViewportClient
{
	FTestEditorViewportClient();


	virtual void Tick(float DeltaTime) override;

	AActor* A;
};
