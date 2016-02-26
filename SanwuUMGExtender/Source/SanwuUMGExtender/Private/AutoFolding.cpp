#include "SanwuUMGExtenderPrivatePCH.h"
#include "SanwuUMGExtenderStyle.h"
#include "AutoFolding.h"
#include "SAutoFolding.h"
#include "AutoFoldingSlot.h"

#define LOCTEXT_NAMESPACE "SanwuUMGExtender"

UAutoFolding::UAutoFolding(const FObjectInitializer& obj)
	:Super(obj)
{
	bIsVariable = false;
	SAutoFolding::FArguments Defaults;
	Visiblity_DEPRECATED = Visibility = UWidget::ConvertRuntimeToSerializedVisibility(Defaults._Visibility.Get());
}

void UAutoFolding::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UAutoFolding::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyAutoFolding.Reset();
}

void UAutoFolding::PostLoad()
{
	Super::PostLoad();
}
#if WITH_EDITOR
const FSlateBrush* UAutoFolding::GetEditorIcon()
{
	return FSanwuUMGExtenderStyle::Get().GetBrush("Widget.AutoFoldingIcon");
}

const FText UAutoFolding::GetPaletteCategory()
{
	return LOCTEXT("Sanwu", "Sanwu");
}
#endif

TSharedRef<SWidget> UAutoFolding::RebuildWidget()
{
	//if (!b_DoOnce)
	//{
	//	TSharedPtr<SButton> btn = SNew(SButton);
	//	b_DoOnce = !b_DoOnce;
	//	return btn->AsShared();
	//}

	MyAutoFolding = SNew(SAutoFolding);
	for (UPanelSlot* Slot : Slots)
	{
		if (UAutoFoldingSlot* TypedSlot = Cast<UAutoFoldingSlot>(Slot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyAutoFolding.ToSharedRef());
		}
	}
	return BuildDesignTimeWidget(MyAutoFolding.ToSharedRef());
}

UClass* UAutoFolding::GetSlotClass() const
{
	return UAutoFoldingSlot::StaticClass();
}

void UAutoFolding::OnSlotAdded(UPanelSlot* Slot)
{
	if (MyAutoFolding.IsValid())
	{
		Cast<UAutoFoldingSlot>(Slot)->BuildSlot(MyAutoFolding.ToSharedRef());
	}
}

void UAutoFolding::OnSlotRemoved(UPanelSlot* Slot)
{
	if (MyAutoFolding.IsValid())
	{
		TSharedPtr<SWidget> Widget = Slot->Content->GetCachedWidget();
		if (Widget.IsValid())
		{
			MyAutoFolding->RemoveSlot(Widget.ToSharedRef());
		}
	}
}

UAutoFoldingSlot* UAutoFolding::AddChildToAutoFolding(UWidget* Content)
{
	return Cast<UAutoFoldingSlot>(Super::AddChild(Content));
}

#undef LOCTEXT_NAMESPACE
