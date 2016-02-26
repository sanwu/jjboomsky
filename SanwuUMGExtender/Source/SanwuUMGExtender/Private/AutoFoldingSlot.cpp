#include "SanwuUMGExtenderPrivatePCH.h"
#include "AutoFoldingSlot.h"

UAutoFoldingSlot::UAutoFoldingSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	, Slot(NULL)
{
	HorizontalAlignment = HAlign_Fill;
	VerticalAlignment = VAlign_Fill;
	Size = FSlateChildSize(ESlateSizeRule::Automatic);
}

void UAutoFoldingSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	Slot = NULL;
}

void UAutoFoldingSlot::BuildSlot(TSharedRef<SAutoFolding> InAutoFolding)
{
	Slot = &InAutoFolding->AddSlot()
		.Padding(Padding)
		.HAlign(HorizontalAlignment)
		.VAlign(VerticalAlignment)
		[
			Content == NULL ? SNullWidget::NullWidget : Content->TakeWidget()
		];
	Slot->SizeParam = UWidget::ConvertSerializedSizeParamToRuntime(Size);
}

void UAutoFoldingSlot::SetPadding(FMargin InPadding)
{
	Padding = InPadding;
	if (Slot)
	{
		Slot->Padding(InPadding);
	}
}

void UAutoFoldingSlot::SetSize(FSlateChildSize InSize)
{
	Size = InSize;
	if (Slot)
	{
		Slot->SizeParam = UWidget::ConvertSerializedSizeParamToRuntime(InSize);
	}
}

void UAutoFoldingSlot::SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if (Slot)
	{
		Slot->HAlign(InHorizontalAlignment);
	}
}

void UAutoFoldingSlot::SetVerticalAlignment(EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	if (Slot)
	{
		Slot->VAlign(InVerticalAlignment);
	}
}

void UAutoFoldingSlot::SynchronizeProperties()
{
	SetPadding(Padding);
	SetSize(Size);
	SetHorizontalAlignment(HorizontalAlignment);
	SetVerticalAlignment(VerticalAlignment);
}


