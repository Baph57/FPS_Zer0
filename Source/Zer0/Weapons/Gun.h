// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class ZER0_API AGun : public AActor
{
	GENERATED_BODY()
	

	/** Gun mesh: 1st person view (no longer seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

public:	
	// Sets default values for this actor's properties
	AGun();

	//Animation instance forward declaration
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class UAnimInstance* AnimInstance1P; 

	//Animation instance forward declaration
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class UAnimInstance* AnimInstance3P;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation3P;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABallisticsProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	int32 AmmoCount = 30;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void OnFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// APawn interface
	//virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface



};
