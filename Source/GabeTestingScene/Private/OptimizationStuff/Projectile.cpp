// Fill out your copyright notice in the Description page of Project Settings.


#include "OptimizationStuff/Projectile.h"

#include "OptimizationStuff/ProjectilePool.h"

// Sets default values
AProjectile::AProjectile(): lifeTime(0), currentLifeTime(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("PhysicsObject");
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Enable();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentLifeTime -= DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("AProjectile::Tick - %f"), currentLifeTime);
	if(currentLifeTime < 0.f)
	{
		Disable();
		
	}
}

//Called by pool;
void AProjectile::Disable()
{
	MeshComponent->SetSimulatePhysics(false);
	MeshComponent->SetVisibility(false);

	UProjectileSubSystem* system = GetWorld()->GetSubsystem<UProjectileSubSystem>();
	system->ReturnToPool(this);
}

void AProjectile::Enable()
{
	currentLifeTime = lifeTime;
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetVisibility(true);
}

void AProjectile::Launch(FVector direction) const
{
	MeshComponent->SetPhysicsLinearVelocity(direction);
}

