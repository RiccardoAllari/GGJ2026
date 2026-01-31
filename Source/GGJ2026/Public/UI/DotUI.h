// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DotUI.generated.h"

/**
 * 
 */

class UImage;

UCLASS()
class GGJ2026_API UDotUI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	UImage* DotImage;
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	UImage* InteractKey;

	UPROPERTY(EditAnywhere)
	UTexture2D* InteractionPng;
	UPROPERTY(EditAnywhere)
	UTexture2D* StandardDot;
	
public:
	UFUNCTION(BlueprintCallable, Category="Dot")
	void SetDotActive(bool Active);
};
