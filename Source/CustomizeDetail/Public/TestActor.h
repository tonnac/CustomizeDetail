// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestStruct.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

USTRUCT()
struct FMyStruct
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category="111")
	int32 Category111 = 32;
	
	UPROPERTY(EditAnywhere, Category="222")
	int32 Category222 = 33;
	
	UPROPERTY(EditAnywhere, Category="333")
	int32 Category333 = 34;
};

UCLASS()
class CUSTOMIZEDETAIL_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

public:
	UPROPERTY(EditAnywhere, Category = "TestStruct")
	FTestStruct TestStruct;

	UPROPERTY(EditAnywhere, Category="3334")
	FMyStruct MyStruct;
	
	UPROPERTY(EditAnywhere, Category="3335")
	int32 Value = 555;

	UPROPERTY(EditAnywhere, Category="3335")
	FSlateColor Color;
	

};
