#pragma once
#include "SBoxPanel.h"

///自动排列的容器组件。


class SAutoLayout :public SBoxPanel
{
public:
	class FSlot : public SBoxPanel::FSlot
	{
	public:

		FSlot()
			: SBoxPanel::FSlot()
		{
			}

		FSlot& AutoHeight()
		{
			SizeParam = FAuto();
			return *this;
		}

		FSlot& MaxHeight(const TAttribute< float >& InMaxHeight)
		{
			MaxSize = InMaxHeight;
			return *this;
		}

		FSlot& FillHeight(const TAttribute< float >& StretchCoefficient)
		{
			SizeParam = FStretch(StretchCoefficient);
			return *this;
		}

		DEPRECATED(4.5, "AspectRatio() property is no longer supported; it did not behave correctly to begin with and was rarely used.")
			FSlot& AspectRatio()
		{
				return *this;
			}

		FSlot& Padding(float Uniform)
		{
			SlotPadding = FMargin(Uniform);
			return *this;
		}

		FSlot& Padding(float Horizontal, float Vertical)
		{
			SlotPadding = FMargin(Horizontal, Vertical);
			return *this;
		}

		FSlot& Padding(float Left, float Top, float Right, float Bottom)
		{
			SlotPadding = FMargin(Left, Top, Right, Bottom);
			return *this;
		}

		FSlot& Padding(const TAttribute<FMargin>::FGetter& InDelegate)
		{
			SlotPadding.Bind(InDelegate);
			return *this;
		}

		FSlot& HAlign(EHorizontalAlignment InHAlignment)
		{
			HAlignment = InHAlignment;
			return *this;
		}

		FSlot& VAlign(EVerticalAlignment InVAlignment)
		{
			VAlignment = InVAlignment;
			return *this;
		}

		FSlot& Padding(TAttribute<FMargin> InPadding)
		{
			SlotPadding = InPadding;
			return *this;
		}

		FSlot& operator[](TSharedRef<SWidget> InWidget)
		{
			SBoxPanel::FSlot::operator[](InWidget);
			return *this;
		}

		FSlot& Expose(FSlot*& OutVarToInit)
		{
			OutVarToInit = this;
			return *this;
		}
	};

	static FSlot& Slot()
	{
		return *(new FSlot());
	}
	
public:
	SLATE_BEGIN_ARGS(SAutoLayout){}
	SLATE_ATTRIBUTE(FMargin,contentMargin)
	SLATE_SUPPORTS_SLOT(SAutoLayout::FSlot)
	SLATE_END_ARGS()

	FORCENOINLINE SAutoLayout()
	: SBoxPanel(Orient_Horizontal)
	{
	}

	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren)const override;
public:
	void Construct(const FArguments& InArgs);
	virtual FVector2D ComputeDesiredSize(float) const override;
	FSlot& AddSlot() {
		SAutoLayout::FSlot& NewSlot = *new FSlot();
		this->Children.Add(&NewSlot);
		return NewSlot;
	}
private:
	mutable FVector2D areaSize;
	mutable float areaHeight = 100;
	FMargin contentMargin;

};
