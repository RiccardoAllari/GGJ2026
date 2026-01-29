// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOveableObjectsManager.generated.h"

class AMaterialChangeObjects;
class AMeshChangeObjects;
class AMoveableObjects;

UCLASS()
class GGJ2026_API AMOveableObjectsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMOveableObjectsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AMoveableObjects*> MoveableObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AMeshChangeObjects*> MeshChangeObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AMaterialChangeObjects*> MaterialChangeObjects;

	UFUNCTION(CallInEditor, Category="FillArrays")
	void FillMoveableArray();

	UFUNCTION(CallInEditor, Category="FillArrays")
	void FillMeshChangeArray();

	UFUNCTION(CallInEditor, Category="FillArrays")
	void FillMaterialChangeArray();

};
