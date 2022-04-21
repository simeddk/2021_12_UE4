#include "CVertexActor.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"


ACVertexActor::ACVertexActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UProceduralMeshComponent>(this, &Mesh, "Mesh");

	float width = 50, height = 50, depth = 50;

	//Front
	Vertices.Add(FVector(-depth, -width, -height));//������
	Vertices.Add(FVector(-depth, -width, +height));//���»�
	Vertices.Add(FVector(-depth, +width, -height));//�տ���
	Vertices.Add(FVector(-depth, +width, +height));//�տ��
	AddFace(0);

	//Back
	Vertices.Add(FVector(+depth, -width, -height));//������
	Vertices.Add(FVector(+depth, +width, -height));//�ڿ���
	Vertices.Add(FVector(+depth, -width, +height));//���»�
	Vertices.Add(FVector(+depth, +width, +height));//�ڿ��
	AddFace(4);

	//Top
	Vertices.Add(FVector(-depth, -width, +height)); //���»�
	Vertices.Add(FVector(+depth, -width, +height)); //���»�
	Vertices.Add(FVector(-depth, +width, +height)); //�տ��
	Vertices.Add(FVector(+depth, +width, +height)); //�ڿ��
	AddFace(8);

	//Bottom
	Vertices.Add(FVector(-depth, -width, -height)); //������
	Vertices.Add(FVector(-depth, +width, -height)); //�տ���
	Vertices.Add(FVector(+depth, -width, -height)); //������
	Vertices.Add(FVector(+depth, +width, -height)); //�ڿ���
	AddFace(12);

	//Left
	Vertices.Add(FVector(+depth, -width, -height)); //������
	Vertices.Add(FVector(+depth, -width, +height));	//���»�
	Vertices.Add(FVector(-depth, -width, -height));	//������
	Vertices.Add(FVector(-depth, -width, +height));	//���»�
	AddFace(16);

	//Right
	Vertices.Add(FVector(-depth, +width, -height)); //�տ���
	Vertices.Add(FVector(-depth, +width, +height));	//�տ��
	Vertices.Add(FVector(+depth, +width, -height));	//�ڿ���
	Vertices.Add(FVector(+depth, +width, +height));	//�ڿ��
	AddFace(20);

	Mesh->CreateMeshSection
	(
		0,
		Vertices,
		Indices,
		TArray<FVector>(),
		TArray<FVector2D>(),
		TArray<FColor>(),
		TArray<FProcMeshTangent>(),
		true
	);
}

void ACVertexActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < Vertices.Num(); i++)
		Vertices[i] += FVector(0, 0, Speed * DeltaTime);

	Mesh->UpdateMeshSection
	(
		0,
		Vertices,
		TArray<FVector>(),
		TArray<FVector2D>(),
		TArray<FColor>(),
		TArray<FProcMeshTangent>()
	);
}


void ACVertexActor::AddFace(uint32 InStart)
{
	Indices.Add(InStart + 2);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 0);

	Indices.Add(InStart + 2);
	Indices.Add(InStart + 3);
	Indices.Add(InStart + 1);
}