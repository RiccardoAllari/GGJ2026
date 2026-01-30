// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GGJ2026Character.generated.h"

class UMaskTimer;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaskStatusChange, bool, MaskStatus);

UCLASS(abstract)
class AGGJ2026Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ActivateMaskAction;
	
public:
	AGGJ2026Character();
	virtual void Tick(float DeltaSeconds) override;

protected:

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

protected:

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

public:

	FOnMaskStatusChange OnMaskStatusChange;
	
	UPROPERTY(EditDefaultsOnly, Category="JamParameters")
	float MaxInteractDistance = 300.f;
	UPROPERTY(EditAnywhere, Category="JamParameters")
	TWeakObjectPtr<AActor> CurrentInteractable;
	UPROPERTY(EditAnywhere, Category="JamParameters")
	TWeakObjectPtr<AActor> LastInteractable;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UDotUI> InteractDotClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMaskTimer> MaskTimerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UDotUI* InteractDotWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UMaskTimer* MaskTimerWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	bool MaskActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	bool HasMask = false;

	UFUNCTION()
	void UpdateInteractable();
	UFUNCTION()
	bool TraceForInteractable(FHitResult& OutHit);

	void OnStartLookingInteractable(AActor* Actor);
	void OnStopLookingInteractable(AActor* Actor);
	void TryInteract();
	void ShowInteractWidget(bool Show);

	UFUNCTION(BlueprintCallable, Category="Mask")
	bool IsMaskActive() const { return MaskActive; };
	void ActivateMask();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mask")
	float MaskTimer = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JamParameters")
	float MaxMaskTime = 30.f;
	
	FTimerHandle MaskTimerHandle;

	void UpdateMaskTimer();

	UFUNCTION(BlueprintCallable, Category="Mask")
	void MaskPickedUp();

protected:
	virtual void BeginPlay() override;

};

