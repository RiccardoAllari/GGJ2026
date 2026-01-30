// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialChangeObjects/MaterialChangeObjects.h"

#include "Components/BoxComponent.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Sets default values
AMaterialChangeObjects::AMaterialChangeObjects()
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
void AMaterialChangeObjects::BeginPlay()
{
	Super::BeginPlay();
	if (!ParameterCollection) return;

	MPCInstance = GetWorld()->GetParameterCollectionInstance(ParameterCollection);
	if (!MPCInstance) return;

	for (const auto& Pair : ScalarOverrides)
	{
		float Value;
		if (MPCInstance->GetScalarParameterValue(Pair.Key, Value))
		{
			OriginalScalars.Add(Pair.Key, Value);
		}
	}
	
	for (const auto& Pair : VectorOverrides)
	{
		FLinearColor Value;
		if (MPCInstance->GetVectorParameterValue(Pair.Key, Value))
		{
			OriginalVectors.Add(Pair.Key, Value);
		}
	}

	if (VisibleWithMask == false)
	{
		Mesh->SetVisibility(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InteractionCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		Mesh->SetVisibility(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractionCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called every frame
void AMaterialChangeObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaterialChangeObjects::ChangeMaterial(bool MaskStatus)
{
	if (!MPCInstance) return;

	if (MaskStatus)
	{
		for (const auto& Pair : ScalarOverrides)
		{
			MPCInstance->SetScalarParameterValue(Pair.Key, Pair.Value);
		}

		for (const auto& Pair : VectorOverrides)
		{
			MPCInstance->SetVectorParameterValue(Pair.Key, Pair.Value);
		}
	}
	else
	{
		for (const auto& Pair : OriginalScalars)
		{
			MPCInstance->SetScalarParameterValue(Pair.Key, Pair.Value);
		}

		for (const auto& Pair : OriginalVectors)
		{
			MPCInstance->SetVectorParameterValue(Pair.Key, Pair.Value);
		}
	}
	if (VisibleWithMask && MaskStatus)
	{
		Mesh->SetVisibility(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InteractionCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		Mesh->SetVisibility(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractionCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

