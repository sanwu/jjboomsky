#pragma once
#include "Components/PanelSlot.h"
#include "SlateWrapperTypes.h"
#include "SAutoFolding.h"

#include "AutoFoldingSlot.generated.h"

UCLASS()
class SANWUUMGEXTENDER_API UAutoFoldingSlot : public UPanelSlot
{
	GENERATED_UCLASS_BODY()

public:
	/** The padding area between the slot and the content it contains. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Vertical Box Slot")
		FMargin Padding;

	/** How much space this slot should occupy in the direction of the panel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Vertical Box Slot")
		FSlateChildSize Size;

	/** The alignment of the object horizontally. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Vertical Box Slot")
		TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;

	/** The alignment of the object vertically. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout|Vertical Box Slot")
		TEnumAsByte<EVerticalAlignment> VerticalAlignment;

	UFUNCTION(BlueprintCallable, Category = "Layout|Vertical Box Slot")
		void SetPadding(FMargin InPadding);

	UFUNCTION(BlueprintCallable, Category = "Layout|Vertical Box Slot")
		void SetSize(FSlateChildSize InSize);

	UFUNCTION(BlueprintCallable, Category = "Layout|Vertical Box Slot")
		void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);

	UFUNCTION(BlueprintCallable, Category = "Layout|Vertical Box Slot")
		void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);

public:
	void BuildSlot(TSharedRef<SAutoFolding> InAutoFolding);
	// UPanelSlot interface
	virtual void SynchronizeProperties() override;
	// End of UPanelSlot interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
private:
	SAutoFolding::FSlot* Slot;
};