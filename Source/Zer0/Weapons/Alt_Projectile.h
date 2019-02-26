// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
};

