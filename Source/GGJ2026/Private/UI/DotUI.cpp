// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ2026/Public/UI/DotUI.h"
#include "Components/Image.h"

void UDotUI::SetDotActive(bool Active)
{
	if (!DotImage) return;

	if (Active)
	{
		//DotImage->SetColorAndOpacity(FLinearColor::Red);
		DotImage ->SetBrushFromTexture(InteractionPng);
		InteractKey->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		//DotImage->SetColorAndOpacity(FLinearColor::White);
		DotImage ->SetBrushFromTexture(StandardDot);
		InteractKey->SetVisibility(ESlateVisibility::Hidden);
	}
}