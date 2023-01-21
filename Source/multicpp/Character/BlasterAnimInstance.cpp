// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterAnimInstance.h"
#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(BlasterCharacter == nullptr)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}
	if (BlasterCharacter == nullptr) return;

	FVector Velocity = BlasterCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();

	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ?true : false;

	bWeaponEquipped = BlasterCharacter->IsWeaponEquipped();

	bIsCrouched = BlasterCharacter->bIsCrouched;

	bIsAiming = BlasterCharacter->IsAiming();

	//Offset Yaw for Strafing
	FRotator AimRotation = BlasterCharacter->GetBaseAimRotation(); //For Getting Aim direction
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasterCharacter->GetVelocity()); //For Getting Movement Direction
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6.f);
	YawOffset = DeltaRotation.Yaw;
	
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasterCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaSeconds;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.F);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	/*if (!BlasterCharacter->HasAuthority() && !BlasterCharacter->IsLocallyControlled())
	{
		/*
		UE_LOG(LogTemp, Warning, TEXT("AimRotation Yaw %f: "), AimRotation.Yaw);
		UE_LOG(LogTemp, Warning, TEXT("MovementRotaion Yaw %f: "), MovementRotaion.Yaw);
		#1#
		
		
	}*/
	
}
