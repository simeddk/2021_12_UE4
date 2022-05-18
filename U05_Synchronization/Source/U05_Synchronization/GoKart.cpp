#include "GoKart.h"

AGoKart::AGoKart()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector translation = Velocity * 100 * DeltaTime;
	AddActorWorldOffset(translation);

}

void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);

	
}

void AGoKart::MoveForward(float Value)
{
	Velocity = GetActorForwardVector() * 20 * Value;

}