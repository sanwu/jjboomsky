#pragma once
#include "SBoxPanel.h"

class SAutoFolding : public SVerticalBox
{
public:
	class FSlot : public SVerticalBox::FSlot
	{
		public:
			FSlot() :SVerticalBox::FSlot()
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
				SVerticalBox::FSlot::operator[](InWidget);
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

	SLATE_BEGIN_ARGS(SAutoFolding)
	{
		_Visibility = EVisibility::SelfHitTestInvisible;
	}
	SLATE_ATTRIBUTE(FMargin, contentMargin)
	SLATE_SUPPORTS_SLOT(SAutoFolding::FSlot)

	SLATE_END_ARGS()

	FSlot& AddSlot()
	{
		SAutoFolding::FSlot& NewSlot = *new SAutoFolding::FSlot();
		this->Children.Add(&NewSlot);
		return NewSlot;
	}
	
	FSlot& InsertSlot(int32 Index = INDEX_NONE)
	{
		if (Index == INDEX_NONE)
		{
			return AddSlot();
		}
		SAutoFolding::FSlot &NewSlot = *new SAutoFolding::FSlot();
		this->Children.Insert(&NewSlot, Index);
		return NewSlot;
	}

	int32 NumSlots() const
	{
		return this->Children.Num();
	}

	FORCENOINLINE SAutoFolding()
		:SVerticalBox()
	{
			
	}
		
	void Construct(const FArguments& InArgs);

public:
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual void InitFoldingTitle();
private:
	FMargin contentMargin;
	mutable FVector2D areaSize;
	bool b_HaveChild = false; //如果含有子节点，则显示“+”，没有则不显示
	bool b_Activation = true; //是否点开打开子节点显示（没有子节点不让打开，有子节点打开则显示“-”）/ 编辑状态默认打开，设计的时候可以看到子节点情况，运行则关闭
};