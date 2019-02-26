// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Alt_Projectile.generated.h"

UCLASS(config = Game)
class AAlt_Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* Alt_CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* Alt_ProjectileMovement;




public:
	AAlt_Projectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns Alt_CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetAlt_CollisionComp() const { return Alt_CollisionComp; }
	/** Returns Alt_ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetAlt_ProjectileMovement() const { return Alt_ProjectileMovement; }

	// Creates the projectile and launching along forward vector of barrel with given speed
	void LaunchProjectile(float Speed);


private:

	//Firing visual effects
	UPROPERTY(VisibleAnywhere, Category = Custom)
	UParticleSystemComponent* LaunchBlast = nullptr;

	//Visual blast at site of impact
	UPROPERTY(VisibleAnywhere, Category = Custom)
	UParticleSystemComponent* ImpactBlast = nullptr;

	//The physical force of the explosion (ImpactBlast)
	UPROPERTY(VisibleAnywhere, Category = Custom)
	URadialForceComponent* ExplosionForce = nullptr;

	//Damager || ApplyRadialDamage is expecting a float
	UPROPERTY(EditDefaultsOnly, Category = Custom)
	float ProjectileDamage = 20;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = Custom)
	float DestroyDelay = 10.;


	void OnTimerExpire();



};

