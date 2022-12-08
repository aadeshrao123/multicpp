// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SphereComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Setting this false to stop tick if we want to change it in future we will set it to true
	

	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block); //Setting Collision Response to block from all channels So when we drop this weapon it will bounce off everything
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn/*Getting the pawn to set collision*/, ECollisionResponse::ECR_Ignore)/*Setting the collision for pawn*/;// After Dropping we want to ignore the pawn so pawn can run over it without colliding with it
	WeaponMesh->SetCollisionEnabled((ECollisionEnabled::NoCollision));// In start we want our weapon collision to be NoCollision

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Area Sphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels((ECollisionResponse::ECR_Ignore));
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

