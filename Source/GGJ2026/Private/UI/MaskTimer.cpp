// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ2026/Public/UI/MaskTimer.h"
#include "Components/ProgressBar.h"

void UMaskTimer::SetProgress(float Progress)
{
	if (MaskProgressBar)
	{
		MaskProgressBar->SetPercent(Progress);
		
		FLinearColor Color = FMath::Lerp(FLinearColor(0.f, 1.f, 0.f, 1.f),FLinearColor(1.f, 0.f, 0.f, 1.f),Progress);

		MaskProgressBar->SetFillColorAndOpacity(Color);
	}
}

void UMaskTimer::SetProgressColor(const FLinearColor& Color)
{
	if (MaskProgressBar)
	{
		MaskProgressBar->SetFillColorAndOpacity(Color);
	}
}
