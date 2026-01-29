// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableObjects/MOveableObjectsManager.h"

#include "GGJ2026Character.h"
#include "MoveableObjects.h"
#include "Kismet/GameplayStatics.h"
#include "MaterialChangeObjects/MaterialChangeObjects.h"
#include "MeshChangeObjects/MeshChangeObjects.h"

// Sets default values
AMOveableObjectsManager::AMOveableObjectsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMOveableObjectsManager::BeginPlay()
{
	Super::BeginPlay();
	AGGJ2026Character* Character = Cast<AGGJ2026Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	if (!Character) return;

	for (AMoveableObjects* Moveable : MoveableObjects)
	{
		if (IsValid(Moveable))
		{
			Character->OnMaskStatusChange.AddDynamic(Moveable, &AMoveableObjects::UpdatePosAndRot);
		}
	}

	for (AMeshChangeObjects* MeshChangeObject : MeshChangeObjects)
	{
		if (IsValid(MeshChangeObject))
		{
			Character->OnMaskStatusChange.AddDynamic(MeshChangeObject, &AMeshChangeObjects::ChangeMesh);
		}
	}

	for (AMaterialChangeObjects* MaterialChangeObject : MaterialChangeObjects)
	{
		if (IsValid(MaterialChangeObject))
		{
			Character->OnMaskStatusChange.AddDynamic(MaterialChangeObject, &AMaterialChangeObjects::ChangeMaterial);
		}
	}
}

void AMOveableObjectsManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AGGJ2026Character* Character = Cast<AGGJ2026Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (Character)
	{
		for (AMoveableObjects* Moveable : MoveableObjects)
		{
			if (IsValid(Moveable))
			{
				Character->OnMaskStatusChange.RemoveDynamic(Moveable, &AMoveableObjects::UpdatePosAndRot);
			}
		}
	}

	if (Character)
	{
		for (AMeshChangeObjects* MeshChangeObject : MeshChangeObjects)
		{
			if (IsValid(MeshChangeObject))
			{
				Character->OnMaskStatusChange.RemoveDynamic(MeshChangeObject, &AMeshChangeObjects::ChangeMesh);
			}
		}
	}

	if (Character)
	{
		for (AMaterialChangeObjects* MaterialChangeObject : MaterialChangeObjects)
		{
			if (IsValid(MaterialChangeObject))
			{
				Character->OnMaskStatusChange.RemoveDynamic(MaterialChangeObject, &AMaterialChangeObjects::ChangeMaterial);
			}
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AMOveableObjectsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMOveableObjectsManager::FillMoveableArray()
{
	MoveableObjects.Empty();

	if (!GetWorld())
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMoveableObjects::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (AMoveableObjects* Moveable = Cast<AMoveableObjects>(Actor))
		{
			MoveableObjects.Add(Moveable);
		}
	}

	#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Collected %d MoveableObjects"), MoveableObjects.Num());
		if (!IsRunningGame())
		{
			Modify();
		}
	#endif
}

void AMOveableObjectsManager::FillMeshChangeArray()
{
	MeshChangeObjects.Empty();
	
	if (!GetWorld())
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMeshChangeObjects::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (AMeshChangeObjects* Changeable = Cast<AMeshChangeObjects>(Actor))
		{
			MeshChangeObjects.Add(Changeable);
		}
	}
	#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Collected %d MeshChangeableObjects"), MeshChangeObjects.Num());
		if (!IsRunningGame())
		{
			Modify();
		}
	#endif
}

void AMOveableObjectsManager::FillMaterialChangeArray()
{
	MaterialChangeObjects.Empty();
	
	if (!GetWorld())
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMaterialChangeObjects::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (AMaterialChangeObjects* Changeable = Cast<AMaterialChangeObjects>(Actor))
		{
			MaterialChangeObjects.Add(Changeable);
		}
	}
	#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Collected %d MaterialChangeObjects"), MaterialChangeObjects.Num());
		if (!IsRunningGame())
		{
			Modify();
		}
	#endif
}

