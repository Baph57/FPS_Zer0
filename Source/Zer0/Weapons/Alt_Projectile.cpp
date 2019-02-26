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

		//on hit, deactivate our launchblast particles, enable impact particles, and fire our explosion physics
		LaunchBlast->Deactivate();
		ImpactBlast->Activate();
		ExplosionForce->FireImpulse();

		//setting new root component for reference and deleting our initial static mesh component
		SetRootComponent(ImpactBlast);
		Alt_CollisionComp->DestroyComponent();

		//damage
		UGameplayStatics::ApplyRadialDamage(
			this, //where the damage is applied from
			ProjectileDamage, //amount of damage to apply
			GetActorLocation(), //getting the location of our projectile in the world
			ExplosionForce->Radius, //damaging radius, 'looking through' explosion force and just grabbing/using its radius
			UDamageType::StaticClass(), //Lookup documentation for further detail
			TArray<AActor*>() //damage all actors within the radius
		);

		//setting our timer
		FTimerHandle Timer;

		//get world, get time manager, set a timer, give it our above timer, run our method after timer
		//and give the timer our delay for destroy()
		GetWorld()->GetTimerManager().SetTimer(
			Timer,
			this,
			&AProjectile::OnTimerExpire,
			DestroyDelay,
			false
		);
	}
}

void AAlt_Projectile::LaunchProjectile(float Speed)
{
	//using previously declared forward vector of our tank barrel
	TankProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);

	//now that we have projectile speed we will activate the movement
	TankProjectileMovement->Activate();
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}
