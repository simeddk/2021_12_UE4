#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class U03_GAME_API ACHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;

public:
	FORCEINLINE void OnDraw() { bDraw = true; }
	FORCEINLINE void OffDraw() { bDraw = false; }
	
public:
	ACHUD();

	virtual void DrawHUD() override;

private:
	bool bDraw;
};
