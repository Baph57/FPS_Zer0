// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "BallisticsProjectile.h"
#include "Animation/AnimInstance.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" 
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/InputComponent.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	SetRootComponent(FP_Gun);
	FP_Gun->SetOnlyOwnerSee(false);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 44.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AGun::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
//{
//	// set up gameplay key bindings
//	check(PlayerInputComponent);
//
//	// Bind fire event
//	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGun::OnFire);
//}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();


		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			//Added ammo functionality
			if (AmmoCount > 0)
			{
				// spawn the projectile at the muzzle
				World->SpawnActor<ABallisticsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				AmmoCount--;

			}
		}

		if (AmmoCount > 0) {
			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			// First person designation for animations
			if (FireAnimation1P != nullptr && AnimInstance1P != nullptr)
			{
				// Get the animation object for the arms mesh
				AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);
			}

			// Third person designation for animations
			if (FireAnimation3P != nullptr && AnimInstance3P != nullptr)
			{
				// Get the animation object for the arms mesh
				AnimInstance3P->Montage_Play(FireAnimation3P, 1.f);
			}
		}
	}
}

void AGun::AltFire()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();


		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			//Added ammo functionality
			if (AltAmmoCount > 0)
			{
				// spawn the projectile at the muzzle
				World->SpawnActor<ABallisticsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				AltAmmoCount--;

			}
		}

		if (AltAmmoCount > 0) {
			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			// First person designation for animations
			if (FireAnimation1P != nullptr && AnimInstance1P != nullptr)
			{
				// Get the animation object for the arms mesh
				AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);
			}

			// Third person designation for animations
			if (FireAnimation3P != nullptr && AnimInstance3P != nullptr)
			{
				// Get the animation object for the arms mesh
				AnimInstance3P->Montage_Play(FireAnimation3P, 1.f);
			}
		}
	}
}