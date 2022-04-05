#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(character);
	CheckNull(action);

	action->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());

	bFalling = character->GetCharacterMovement()->IsFalling();

	UCFeetComponent* feet = CHelpers::GetComponent<UCFeetComponent>(character);
	if (!!feet)
	{
		FeetData = feet->GetData();
		bIkMode = feet->IsIkMode();
	}
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPreType, EActionType InNewType)
{
	ActionType = InNewType;
}