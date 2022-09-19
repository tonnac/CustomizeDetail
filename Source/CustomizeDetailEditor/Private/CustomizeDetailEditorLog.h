#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogCustomizeDeatilEditor, Log, All);
#define FUNCTION_LINE *FString::Printf(TEXT("[%s:%d]"), TEXT(__FUNCTION__), __LINE__)
#define DETAIL_EDITOR_LOG(Format, ...) UE_LOG(LogCustomizeDeatilEditor, Log, TEXT("%s %s"), FUNCTION_LINE, *FString::Printf(Format, ##__VA_ARGS__))
#define DETAIL_EDITOR_WARNING(Format, ...) UE_LOG(LogCustomizeDeatilEditor, Warning, TEXT("%s %s"), FUNCTION_LINE, *FString::Printf(Format, ##__VA_ARGS__))
#define DETAIL_EDITOR_ERROR(Format, ...) UE_LOG(LogCustomizeDeatilEditor, Error, TEXT("%s %s"), FUNCTION_LINE, *FString::Printf(Format, ##__VA_ARGS__))
