// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Subsystems/Subsystem.h"
#include "ProjectilePool.generated.h"

/**
 * 
 */
UCLASS()
class GABETESTINGSCENE_API UProjectileSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:

	UPROPERTY()
	TArray<AProjectile*> ActiveProjectiles = TArray<AProjectile*>();
	UPROPERTY()
	TArray<AProjectile*> DisabledProjectiles = TArray<AProjectile*>();

	FTimerHandle TimerHandle;

	void Update();
	
public:
	
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	

	
	
	
	 void ReturnToPool(AProjectile* projectile);
	 AProjectile* SpawnProjectile(TSubclassOf<AProjectile> projectileClass, FVector location, FRotator rotation);
	
	
};
