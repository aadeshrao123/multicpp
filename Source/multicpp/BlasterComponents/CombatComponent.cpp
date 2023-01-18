// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "multicpp/Character/BlasterCharacter.h"
#include "multicpp/Weapon/Weapon.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCombatComponent::SetAiming(bool bIsAiming)
{
	bAiming = bIsAiming; // It is not important but I am writing this so the client whi is pressing aim button doesn't need to wait for the information to reach server it will directly show on clients machine and next line will send the information to server also 
	ServerSetAiming(bIsAiming);// For send ing aim button pressed info to server
}

void UCombatComponent::ServerSetAiming_Implementation(bool bIsAiming)
{
	bAiming = bIsAiming;
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCombatComponent, EquippedWeapon);
	DOREPLIFETIME(UCombatComponent, bAiming);
}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (BlasteraCharacter == nullptr || WeaponToEquip == nullptr) return;
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	if (const USkeletalMeshSocket* HandSocket = BlasteraCharacter->GetMesh()->GetSocketByName(FName("WeaponSocket"))) //for checking if hand socket is null or not if not then proceed
	{
		HandSocket->AttachActor(EquippedWeapon, BlasteraCharacter->GetMesh());
	}
	EquippedWeapon->SetOwner(BlasteraCharacter); // Setting the owner as Blaster character after picking up the weapon
}

