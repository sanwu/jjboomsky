// Fill out your copyright notice in the Description page of Project Settings.

#include "SanwuUEUtilitesPrivatePCH.h"
#include "SanwuStringUtilityes.h"
TArray<FString> USanwuStringUtilityes::SplitStringToArray(FString SRC, FString Arg)
{
	TArray<FString>result;
	if (SRC.Contains(Arg,ESearchCase::CaseSensitive))
	{
		FString leftStr;
		FString rightStr;
		SRC.Split(Arg, &leftStr, &rightStr, ESearchCase::CaseSensitive);
		if (leftStr.Len()>0)
		{
			result.Add(leftStr);
		}
		result.Append(SplitStringToArray(rightStr, Arg));
		return result;
	}
	else {
		if (SRC.Len()>0)
		{
			result.Add(SRC);
		}
		return result;
	}
}
