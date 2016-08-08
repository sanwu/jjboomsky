// Fill out your copyright notice in the Description page of Project Settings.

#include "SanwuUEUtilitesPrivatePCH.h"
#include "SanwuStringUtilityes.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
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
class UTexture2D* USanwuStringUtilityes::GetTexture2DFromDiskFile(const FString& FilePath)
{
	TArray<uint8> RawFileData;
	UTexture2D* MyTexture = NULL;
	if (FFileHelper::LoadFileToArray(RawFileData, *FilePath /*"<path to file>"*/))
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		// Note: PNG format.  Other formats are supported
		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			const TArray<uint8>* UncompressedBGRA = NULL;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{
				// Create the UTexture for rendering
				MyTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

				// Fill in the source data from the file
				void* TextureData = MyTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
				MyTexture->PlatformData->Mips[0].BulkData.Unlock();

				// Update the rendering resource from data.
				MyTexture->UpdateResource();
			}
		}
	}
	return MyTexture;
}
