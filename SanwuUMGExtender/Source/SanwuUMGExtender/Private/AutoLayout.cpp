#include "SanwuUMGExtenderPrivatePCH.h"
#include "SanwuUMGExtenderStyle.h"
#include "AutoLayout.h"

#define LOCTEXT_NAMESPACE "SanwuUMGExtender"

UAutoLayout::UAutoLayout(const FObjectInitializer&ObjectInitializer)
	:Super(ObjectInitializer)
{

}
void UAutoLayout::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
}
TSharedRef<SWidget> UAutoLayout::RebuildWidget()
{
	TSharedPtr<SButton> btn = SNew(SButton);
	return btn->AsShared();
}
void UAutoLayout::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}
void UAutoLayout::PostLoad()
{
	Super::PostLoad();
}
#if WITH_EDITOR
const FSlateBrush* UAutoLayout::GetEditorIcon()
{
	return FSanwuUMGExtenderStyle::Get().GetBrush("Widget.AutoLayoutIcon");
}
const FText UAutoLayout::GetPaletteCategory()
{
	return LOCTEXT("Sanwu","Sanwu");
}
#endif

#undef LOCTEXT_NAMESPACE