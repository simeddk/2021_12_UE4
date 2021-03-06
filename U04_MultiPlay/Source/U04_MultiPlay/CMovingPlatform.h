#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CMovingPlatform.generated.h"

UCLASS()
class U04_MULTIPLAY_API ACMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		int32 ActiveTriggers = 1;
	
public:
	ACMovingPlatform();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void AddActiveTrigger();
	void RemoveActiveTrigger();


private:
	UPROPERTY(EditAnywhere)
		float Speed = 20.0f;
	
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
		FVector TargetLocation;

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

};
