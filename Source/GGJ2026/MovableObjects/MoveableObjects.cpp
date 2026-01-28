// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableObjects/MoveableObjects.h"

#include "Components/BoxComponent.h"

// Sets default values
AMoveableObjects::AMoveableObjects()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	InteractionCollision->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void AMoveableObjects::BeginPlay()
{
	Super::BeginPlay();
	StartingPosition = GetActorLocation();
	StartingRotation = GetActorRotation();
}

// Called every frame
void AMoveableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoveableObjects::UpdatePosAndRot(bool MaskStatus)
{
	if (MaskStatus)
	{
		SetActorLocation(MaskedPosition);
		SetActorRotation(MaskedRotation);
	}
	else
	{
		SetActorLocation(StartingPosition);
		SetActorRotation(StartingRotation);
	}
}

