#pragma once
#include "Engine/DataTable.h"
#include "TestTable.generated.h"

USTRUCT(BlueprintType)
struct CUSTOMIZEDETAIL_API FTestTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 NNN;

	UPROPERTY(EditAnywhere)
	FText AAA;
};
