#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class U03_GAME_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	
public:
	virtual void Tick(float DeltaTime) override;


private:
	class ACPlayer* UseCursorLocation();
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation);

private:
	class UDecalComponent* Decal;
	FVector Location;
};
