// Fill out your copyright notice in the Description page of Project Settings.


#include "OptimizationStuff/Cannon.h"

#include "OptimizationStuff/Projectile.h"
#include "OptimizationStuff/ProjectilePool.h"

// Sets default values
ACannon::ACannon(): timeToFire(0), force(0), firingPoint(nullptr), currentTimeToFire(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTimeToFire += DeltaTime;

	if(currentTimeToFire >= timeToFire)
		Shoot();
	
}

void ACannon::Shoot()
{
	currentTimeToFire = 0;
	OnShoot.Broadcast();
	UProjectileSubSystem *system = GetWorld()->GetSubsystem<UProjectileSubSystem>();
	AProjectile* projectile = system->SpawnProjectile(Projectile,
		firingPoint->GetComponentLocation(), firingPoint->GetComponentRotation());

	projectile->Launch(firingPoint->GetForwardVector() * force);
}

