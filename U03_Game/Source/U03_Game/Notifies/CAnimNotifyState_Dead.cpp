#include "CAnimNotifyState_Dead.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Components/CActionComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


FString UCAnimNotifyState_Dead::GetNotifyName_Implementation() const
{
	return "Dead";
}

void UCAnimNotifyState_Dead::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//��� ������ �ø��� ����
	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);
	
	action->OffAllCollisions();

	//ĳ������ ĸ�� ����
	Cast<ACharacter>(MeshComp->GetOwner())->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCAnimNotifyState_Dead::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//ĳ������ ���� ����
	IICharacter* charcter = Cast<IICharacter>(MeshComp->GetOwner());
	CheckNull(charcter);

	charcter->ChangeColor(FLinearColor::Gray);
}