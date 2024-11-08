// Fill out your copyright notice in the Description page of Project Settings.


#include "OptimizationStuff/ProjectilePool.h"

void UProjectileSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]
	{
		Update();
	}, 0.016f, true);
}


void UProjectileSubSystem::Update()
{
	float dt = GetWorld()->DeltaTimeSeconds;

	UE_LOG(LogTemp, Warning, TEXT("Ticking %d projectiles"), ActiveProjectiles.Num()) 
	for(AProjectile* Proj : ActiveProjectiles)
	{
		Proj->Tick(dt);
	}
}

void UProjectileSubSystem::ReturnToPool(AProjectile* projectile)
{
	DisabledProjectiles.Add(projectile);
	ActiveProjectiles.Remove(projectile);
}

AProjectile* UProjectileSubSystem::SpawnProjectile(TSubclassOf<AProjectile> projectileClass, FVector location, FRotator rotation)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Projectile"))
	if(DisabledProjectiles.IsEmpty())
	{
		AProjectile * proj =  GetWorld()->SpawnActor<AProjectile>(projectileClass, location, rotation);

			proj->Enable();
		ActiveProjectiles.Add(proj);
		return proj;
	}
	AProjectile* projectile = DisabledProjectiles.Pop();
	projectile->SetActorLocationAndRotation(location, rotation);
	projectile->Enable();
	ActiveProjectiles.Add(projectile);
	return projectile;
}
