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

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* MaskOff;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* MaskOn;

public:
	UFUNCTION(BlueprintCallable)
	void SetProgress(float Progress);

	UFUNCTION(BlueprintCallable)
	void SetProgressColor(const FLinearColor& Color);

	UFUNCTION(BlueprintCallable)
	void SetMaskImage(bool MaskStatus);
};
