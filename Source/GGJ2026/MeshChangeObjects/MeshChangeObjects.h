// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable/IInteractable.h"
#include "MeshChangeObjects.generated.h"

UCLASS()
class GGJ2026_API AMeshChangeObjects : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshChangeObjects();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactable")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactable")
	UPrimitiveComponent* InteractionCollision;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Changeable")
	UStaticMesh* AlternateMesh;

	UPROPERTY()
	UStaticMesh* OriginalMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ChangeMesh(bool MaskStatus);
};
