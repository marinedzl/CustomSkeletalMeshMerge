#pragma once
#include "EngineMinimal.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "CompositeTexture.generated.h"

UCLASS(Blueprintable)
class UCompositeTexture : public UCanvasRenderTarget2D
{
	GENERATED_BODY()

	UCompositeTexture();

	UFUNCTION()
	void PerformMerge(UCanvas* Canvas, int32 Width, int32 Height);
public:
	static UCompositeTexture* Create(UObject* WorldContextObject, const FIntPoint& Size, const TArray<UTexture*>* Textures, const TArray<FBox2D>* Boxes);
private:
	const TArray<UTexture*>* Textures;
	const TArray<FBox2D>* Boxes;
};
