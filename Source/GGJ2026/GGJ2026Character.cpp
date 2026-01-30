// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ2026Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GGJ2026.h"
#include "Blueprint/UserWidget.h"
#include "Interactable/IInteractable.h"
#include "Interactable/InteractableActor.h"
#include "Kismet/GameplayStatics.h"
#include "GGJ2026/Public/UI/DotUI.h"
#include "GGJ2026/Public/UI/MaskTimer.h"

AGGJ2026Character::AGGJ2026Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void AGGJ2026Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateInteractable();
}

void AGGJ2026Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AGGJ2026Character::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGGJ2026Character::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGGJ2026Character::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGGJ2026Character::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AGGJ2026Character::LookInput);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AGGJ2026Character::TryInteract);
		EnhancedInputComponent->BindAction(ActivateMaskAction, ETriggerEvent::Triggered, this, &AGGJ2026Character::ActivateMask);
	}
	else
	{
		UE_LOG(LogGGJ2026, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AGGJ2026Character::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void AGGJ2026Character::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AGGJ2026Character::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AGGJ2026Character::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AGGJ2026Character::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void AGGJ2026Character::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void AGGJ2026Character::UpdateInteractable()
{
	LastInteractable = CurrentInteractable;
	CurrentInteractable = nullptr;

	FHitResult Hit;
	if (TraceForInteractable(Hit))
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor && HitActor -> GetClass()-> ImplementsInterface(UInteractable::StaticClass()))
		{
			AInteractableActor* InteractableActor = Cast<AInteractableActor>(HitActor);
			if (!InteractableActor->NeverInteractable)
			{
				if (InteractableActor->OnlyInteractWithMaskOn)
				{
					if (MaskActive)
					{
						CurrentInteractable = InteractableActor;
					}
				}
				else
				{
					CurrentInteractable = HitActor;
				}
			}
		}
	}
	
	if (LastInteractable != CurrentInteractable)
	{
		if (LastInteractable.IsValid())
		{
			OnStopLookingInteractable(LastInteractable.Get());
		}
		if (CurrentInteractable.IsValid())
		{
			OnStartLookingInteractable(CurrentInteractable.Get());
		}
	}
}

bool AGGJ2026Character::TraceForInteractable(FHitResult& OutHit)
{
	FVector Start;
	FRotator Rot;
	Controller -> GetPlayerViewPoint(Start, Rot);

	FVector End = Start + Rot.Vector() * MaxInteractDistance;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool Hit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params);

	return Hit;
}

void AGGJ2026Character::TryInteract()
{
	if (!CurrentInteractable.IsValid()) return;
	
	AActor* Actor = CurrentInteractable.Get();
	
	if (Actor -> GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_Interact(Actor, this);
	}
}

void AGGJ2026Character::OnStartLookingInteractable(AActor* Actor)
{
	if (!IsValid(Actor)) return;
	InteractDotWidget->SetDotActive(true);
}

void AGGJ2026Character::OnStopLookingInteractable(AActor* Actor)
{
	if (!IsValid(Actor)) return;
	InteractDotWidget->SetDotActive(false);

}

void AGGJ2026Character::ActivateMask()
{
	if (!HasMask) return;

	// Prevent spam
	if (bMaskTransitionLocked)
		return;

	bMaskTransitionLocked = true;

	// Disable input
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);
	}

	// Start fade out
	FadeOutMask();
}

void AGGJ2026Character::UpdateMaskTimer()
{
	MaskTimer += 0.05f;

	float Progress = FMath::Clamp(MaskTimer / MaxMaskTime, 0.f, 1.f);
	
	if (MaskTimerWidget)
	{
		MaskTimerWidget->SetProgress(Progress);
	}

	if (MaskTimer >= MaxMaskTime)
	{
		GetWorldTimerManager().ClearTimer(MaskTimerHandle);

		UE_LOG(LogTemp, Warning, TEXT("GAME OVER: Mask Timer reached max"));
		// Game over logic
	}
}

void AGGJ2026Character::MaskPickedUp()
{
	HasMask = true;
	if (MaskTimerWidget)
	{
		MaskTimerWidget -> AddToViewport();
	}
	
}

void AGGJ2026Character::FadeOutMask()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->PlayerCameraManager->StartCameraFade(0.f, 1.f, FadeDuration, FLinearColor::Black, false, true);

	// Wait FadeDuration + small buffer before fade in
	GetWorldTimerManager().SetTimer(
		MaskFadeTimerHandle,
		this,
		&AGGJ2026Character::FadeInMask,
		FadeDuration + 0.05f,
		false
	);
}

void AGGJ2026Character::FadeInMask()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	// Activate the mask now
	MaskActive = !MaskActive;
	OnMaskStatusChange.Broadcast(MaskActive);

	if (MaskActive)
	{
		// Start timer
		GetWorldTimerManager().SetTimer(MaskTimerHandle, this, &AGGJ2026Character::UpdateMaskTimer, 0.05f, true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(MaskTimerHandle);
	}

	// Fade back in
	PC->PlayerCameraManager->StartCameraFade(1.f, 0.f, FadeDuration, FLinearColor::Black, false, false);

	// Start cooldown timer
	GetWorldTimerManager().SetTimer(
		MaskCooldownTimerHandle,
		this,
		&AGGJ2026Character::UnlockMaskInteraction,
		FadeDuration - 0.5f,
		false
	);
}

void AGGJ2026Character::UnlockMaskInteraction()
{
	bMaskTransitionLocked = false;

	// Re-enable input
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->SetIgnoreMoveInput(false);
		PC->SetIgnoreLookInput(false);
	}
}

void AGGJ2026Character::BeginPlay()
{
	Super::BeginPlay();
	if (InteractDotClass)
	{
		InteractDotWidget = CreateWidget<UDotUI>(GetWorld(), InteractDotClass);
		if (InteractDotWidget)
		{
			InteractDotWidget->AddToViewport();
		}
	}
	if (MaskTimerClass)
	{
		MaskTimerWidget = CreateWidget<UMaskTimer>(GetWorld(), MaskTimerClass);
	}
}
