#include "CAnimNotifyState_Coliision.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction_Melee.h"
#include "Components/CActionComponent.h"

FString UCAnimNotifyState_Coliision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Coliision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ACDoAction_Melee* melee = Cast<ACDoAction_Melee>(action->GetCurrent()->GetDoAction());
	if (!!melee)
	{
		FString collisionName =  melee->GetCollisionName();
		action->GetCurrent()->GetAttachment()->OnCollision(collisionName);
	}
	else
		action->GetCurrent()->GetAttachment()->OnCollision();
}

void UCAnimNotifyState_Coliision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	action->GetCurrent()->GetAttachment()->OffCollision();
}
