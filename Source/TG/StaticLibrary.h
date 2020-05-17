// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UStaticLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	template<typename TEnum>
	static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value);
	template<typename TEnum>
	static FORCEINLINE TArray<TEnum> EnumGetList(const FString& Name);
};

template<typename TEnum>
FORCEINLINE FString UStaticLibrary::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return FString("InValid");
	}
	else
	{
		FString TempString = EnumPtr->GetNameByValue((int64)Value).ToString();
		TempString.RemoveFromStart(Name + "::");
		return TempString;
	}
}

template<typename TEnum>
FORCEINLINE TArray<TEnum>
UStaticLibrary::EnumGetList(const FString& Name)
{
	TArray<TEnum> Result;
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	for (int i = 0; i < pEnum->GetMaxEnumValue(); i++)
	{
		if (pEnum->IsValidEnumValue(i))
		{
			Result.Add(static_cast<TEnum>(i));
		}
	}
	return Result;
}

template <typename EnumType>
static FORCEINLINE EnumType GetEnumValueFromString(const FString& EnumName, const FString& String) {
	UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	if (!Enum) {
		return EnumType(0);
	}
	return (EnumType)Enum->FindEnumIndex(FName(*String));
}