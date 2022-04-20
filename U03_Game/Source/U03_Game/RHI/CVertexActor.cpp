#include "CVertexActor.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"


ACVertexActor::ACVertexActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UProceduralMeshComponent>(this, &Mesh, "Mesh");

	float width = 50, height = 50, depth = 50;

	Vertices.Add(FVector(-depth, -width, -height));//������
	Vertices.Add(FVector(-depth, -width, +height));//���»�
	Vertices.Add(FVector(-depth, +width, -height));//�տ���
	Vertices.Add(FVector(-depth, +width, +height));//�տ��
	AddFace(0); //Todo
}

void ACVertexActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACVertexActor::AddFace(uint32 InStart)
{

}