// Copyright 1998-2016 Sanwu Games, Inc. All Rights Reserved.
#pragma once
#include "Components/ContentWidget.h"
#include "AutoLayout.generated.h"
/**
* AutoLayout 是一个盛放对象的容器。 
* 当AutoLayout的宽高发生变化时，里面的子对象会自动适应
* 比如做一个相册。每个照片宽度是10 AutoLayout宽度为100，那横向则能放10张照片。
* 这时候，当AutoLayout宽度变为90时。里面的照片会自动重新排列，变成一行9个
*/
UCLASS()
class SANWUUMGEXTENDER_API UAutoLayout : public UContentWidget
{
	GENERATED_UCLASS_BODY()
public:

public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

};