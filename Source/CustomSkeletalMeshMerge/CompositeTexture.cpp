#include "CompositeTexture.h"
#include "Engine.h"
#include "Classes/Engine/Canvas.h"

#pragma optimize("", off)
UCompositeTexture::UCompositeTexture()
{
	Textures = nullptr;
	Boxes = nullptr;
	OnCanvasRenderTargetUpdate.AddDynamic(this, &UCompositeTexture::PerformMerge);
}

void UCompositeTexture::PerformMerge(UCanvas* Canvas, int32 CanvasWidth, int32 CanvasHeight)
{
	if (Textures && Boxes)
	{
		for (int32 i = 0; i < Textures->Num(); ++i)
		{
			UTexture2D* Texture = Cast<UTexture2D>((*Textures)[i]);
			if (Texture)
			{
				const FBox2D& Box = (*Boxes)[i];
				const FVector2D CanvasSize(CanvasWidth, CanvasHeight);
				const FVector2D Pos = Box.Min * CanvasSize;
				const FVector2D Size = Box.GetSize() * CanvasSize;
				Canvas->SetDrawColor(FColor::White);
				Canvas->DrawTile(Texture, Pos.X, Pos.Y, Size.X, Size.Y, 0, 0, Texture->GetSizeX(), Texture->GetSizeY());
			}
		}
	}
}

UCompositeTexture* UCompositeTexture::Create(UObject* WorldContextObject, const FIntPoint& Size, bool bNormal,
	const TArray<UTexture*>* Textures, const TArray<FBox2D>* Boxes)
{
	if (Size.X == 0 || Size.Y == 0 || !Textures || !Boxes || Textures->Num() != Boxes->Num() || Textures->Num() < 0)
		return nullptr;


	UCompositeTexture* RenderTarget = NewObject<UCompositeTexture>(GetTransientPackage());
	check(RenderTarget);

	RenderTarget->World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	RenderTarget->bAutoGenerateMips = true;
	RenderTarget->SizeX = Size.X;
	RenderTarget->SizeY = Size.Y;
	RenderTarget->OverrideFormat = bNormal ? PF_FloatRGBA : PF_B8G8R8A8;
	RenderTarget->bForceLinearGamma = true;

	RenderTarget->Textures = Textures;
	RenderTarget->Boxes = Boxes;

	RenderTarget->UpdateResource();

	return RenderTarget;
}
#pragma optimize("", on)
