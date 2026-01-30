// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable/IInteractable.h"
#include "Interactable/InteractableActor.h"
#include "MaterialChangeObjects.generated.h"

UCLASS()
class GGJ2026_API AMaterialChangeObjects : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaterialChangeObjects();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MaterialChangeable")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MaterialChangeable")
	UPrimitiveComponent* InteractionCollision;*/

	UPROPERTY(EditAnywhere, Category="MaterialChangeable")
	UMaterialParameterCollection* ParameterCollection;

	UPROPERTY(EditAnywhere, Category="MaterialChangeable")
	TMap<FName, float> ScalarOverrides;

	UPROPERTY(EditAnywhere, Category="MaterialChangeable")
	TMap<FName, FLinearColor> VectorOverrides;

	UPROPERTY(EditAnywhere, Category="MaterialChangeable")
	bool VisibleWithMask = true;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MaterialChangeable")
	bool OnlyInteractWithMaskOn = false;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ChangeMaterial(bool MaskStatus);

private:

	UPROPERTY()
	TMap<FName, float> OriginalScalars;
	UPROPERTY()
	TMap<FName, FLinearColor> OriginalVectors;
	UPROPERTY()
	TObjectPtr<UMaterialParameterCollectionInstance> MPCInstance;
};
