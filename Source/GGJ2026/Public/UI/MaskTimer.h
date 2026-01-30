// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MaskTimer.generated.h"

/**
 * 
 */

class UProgressBar;

UCLASS()
class GGJ2026_API UMaskTimer : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* MaskProgressBar;

public:
	UFUNCTION(BlueprintCallable)
	void SetProgress(float Progress);

	UFUNCTION(BlueprintCallable)
	void SetProgressColor(const FLinearColor& Color);
};
