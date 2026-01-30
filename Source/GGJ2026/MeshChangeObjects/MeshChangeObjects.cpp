// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshChangeObjects/MeshChangeObjects.h"

#include "Components/BoxComponent.h"

// Sets default values
AMeshChangeObjects::AMeshChangeObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	/*PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(false);

	InteractionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollision"));
	InteractionCollision->SetupAttachment(RootComponent);

	InteractionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionCollision->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	InteractionCollision->SetGenerateOverlapEvents(false);*/
}

// Called when the game starts or when spawned
void AMeshChangeObjects::BeginPlay()
{
	Super::BeginPlay();
	if (Mesh)
	{
		OriginalMesh = Mesh->GetStaticMesh();
	}
}

// Called every frame
void AMeshChangeObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeshChangeObjects::ChangeMesh(bool MaskStatus)
{
	if (!Mesh || !AlternateMesh || !OriginalMesh) return;

	if (MaskStatus) Mesh -> SetStaticMesh(AlternateMesh);
	else Mesh -> SetStaticMesh(OriginalMesh);
}
