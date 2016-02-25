#include "SanwuUMGExtenderPrivatePCH.h"
#include "SanwuUMGExtenderStyle.h"
#include "AutoFolding.h"
#include "SAutoFolding.h"

#define LOCTEXT_NAMESPACE "SanwuUMGExtender"

UAutoFolding::UAutoFolding(const FObjectInitializer& obj)
	:Super(obj)
{

}

void UAutoFolding::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UAutoFolding::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
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
	return Super::GetPaletteCategory();
}
#endif

TSharedRef<SWidget> UAutoFolding::RebuildWidget()
{
	TSharedPtr<SAutoFolding> btn = SNew(SAutoFolding);
	return btn->AsShared();
}

UClass* UAutoFolding::GetSlotClass() const
{
	return nullptr;
}

void UAutoFolding::OnSlotAdded(UPanelSlot* Slot)
{

}

void UAutoFolding::OnSlotRemoved(UPanelSlot* Slot)
{

}



