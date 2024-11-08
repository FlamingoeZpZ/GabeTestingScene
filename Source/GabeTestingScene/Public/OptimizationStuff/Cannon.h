// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

//Observer
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot);

UCLASS()
class GABETESTINGSCENE_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();
	
	UPROPERTY(EditDefaultsOnly, Category="Cannon")
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(BlueprintAssignable)
	FOnShoot OnShoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Cannon")
	float timeToFire;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Cannon")
	float force;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Cannon")
	USceneComponent* firingPoint;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float currentTimeToFire;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Shoot();
	

};
