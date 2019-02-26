// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Alt_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AAlt_Projectile::AAlt_Projectile()
{
	// Use a sphere as a simple collision representation
	Alt_CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	Alt_CollisionComp->InitSphereRadius(5.0f);
	Alt_CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	Alt_CollisionComp->OnComponentHit.AddDynamic(this, &AAlt_Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	Alt_CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Alt_CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = Alt_CollisionComp;

	// Use a Alt_ProjectileMovementComponent to govern this projectile's movement
	Alt_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Alt_ProjectileComp"));
	Alt_ProjectileMovement->UpdatedComponent = Alt_CollisionComp;
	Alt_ProjectileMovement->InitialSpeed = 3000.f;
	Alt_ProjectileMovement->MaxSpeed = 3000.f;
	Alt_ProjectileMovement->bRotationFollowsVelocity = true;
	Alt_ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AAlt_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		auto HitParam = GetActorLocation().ToString();
		UE_LOG(LogTemp, Warning, TEXT("Line 41 BallisticsProjectile.cpp || %s"), *HitParam)
			Destroy();
	}
}