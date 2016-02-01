#include "SanwuUMGExtenderPrivatePCH.h"
#include "SanwuUMGExtenderStyle.h"
#include "IPluginManager.h"
TSharedPtr<FSlateStyleSet> FSanwuUMGExtenderStyle::UMGStyleInstance = nullptr;
void FSanwuUMGExtenderStyle::Initialize()
{
	if (!UMGStyleInstance.IsValid())
	{
		UMGStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*UMGStyleInstance);
	}
}

void FSanwuUMGExtenderStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*UMGStyleInstance);
	ensure(UMGStyleInstance.IsUnique());
	UMGStyleInstance.Reset();
}
FName FSanwuUMGExtenderStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SanwuUMGExtenderStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.f, 16.f);

TSharedRef<FSlateStyleSet>FSanwuUMGExtenderStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("SanwuUMGExtenderStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("SanwuUMGExtender")->GetBaseDir() / TEXT("Resources"));
	Style->Set("Widget.AutoLayoutIcon", new IMAGE_BRUSH(TEXT("imags/AutoLayoutIcon"), Icon16x16));
	
	return Style;
}
#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT
void FSanwuUMGExtenderStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FSanwuUMGExtenderStyle::Get()
{
	return *UMGStyleInstance;
}