// Copyright 1998-2016 Sanwu Games, Inc. All Rights Reserved.
#pragma once
#include "Components/ContentWidget.h"
#include "AutoLayout.h"
#include "AutoFolding.generated.h"

UCLASS()
class SANWUUMGEXTENDER_API UAutoFolding : public UAutoLayout
{
	GENERATED_UCLASS_BODY()
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;

protected:
	TSharedPtr<class SAutoFolding> MyAutoFolding;
	virtual TSharedRef<SWidget> RebuildWidget() override;
};