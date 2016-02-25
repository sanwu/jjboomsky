#include "SanwuUMGExtenderPrivatePCH.h"
#include "SAutoLayout.h"

void SAutoLayout::Construct(const FArguments& InArgs)
{
	const int32 NumSlots = InArgs.Slots.Num();
	contentMargin = InArgs._contentMargin.Get();
	for (int32 SlotIndex = 0; SlotIndex < NumSlots; ++SlotIndex)
	{
		Children.Add(InArgs.Slots[SlotIndex]);
	}
	
}
void SAutoLayout::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren)const
{
	areaSize = AllottedGeometry.GetLocalSize();
	float startX = contentMargin.Left;
	float startY = contentMargin.Top;
	float currentMaxHeight = 0.f;
	for (int32 ChildIndex = 0; ChildIndex < Children.Num(); ++ChildIndex)
	{
		const SBoxPanel::FSlot& CurChild = Children[ChildIndex];
		const EVisibility ChildVisibility = CurChild.GetWidget()->GetVisibility();
		FVector2D size = CurChild.GetWidget()->GetDesiredSize();
		if (ArrangedChildren.Accepts(ChildVisibility))
		{
			if (size.Y>currentMaxHeight)
			{
				currentMaxHeight = size.Y;
			}


			if (startX+size.X<areaSize.X)
			{
				ArrangedChildren.AddWidget(ChildVisibility, AllottedGeometry.MakeChild(CurChild.GetWidget(), FVector2D(startX, startY), FVector2D(size.X, size.Y)));
				startX += contentMargin.Right;
				startX += size.X;
			}
			else{
				startX = contentMargin.Left;
				startY += currentMaxHeight + contentMargin.Bottom;
				ArrangedChildren.AddWidget(ChildVisibility, AllottedGeometry.MakeChild(CurChild.GetWidget(), FVector2D(startX, startY), FVector2D(size.X, size.Y)));
				startX += size.X + contentMargin.Right;
				currentMaxHeight = size.Y;
			}

		}
	}
	areaHeight = startY + currentMaxHeight + contentMargin.Bottom + contentMargin.Top;
}
FVector2D SAutoLayout::ComputeDesiredSize(float)const
{
	return FVector2D(100,areaHeight);
}
