// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable/IInteractable.h"
#include "MoveableObjects.generated.h"

UCLASS()
class GGJ2026_API AMoveableObjects : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveableObjects();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactable")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactable")
	UPrimitiveComponent* InteractionCollision;

	UPROPERTY()
	FVector StartingPosition;
	UPROPERTY()
	FRotator StartingRotation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Moveable")
	FVector MaskedPosition;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Moveable")
	FRotator MaskedRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdatePosAndRot(bool MaskStatus);

};
