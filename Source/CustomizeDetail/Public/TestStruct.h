#pragma once

#include "TestStruct.generated.h"

USTRUCT()
struct CUSTOMIZEDETAIL_API FTestStruct
{
	GENERATED_BODY()

	static constexpr int32 Version = 2;

	friend FArchive& operator << (FArchive& Ar, FTestStruct& TestStruct);
	FArchive& ReadWriteCurrentVersion(FArchive& Ar);
	
	UPROPERTY(EditAnywhere, Category = "11")
	int32 TestValue = 0;

	UPROPERTY(EditAnywhere, Category = "22")
	float TestFloat = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "22")
	TMap<int32, int32> TestMap;
	
	UPROPERTY(EditAnywhere, Category = "22")
	int32 VersionTestValue = 0;
	
	UPROPERTY(EditAnywhere, Category = "22", meta=(HideInDetailPanel))
	int32 VersionTestValue_ = 0;
};

FORCEINLINE FArchive& operator<<(FArchive& Ar, FTestStruct& TestStruct)
{
	if (Ar.IsLoading())
	{
		int32 SavedVersion = 0;
		Ar << SavedVersion;

		switch (SavedVersion)
		{
		case 1:
			return Ar << TestStruct.TestValue << TestStruct.TestFloat << TestStruct.TestMap;
		case FTestStruct::Version:
			return TestStruct.ReadWriteCurrentVersion(Ar);
		default:
			return Ar;
		}
	}
	if (Ar.IsSaving())
	{
		static int32 CurrentVersion = FTestStruct::Version;
		return TestStruct.ReadWriteCurrentVersion(Ar << CurrentVersion);
	}
	return Ar;
}

FORCEINLINE FArchive& FTestStruct::ReadWriteCurrentVersion(FArchive& Ar)
{
	return Ar << TestValue << TestFloat << VersionTestValue << TestMap;
}
