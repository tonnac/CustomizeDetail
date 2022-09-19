#include "CustomizeDetailEditorHelperMethods.h"

#include "TestTable.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"

const TMap<int32, FTestTable*>& FCustomizeDetailEditorHelperMethods::GetTables()
{
	static TMap<int32, FTestTable*> Tables;

	if (Tables.Num() == 0)
	{
		FStreamableManager& StreamableManager =	UAssetManager::Get().GetStreamableManager();
		UDataTable* DataTable = CastChecked<UDataTable>(StreamableManager.LoadSynchronous(FSoftObjectPath(TEXT("DataTable'/Game/Table/TestTable.TestTable'"))));

		for (const TTuple<FName, uint8*>& RowMap : DataTable->GetRowMap())
		{
			FTestTable* Table = reinterpret_cast<FTestTable*>(RowMap.Value);
			Tables.Emplace(Table->NNN, reinterpret_cast<FTestTable*>(RowMap.Value));
		}
	}

	return Tables;
}

const FTestTable* FCustomizeDetailEditorHelperMethods::GetTable(int32 Key)
{
	const TMap<int32, FTestTable*>& a = GetTables();

	FTestTable* const* b = a.Find(Key);

	if (b)
	{
		return *b;
	}

	return nullptr;
}
