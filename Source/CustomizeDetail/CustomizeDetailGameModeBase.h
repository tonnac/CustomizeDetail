// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomizeDetailGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMIZEDETAIL_API ACustomizeDetailGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


	virtual void BeginPlay() override;
};
