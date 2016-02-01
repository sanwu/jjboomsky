// Fill out your copyright notice in the Description page of Project Settings.

#include "SanwuUEUtilitesPrivatePCH.h"
#include "ScreenShootTool.h"
#include "Engine.h"

FString UScreenShootTool::TakeScreenShoot(FString picName,bool bUnique)
{
	FString inStr;
	FString Filename;
	FScreenshotRequest::RequestScreenshot(picName + ".png", false, bUnique);
	FString ResultStr=FScreenshotRequest::GetFilename();
	ResultStr = FPaths::GetBaseFilename(ResultStr, true);
	return ResultStr+".png";
}
FString UScreenShootTool::GetBaseScreenShotPath()
{
	return  FPaths::ConvertRelativePathToFull(FPaths::ScreenShotDir());
}
