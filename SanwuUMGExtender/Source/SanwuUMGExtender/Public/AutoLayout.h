// Copyright 1998-2016 Sanwu Games, Inc. All Rights Reserved.
#pragma once
#include "Components/ContentWidget.h"
#include "AutoLayout.generated.h"

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