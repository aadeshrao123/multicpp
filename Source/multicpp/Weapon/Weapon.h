// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),

	EWS_MAX UMETA(DisplayName = "DefaultMAX")

};


UCLASS()
class MULTICPP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	USkeletalMeshComponent* WeaponMesh; //Creating Skeletal Mesh For Weapon
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	class USphereComponent* AreaSphere; // Sphere for collision for picking  up the weapon

	UPROPERTY(VisibleAnywhere)
	EWeaponState WeaponState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
