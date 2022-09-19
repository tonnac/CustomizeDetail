#pragma once

struct FTestTable;

class FCustomizeDetailEditorHelperMethods
{
public:
	static const TMap<int32, FTestTable*>& GetTables();
	static const FTestTable* GetTable(int32 Key);
};
