// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable/IInteractable.h"
#include "Interactable/InteractableActor.h"
#include "MoveableObjects.generated.h"

UCLASS()
class GGJ2026_API AMoveableObjects : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveableObjects();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Moveable")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Moveable")
	UPrimitiveComponent* InteractionCollision;*/

	UPROPERTY()
	FVector StartingPosition;
	UPROPERTY()
	FRotator StartingRotation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Moveable")
	FVector MaskedPosition;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Moveable")
	FRotator MaskedRotation;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moveable")
	bool OnlyInteractWithMaskOn = false;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdatePosAndRot(bool MaskStatus);

};
