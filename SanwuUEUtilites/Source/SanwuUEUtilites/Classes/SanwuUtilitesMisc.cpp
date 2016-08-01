// Fill out your copyright notice in the Description page of Project Settings.

#include "SanwuUEUtilitesPrivatePCH.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SanwuUtilitesMisc.h"
DEFINE_LOG_CATEGORY_STATIC(LogSanwuUtilitesMisc, Warning, All);
void USanwuUtilitesMisc::RestartGameClient()
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "You Can`t use  \"RestartGameClient\" node with editor mode !");
	//return;
#endif
	FString RootPath = FPaths::RootDir();
	RootPath=RootPath.Replace(*FString("/"), *FString("\\"));
	FString GameExeFullPath=RootPath+ UKismetSystemLibrary::GetGameName() + ".exe";
	UE_LOG(LogSanwuUtilitesMisc, Warning, TEXT("%s"), *GameExeFullPath);
	FString Command=FString::Printf(TEXT("ping 127.0.0.1 -n 2 > nul\r\n@echo off\r\nstart %s"),*GameExeFullPath);
	FFileHelper::SaveStringToFile(Command, *(FPaths::GameSavedDir() / "RestartClient.bat"));
	FPlatformProcess::ExecProcess(*(FPaths::GameSavedDir() / "RestartClient.bat"), nullptr, nullptr, nullptr, nullptr);
	GEngine->Exec(GWorld, *FString("Exit"));
}