// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UCLASS()
class GGJ2026_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactable")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactable")
	UPrimitiveComponent* InteractionCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interactable")
	bool OnlyInteractWithMaskOn = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
